#include <algorithm>
#include <functional>
#include <iterator>

#include "ReadRecordsRespPars.h"
#include "ByteArrayUtils.h"

/* Common */
#include "stringhelper.h"
#include "Arrays.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace po {
                        namespace parser {

                            using AbstractApduResponseParser = org::eclipse::keyple::command::AbstractApduResponseParser;
                            using ByteArrayUtils = org::eclipse::keyple::util::ByteArrayUtils;

                            std::unordered_map<int, std::shared_ptr<AbstractApduResponseParser::StatusProperties>> ReadRecordsRespPars::STATUS_TABLE;

                            ReadRecordsRespPars::StaticConstructor::StaticConstructor() {
                                std::unordered_map<int, std::shared_ptr<AbstractApduResponseParser::StatusProperties>> m(AbstractApduResponseParser::STATUS_TABLE);
                                m.emplace(0x6981, std::make_shared<AbstractApduResponseParser::StatusProperties>(false, "Command forbidden on binary files"));
                                m.emplace(0x6982, std::make_shared<AbstractApduResponseParser::StatusProperties>(false, "Security conditions not fulfilled (PIN code not presented, encryption required)."));
                                m.emplace(0x6985, std::make_shared<AbstractApduResponseParser::StatusProperties>(false, "Access forbidden (Never access mode, stored value log file and a stored value operation was done during the current session)."));
                                m.emplace(0x6986, std::make_shared<AbstractApduResponseParser::StatusProperties>(false, "Command not allowed (no current EF)"));
                                m.emplace(0x6A82, std::make_shared<AbstractApduResponseParser::StatusProperties>(false, "File not found"));
                                m.emplace(0x6A83, std::make_shared<AbstractApduResponseParser::StatusProperties>(false, "Record not found (record index is 0, or above NumRec"));
                                m.emplace(0x6B00, std::make_shared<AbstractApduResponseParser::StatusProperties>(false, "P2 value not supported"));
                                m.emplace(0x6CFF, std::make_shared<AbstractApduResponseParser::StatusProperties>(false, "Le value incorrect"));
                                m.emplace(0x9000, std::make_shared<AbstractApduResponseParser::StatusProperties>(true, "Successful execution."));
                                STATUS_TABLE = m;
                            }

                            ReadRecordsRespPars::StaticConstructor ReadRecordsRespPars::staticConstructor;

                            std::unordered_map<int, std::shared_ptr<AbstractApduResponseParser::StatusProperties>> ReadRecordsRespPars::getStatusTable() {
                                return STATUS_TABLE;
                            }

                            ReadRecordsRespPars::ReadRecordsRespPars(char recordNumber, ReadDataStructure readDataStructure) {
                                this->recordNumber = recordNumber;
                                this->readDataStructure = readDataStructure;
                            }

                            bool ReadRecordsRespPars::isCounterFile() {
                                return readDataStructure == ReadDataStructure::SINGLE_COUNTER || readDataStructure == ReadDataStructure::MULTIPLE_COUNTER;
                            }

                            std::shared_ptr<std::map<int, std::vector<char>>> ReadRecordsRespPars::getRecords() {
                                if (!isInitialized()) {
                                    throw std::make_shared<IllegalStateException>("Parser not initialized.");
                                }
                                std::shared_ptr<std::map<int, std::vector<char>>> records = std::make_shared<std::map<int, std::vector<char>>>();
                                if (!response->isSuccessful()) {
                                    /* return an empty map */
                                    // TODO should we raise an exception?
                                    return records;
                                }
                                if (readDataStructure == ReadDataStructure::SINGLE_RECORD_DATA) {
                                    records->emplace(static_cast<int>(recordNumber), response->getDataOut());
                                }
                                else if (readDataStructure == ReadDataStructure::MULTIPLE_RECORD_DATA) {
                                    std::vector<char> apdu = response->getDataOut();
                                    int apduLen = apdu.size();
                                    int index = 0;
                                    while (apduLen > 0) {
                                        char recordNb = apdu[index++];
                                        char len = apdu[index++];
                                        records->insert(std::pair<int, std::vector<char>>(recordNb, Arrays::copyOfRange(apdu, index, index + len)));
                                        index = index + len;
                                        apduLen = apduLen - 2 - len;
                                    }
                                }
                                else {
                                    throw IllegalStateException("The file is a counter file.");
                                }
                                return records;
                            }

                            std::shared_ptr<std::map<int, int>> ReadRecordsRespPars::getCounters()
                            {
                                if (!isInitialized()) {
                                    throw IllegalStateException("Parser not initialized.");
                                }

                                std::shared_ptr<std::map<int, int>> counters = std::make_shared<std::map<int, int>>();
                                if (!response->isSuccessful()) {
                                    /* return an empty map */
                                    // TODO should we raise an exception?
                                    return counters;
                                }

                                if (readDataStructure == ReadDataStructure::SINGLE_COUNTER || readDataStructure == ReadDataStructure::MULTIPLE_COUNTER) {
                                    std::vector<char> apdu = response->getDataOut();
                                    int numberOfCounters = apdu.size() / 3;
                                    int index = 0;
                                    int key = 1; // the first counter is indexed 1
                                    for (int i = 0; i < numberOfCounters; i++) {
                                        /*
                                         * convert the 3-byte unsigned value of the counter into an integer (up to 2^24 -1)
                                         */
                                        int counterValue = ((apdu[index + 0] & 0xFF) * 65536) + ((apdu[index + 1] & 0xFF) * 256) + (apdu[index + 2] & 0xFF);
                                        counters->insert(std::pair<int, int>(key++, counterValue));
                                        index = index + 3;
                                    }

                                }
                                else {
                                    throw std::make_shared<IllegalStateException>("The file is a data file.");
                                }
                                return counters;
                            }

                            std::string ReadRecordsRespPars::toString() {
                                std::string string;
                                if (isInitialized()) {
                                    switch (readDataStructure) {
                                        case org::eclipse::keyple::calypso::command::po::parser::ReadDataStructure::SINGLE_RECORD_DATA: {
                                            std::shared_ptr<std::map<int, std::vector<char>>> recordMap = getRecords();
                                            string = StringHelper::formatSimple("Single record data: {RECORD = %d, DATA = %s}", recordMap->begin()->first, ByteArrayUtils::toHex(recordMap->begin()->second));
                                        }
                                            break;
                                        case org::eclipse::keyple::calypso::command::po::parser::ReadDataStructure::MULTIPLE_RECORD_DATA: {
                                            std::shared_ptr<std::map<int, std::vector<char>>> recordMap = getRecords();
                                            std::shared_ptr<StringBuilder> sb = std::make_shared<StringBuilder>();
                                            sb->append("Multiple record data: ");
                                            std::set<int> records;
                                            std::transform(recordMap->begin(), recordMap->end(), std::inserter(records, records.begin()), std::bind(&std::map<int, std::vector<char>>::value_type::first, std::placeholders::_1));
                                            for (std::set<int>::const_iterator it = records.begin(); it != records.end(); ++it) {
                                                int record = (int) *it;
                                                sb->append(StringHelper::formatSimple("{RECORD = %d, DATA = %s}", record, ByteArrayUtils::toHex(recordMap->find(record)->second)));
                                                if (it != records.end()) {
                                                    sb->append(", ");
                                                }
                                            }
                                            string = sb->toString();
                                        }
                                            break;
                                        case org::eclipse::keyple::calypso::command::po::parser::ReadDataStructure::SINGLE_COUNTER: {
                                            std::shared_ptr<std::map<int, int>> counterMap = getCounters();
                                            string = StringHelper::formatSimple("Single counter: {COUNTER = %d, VALUE = %d}", counterMap->begin()->first, counterMap->begin()->second);
                                        }
                                            break;
                                        case org::eclipse::keyple::calypso::command::po::parser::ReadDataStructure::MULTIPLE_COUNTER: {
                                            std::shared_ptr<std::map<int, int>> counterMap = getCounters();
                                            std::shared_ptr<StringBuilder> sb = std::make_shared<StringBuilder>();
                                            sb->append("Multiple counter: ");
                                            std::set<int> counters;
                                            std::transform(counterMap->begin(), counterMap->end(), inserter(counters, counters.begin()), std::bind(&std::map<int, int>::value_type::first, std::placeholders::_1));
                                            for (std::set<int>::const_iterator it = counters.begin(); it != counters.end(); ++it) {
                                                int counter = (int) *it;
                                                sb->append(StringHelper::formatSimple("{COUNTER = %d, VALUE = %d}", counter, counterMap->find(counter)->second));
                                                if (it != counters.end()) {
                                                    sb->append(", ");
                                                }
                                            }
                                            string = sb->toString();
                                        }
                                            break;
                                        default:
                                            throw std::make_shared<IllegalStateException>("Unexpected data structure");
                                    }
                                }
                                else {
                                    string = "Not initialized.";
                                }
                                return string;
                            }
                        }
                    }
                }
            }
        }
    }
}
