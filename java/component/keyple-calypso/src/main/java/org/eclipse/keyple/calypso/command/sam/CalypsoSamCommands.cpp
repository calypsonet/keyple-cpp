#include "CalypsoSamCommands.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace sam {
                        using namespace org::eclipse::keyple::calypso::command::sam::builder::session;
                        using SelectDiversifierCmdBuild = org::eclipse::keyple::calypso::command::sam::builder::session::SelectDiversifierCmdBuild;
                        using namespace org::eclipse::keyple::calypso::command::sam::parser::session;
                        using SelectDiversifierRespPars = org::eclipse::keyple::calypso::command::sam::parser::session::SelectDiversifierRespPars;
                        using AbstractApduCommandBuilder = org::eclipse::keyple::command::AbstractApduCommandBuilder;
                        using AbstractApduResponseParser = org::eclipse::keyple::command::AbstractApduResponseParser;
                        using CommandsTable = org::eclipse::keyple::command::CommandsTable;

CalypsoSamCommands CalypsoSamCommands::SELECT_DIVERSIFIER("SELECT_DIVERSIFIER", InnerEnum::SELECT_DIVERSIFIER, "Select Diversifier", static_cast<char>(0x14), org::eclipse::keyple::calypso::command::sam::builder::session::SelectDiversifierCmdBuild::typeid, org::eclipse::keyple::calypso::command::sam::parser::session::SelectDiversifierRespPars::typeid);
CalypsoSamCommands CalypsoSamCommands::GET_CHALLENGE("GET_CHALLENGE", InnerEnum::GET_CHALLENGE, "Get Challenge", static_cast<char>(0x84), SamGetChallengeCmdBuild::typeid, SamGetChallengeRespPars::typeid);
CalypsoSamCommands CalypsoSamCommands::DIGEST_INIT("DIGEST_INIT", InnerEnum::DIGEST_INIT, "Digest Init", static_cast<char>(0x8A), DigestInitCmdBuild::typeid, DigestInitRespPars::typeid);
CalypsoSamCommands CalypsoSamCommands::DIGEST_UPDATE("DIGEST_UPDATE", InnerEnum::DIGEST_UPDATE, "Digest Update", static_cast<char>(0x8C), DigestUpdateCmdBuild::typeid, DigestUpdateRespPars::typeid);
CalypsoSamCommands CalypsoSamCommands::DIGEST_UPDATE_MULTIPLE("DIGEST_UPDATE_MULTIPLE", InnerEnum::DIGEST_UPDATE_MULTIPLE, "Digest Update Multiple", static_cast<char>(0x8C), DigestUpdateMultipleCmdBuild::typeid, DigestUpdateMultipleRespPars::typeid);
CalypsoSamCommands CalypsoSamCommands::DIGEST_CLOSE("DIGEST_CLOSE", InnerEnum::DIGEST_CLOSE, "Digest Close", static_cast<char>(0x8E), DigestCloseCmdBuild::typeid, DigestCloseRespPars::typeid);
CalypsoSamCommands CalypsoSamCommands::DIGEST_AUTHENTICATE("DIGEST_AUTHENTICATE", InnerEnum::DIGEST_AUTHENTICATE, "Digest Authenticate", static_cast<char>(0x82), DigestAuthenticateCmdBuild::typeid, DigestAuthenticateRespPars::typeid);

std::vector<CalypsoSamCommands> CalypsoSamCommands::valueList;

CalypsoSamCommands::StaticConstructor::StaticConstructor() {
    valueList.push_back(SELECT_DIVERSIFIER);
    valueList.push_back(GET_CHALLENGE);
    valueList.push_back(DIGEST_INIT);
    valueList.push_back(DIGEST_UPDATE);
    valueList.push_back(DIGEST_UPDATE_MULTIPLE);
    valueList.push_back(DIGEST_CLOSE);
    valueList.push_back(DIGEST_AUTHENTICATE);
}

CalypsoSamCommands::StaticConstructor CalypsoSamCommands::staticConstructor;
int CalypsoSamCommands::nextOrdinal = 0;

                        CalypsoSamCommands::CalypsoSamCommands(const std::string &name, InnerEnum innerEnum, const std::string &name, char instructionByte, std::type_info commandBuilderClass, std::type_info responseParserClass) : nameValue(name), ordinalValue(nextOrdinal++), innerEnumValue(innerEnum) {
                            this->name = name;
                            this->instructionbyte = instructionByte;
                            this->commandBuilderClass = commandBuilderClass;
                            this->responseParserClass = responseParserClass;
                        }

                        std::string CalypsoSamCommands::getName() {
                            return name;
                        }

                        char CalypsoSamCommands::getInstructionByte() {
                            return instructionbyte;
                        }

                        std::type_info CalypsoSamCommands::getCommandBuilderClass() {
                            return commandBuilderClass;
                        }

                        std::type_info CalypsoSamCommands::getResponseParserClass() {
                            return responseParserClass;
                        }

bool CalypsoSamCommands::operator == (const CalypsoSamCommands &other) {
    return this->ordinalValue == other.ordinalValue;
}

bool CalypsoSamCommands::operator != (const CalypsoSamCommands &other) {
    return this->ordinalValue != other.ordinalValue;
}

std::vector<CalypsoSamCommands> CalypsoSamCommands::values() {
    return valueList;
}

int CalypsoSamCommands::ordinal() {
    return ordinalValue;
}

std::string CalypsoSamCommands::toString() {
    return nameValue;
}

CalypsoSamCommands CalypsoSamCommands::valueOf(const std::string &name) {
    for (auto enumInstance : CalypsoSamCommands::valueList) {
        if (enumInstance.nameValue == name) {
            return enumInstance;
        }
    }
}
                    }
                }
            }
        }
    }
}