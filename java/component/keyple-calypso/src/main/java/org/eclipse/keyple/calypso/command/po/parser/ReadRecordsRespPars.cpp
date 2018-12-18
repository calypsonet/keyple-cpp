#include "ReadRecordsRespPars.h"
#include "../../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/util/ByteArrayUtils.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace po {
                        namespace parser {
                            using AbstractApduResponseParser = org::eclipse::keyple::command::AbstractApduResponseParser;
                            using ByteArrayUtils = org::eclipse::keyple::util::ByteArrayUtils;
const std::unordered_map<Integer, std::shared_ptr<StatusProperties>> ReadRecordsRespPars::STATUS_TABLE;

                            ReadRecordsRespPars::StaticConstructor::StaticConstructor() {
                                                                    std::unordered_map<Integer, std::shared_ptr<AbstractApduResponseParser::StatusProperties>> m(AbstractApduResponseParser::STATUS_TABLE);
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

                            std::unordered_map<Integer, std::shared_ptr<AbstractApduResponseParser::StatusProperties>> ReadRecordsRespPars::getStatusTable() {
                                return STATUS_TABLE;
                            }

                            ReadRecordsRespPars::ReadRecordsRespPars(char recordNumber, ReadDataStructure readDataStructure) {
                                this->recordNumber = recordNumber;
                                this->readDataStructure = readDataStructure;
                            }

                            bool ReadRecordsRespPars::isCounterFile() {
                                return readDataStructure == ReadDataStructure::SINGLE_COUNTER || readDataStructure == ReadDataStructure::MULTIPLE_COUNTER;
                            }

                            std::shared_ptr<SortedMap<Integer, std::vector<char>>> ReadRecordsRespPars::getRecords() {
                                if (!isInitialized()) {
                                    throw std::make_shared<IllegalStateException>("Parser not initialized.");
                                }
                                std::shared_ptr<SortedMap<Integer, std::vector<char>>> records = std::map<Integer, std::vector<char>>();
                                if (!response->isSuccessful()) {
                                    /* return an empty map */
                                    // TODO should we raise an exception?
                                    return records;
                                }
                                if (readDataStructure == ReadDataStructure::SINGLE_RECORD_DATA) {
                                    records->put(static_cast<int>(recordNumber), response->getDataOut());
                                }
                                else if (readDataStructure == ReadDataStructure::MULTIPLE_RECORD_DATA) {
                                    std::vector<char> apdu = response->getDataOut();
                                    int apduLen = apdu.size();
                                    int index = 0;
                                    while (apduLen > 0) {
                                        char recordNb = apdu[index++];
                                        char len = apdu[index++];
                                        records->put(static_cast<int>(recordNb), Arrays::copyOfRange(apdu, index, index + len));
                                        index = index + len;
                                        apduLen = apduLen - 2 - len;
                                    }
                                }
                                else {
                                    throw std::make_shared<IllegalStateException>("The file is a counter file.");
                                }
                                return records;
                            }

                            std::shared_ptr<SortedMap<Integer, Integer>> ReadRecordsRespPars::getCounters() {
                                if (!isInitialized()) {
                                    throw std::make_shared<IllegalStateException>("Parser not initialized.");
                                }
                                std::shared_ptr<SortedMap<Integer, Integer>> counters = std::map<Integer, Integer>();
                                if (!response->isSuccessful()) {
                                    /* return an empty map */
                                    // TODO should we raise an exception?
                                    return counters;
                                }
                                if (readDataStructure == ReadDataStructure::SINGLE_COUNTER || readDataStructure == ReadDataStructure::MULTIPLE_COUNTER) {
                                    std::vector<char> apdu = response->getDataOut();
                                    int numberOfCounters = apdu.size() / 3;
                                    int index = 0;
                                    int key = 0;
                                    for (int i = 0; i < numberOfCounters; i++) {
                                        /*
                                         * convert the 3-byte unsigned value of the counter into an integer (up to 2^24 -1)
                                         */
                                        int counterValue = ((apdu[index + 0] & 0xFF) * 65536) + ((apdu[index + 1] & 0xFF) * 256) + (apdu[index + 2] & 0xFF);
                                        counters->put(key++, counterValue);
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
                                            std::shared_ptr<SortedMap<Integer, std::vector<char>>> recordMap = getRecords();
                                            string = std::string::format("Single record data: {RECORD = %d, DATA = %s}", recordMap->firstKey(), ByteArrayUtils::toHex(recordMap->get(recordMap->firstKey())));
                                        }
                                            break;
                                        case org::eclipse::keyple::calypso::command::po::parser::ReadDataStructure::MULTIPLE_RECORD_DATA: {
                                            std::shared_ptr<SortedMap<Integer, std::vector<char>>> recordMap = getRecords();
                                            std::shared_ptr<StringBuilder> sb = std::make_shared<StringBuilder>();
                                            sb->append("Multiple record data: ");
                                            std::shared_ptr<Set> records = recordMap->keySet();
                                            for (std::shared_ptr<Set::const_iterator> it = records->begin(); it != records->end(); ++it) {
                                                Integer record = (Integer) *it;
                                                sb->append(std::string::format("{RECORD = %d, DATA = %s}", record, ByteArrayUtils::toHex(recordMap->get(record))));
                                                if ((*it)->hasNext()) {
                                                    sb->append(", ");
                                                }
                                            }
                                            string = sb->toString();
                                        }
                                            break;
                                        case org::eclipse::keyple::calypso::command::po::parser::ReadDataStructure::SINGLE_COUNTER: {
                                            std::shared_ptr<SortedMap<Integer, Integer>> counterMap = getCounters();
                                            string = std::string::format("Single counter: {COUNTER = %d, VALUE = %d}", counterMap->firstKey(), counterMap->get(counterMap->firstKey()));
                                        }
                                            break;
                                        case org::eclipse::keyple::calypso::command::po::parser::ReadDataStructure::MULTIPLE_COUNTER: {
                                            std::shared_ptr<SortedMap<Integer, Integer>> counterMap = getCounters();
                                            std::shared_ptr<StringBuilder> sb = std::make_shared<StringBuilder>();
                                            sb->append("Multiple counter: ");
                                            std::shared_ptr<Set> counters = counterMap->keySet();
                                            for (std::shared_ptr<Set::const_iterator> it = counters->begin(); it != counters->end(); ++it) {
                                                Integer counter = (Integer) *it;
                                                sb->append(std::string::format("{COUNTER = %d, VALUE = %d}", counter, counterMap->get(counter)));
                                                if ((*it)->hasNext()) {
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