#include "OpenSession24CmdBuild.h"
#include "../../../PoClass.h"
#include "../../CalypsoPoCommands.h"
#include "../../PoRevision.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace po {
                        namespace builder {
                            namespace session {
                                using PoClass = org::eclipse::keyple::calypso::command::PoClass;
                                using CalypsoPoCommands = org::eclipse::keyple::calypso::command::po::CalypsoPoCommands;
                                using PoRevision = org::eclipse::keyple::calypso::command::po::PoRevision;

                                OpenSession24CmdBuild::OpenSession24CmdBuild(char keyIndex, std::vector<char> &samChallenge, char sfiToSelect, char recordNumberToRead, const std::string &extraInfo) throw(std::invalid_argument) : AbstractOpenSessionCmdBuild(PoRevision::REV2_4) {

                                    if (keyIndex == 0x00) {
                                        throw std::invalid_argument("Key index can't be null for rev 2.4!");
                                    }

                                    char p1 = static_cast<char>(0x80 + (recordNumberToRead * 8) + keyIndex);
                                    char p2 = static_cast<char>(sfiToSelect * 8);
                                    /*
                                     * case 4: this command contains incoming and outgoing data. We define le = 0, the actual
                                     * length will be processed by the lower layers.
                                     */
                                    char le = 0;

                                    this->request = setApduRequest(PoClass::LEGACY.getValue(), CalypsoPoCommands::getOpenSessionForRev(PoRevision::REV2_4), p1, p2, samChallenge, le);
                                    if (extraInfo != "") {
                                        this->addSubName(extraInfo);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
