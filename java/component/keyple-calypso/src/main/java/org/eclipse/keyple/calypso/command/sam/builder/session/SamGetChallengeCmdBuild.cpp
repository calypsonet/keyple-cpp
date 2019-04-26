#include "SamGetChallengeCmdBuild.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace sam {
                        namespace builder {
                            namespace session {
                                using CalypsoSamCommands = org::eclipse::keyple::calypso::command::sam::CalypsoSamCommands;
                                using SamCommandBuilder = org::eclipse::keyple::calypso::command::sam::SamCommandBuilder;
                                using SamRevision = org::eclipse::keyple::calypso::command::sam::SamRevision;

                                SamGetChallengeCmdBuild::SamGetChallengeCmdBuild(SamRevision revision, char expectedResponseLength) : SamCommandBuilder(std::make_shared<CalypsoSamCommands>(command), nullptr)
                                {
                                    this->defaultRevision = revision;

                                    if (expectedResponseLength != 0x04 && expectedResponseLength != 0x08) {
                                        throw std::invalid_argument(StringHelper::formatSimple("Bad challenge length! Expected 4 or 8, got %s", expectedResponseLength));
                                    }
                                    char cla = this->defaultRevision.getClassByte();
                                    char p1 = 0x00;
                                    char p2 = 0x00;

                                    // CalypsoRequest calypsoRequest = new CalypsoRequest();
                                    std::vector<char> emptyVector;
                                    request = setApduRequest(cla, std::make_shared<CalypsoSamCommands>(command), p1, p2, emptyVector, expectedResponseLength);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
