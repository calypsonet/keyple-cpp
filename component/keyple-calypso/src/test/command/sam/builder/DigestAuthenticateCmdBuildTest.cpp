#include "DigestAuthenticateCmdBuildTest.h"
#include "DigestAuthenticateCmdBuild.h"
#include "AbstractApduCommandBuilder.h"
#include "ApduRequest.h"
#include "ByteArrayUtil.h"

using namespace keyple::calypso::command::sam::builder;

        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace sam {
                        namespace builder {
                            using DigestAuthenticateCmdBuild = keyple::calypso::command::sam::builder::security::DigestAuthenticateCmdBuild;
                            using AbstractApduCommandBuilder = keyple::core::command::AbstractApduCommandBuilder;
                            using ApduRequest = keyple::core::seproxy::message::ApduRequest;
                            using ByteArrayUtils = keyple::core::util::ByteArrayUtil;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void digestAuthenticate() throws IllegalArgumentException
                            void DigestAuthenticateCmdBuildTest::digestAuthenticate() {

                                std::vector<char> signaturePO = {0x00, 0x01, 0x02, 0x03};
                                std::vector<char> request = {static_cast<char>(0x94), static_cast<char>(0x82), 0x00, 0x00, 0x04, 0x00, 0x01, 0x02, 0x03};

                                std::shared_ptr<AbstractApduCommandBuilder> apduCommandBuilder = std::make_shared<DigestAuthenticateCmdBuild>(nullptr, signaturePO);
                                ApduRequest ApduRequest = apduCommandBuilder->getApduRequest();

                                ASSERT_EQ(ByteArrayUtils::toHex(request), ByteArrayUtils::toHex(ApduRequest::getBytes()));
                            }
                        }
                    }
                }
            }
        }
