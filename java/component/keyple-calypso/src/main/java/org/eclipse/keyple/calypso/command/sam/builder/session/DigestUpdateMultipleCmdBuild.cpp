#include "DigestUpdateMultipleCmdBuild.h"

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

                                DigestUpdateMultipleCmdBuild::DigestUpdateMultipleCmdBuild(SamRevision revision, std::vector<char> &digestData) throw(std::invalid_argument) : org::eclipse::keyple::calypso::command::sam::SamCommandBuilder(command, nullptr) {
                                    if (revision != nullptr) {
                                        this->defaultRevision = revision;
                                    }
                                    char cla = SamRevision::S1D.equals(this->defaultRevision) ? static_cast<char>(0x94) : static_cast<char>(0x80);
                                    char p1 = static_cast<char>(0x80);
                                    char p2 = static_cast<char>(0x00);

                                    request = setApduRequest(cla, command, p1, p2, digestData, nullptr);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}