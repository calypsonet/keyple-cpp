#include "PoGetChallengeRespParsTest.h"
#include "../../../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/seproxy/message/ApduResponse.h"
#include "../../../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/seproxy/message/SelectionStatus.h"
#include "../../../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/seproxy/message/SeResponse.h"
#include "../../../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/seproxy/message/SeResponseSet.h"
#include "../../../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/util/ByteArrayUtils.h"
#include "../../../../../../../../../../main/java/org/eclipse/keyple/calypso/command/po/parser/session/PoGetChallengeRespPars.h"
#include "../../../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/command/AbstractApduResponseParser.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace po {
                        namespace parser {
                            namespace session {
                                using AbstractApduResponseParser = org::eclipse::keyple::command::AbstractApduResponseParser;
                                using ApduResponse = org::eclipse::keyple::seproxy::message::ApduResponse;
                                using SeResponse = org::eclipse::keyple::seproxy::message::SeResponse;
                                using SeResponseSet = org::eclipse::keyple::seproxy::message::SeResponseSet;
                                using SelectionStatus = org::eclipse::keyple::seproxy::message::SelectionStatus;
                                using ByteArrayUtils = org::eclipse::keyple::util::ByteArrayUtils;
                                using org::junit::Assert;
                                using org::junit::Test;
                                using org::junit::runner::RunWith;
                                using org::mockito::junit::MockitoJUnitRunner;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void POGetChallengetRespPars()
                                void PoGetChallengeRespParsTest::POGetChallengetRespPars() {
                                    std::vector<char> response = {0x03, 0x0D, 0x0E, static_cast<char>(0xFA), static_cast<char>(0x9C), static_cast<char>(0x8C), static_cast<char>(0xB7), 0x27, static_cast<char>(0x90), 0x00};
                                    std::vector<std::shared_ptr<ApduResponse>> responses;
                                    std::shared_ptr<ApduResponse> apduResponse = std::make_shared<ApduResponse>(response, nullptr);
                                    responses.push_back(apduResponse);
                                    std::shared_ptr<SeResponseSet> seResponse = std::make_shared<SeResponseSet>(std::make_shared<SeResponse>(true, std::make_shared<SelectionStatus>(nullptr, std::make_shared<ApduResponse>(ByteArrayUtils::fromHex("9000"), nullptr), true), responses));

                                    std::shared_ptr<AbstractApduResponseParser> apduResponseParser = std::make_shared<PoGetChallengeRespPars>(seResponse->getSingleResponse()->getApduResponses()[0]);
                                    Assert::assertArrayEquals(response, apduResponseParser->getApduResponse()->getBytes());
                                    Assert::assertEquals("Success", apduResponseParser->getStatusInformation());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
