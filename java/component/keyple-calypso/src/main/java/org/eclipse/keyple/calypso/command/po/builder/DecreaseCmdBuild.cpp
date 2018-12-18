#include "DecreaseCmdBuild.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace po {
                        namespace builder {
                            using PoClass = org::eclipse::keyple::calypso::command::PoClass;
                            using namespace org::eclipse::keyple::calypso::command::po;

                            DecreaseCmdBuild::DecreaseCmdBuild(PoClass poClass, char sfi, char counterNumber, int decValue, const std::string &extraInfo) throw(std::invalid_argument) : PoCommandBuilder(command, nullptr) {

                                // only counter number >= 1 are allowed
                                if (counterNumber < 1) {
                                    throw std::invalid_argument("Counter number out of range!");
                                }

                                // check if the incValue is in the allowed interval
                                if (decValue < 0 || decValue > 0xFFFFFF) {
                                    throw std::invalid_argument("Decrement value out of range!");
                                }

                                // convert the integer value into a 3-byte buffer
                                std::vector<char> decValueBuffer(3);
                                decValueBuffer[0] = static_cast<char>((decValue >> 16) & 0xFF);
                                decValueBuffer[1] = static_cast<char>((decValue >> 8) & 0xFF);
                                decValueBuffer[2] = static_cast<char>(decValue & 0xFF);

                                char cla = poClass.getValue();
                                char p2 = static_cast<char>(sfi * 8);

                                /* this is a case4 command, we set Le = 0 */
                                this->request = setApduRequest(cla, command, counterNumber, p2, decValueBuffer, static_cast<char>(0));
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