#pragma once

#include <string>
#include <vector>
#include "exceptionhelper.h"
#include <memory>

/********************************************************************************
 * Copyright (c) 2018 Calypso Networks Association https://www.calypsonet-asso.org/
 *
 * See the NOTICE file(s) distributed with this work for additional information regarding copyright
 * ownership.
 *
 * This program and the accompanying materials are made available under the terms of the Eclipse
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0
 *
 * SPDX-License-Identifier: EPL-2.0
 ********************************************************************************/
namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace po {


                        class CalypsoPoCommands final : public CommandsTable {

                            /** The po get data. */
public:
                            static CalypsoPoCommands GET_DATA_FCI;

                            /** The po open session. */
                            static CalypsoPoCommands OPEN_SESSION_10;

                            /** The po open session. */
                            static CalypsoPoCommands OPEN_SESSION_24;

                            /** The po open session. */
                            static CalypsoPoCommands OPEN_SESSION_31;

                            /** The po open session. */
                            static CalypsoPoCommands OPEN_SESSION_32;

                            /** The po close session. */
                            static CalypsoPoCommands CLOSE_SESSION;

                            /** The po read records. */
                            static CalypsoPoCommands READ_RECORDS;

                            /** The po update record. */
                            static CalypsoPoCommands UPDATE_RECORD;

                            /** The po append record. */
                            static CalypsoPoCommands APPEND_RECORD;

                            /** The po get challenge. */
                            static CalypsoPoCommands GET_CHALLENGE;

                            /** The po increase counter. */
                            static CalypsoPoCommands INCREASE;

                            /** The po decrease counter. */
                            static CalypsoPoCommands DECREASE;

                            /** The po decrease counter. */
                            static CalypsoPoCommands SELECT_FILE;

private:
                            static std::vector<CalypsoPoCommands> valueList;

                            class StaticConstructor {
                            public:
                                StaticConstructor();
                            };

                            static StaticConstructor staticConstructor;

public:
                            enum class InnerEnum {
                                GET_DATA_FCI,
                                OPEN_SESSION_10,
                                OPEN_SESSION_24,
                                OPEN_SESSION_31,
                                OPEN_SESSION_32,
                                CLOSE_SESSION,
                                READ_RECORDS,
                                UPDATE_RECORD,
                                APPEND_RECORD,
                                GET_CHALLENGE,
                                INCREASE,
                                DECREASE,
                                SELECT_FILE
                            };

                            const InnerEnum innerEnumValue;
private:
                            const std::string nameValue;
                            const int ordinalValue;
                            static int nextOrdinal;

                            /** The name. */
                        private:
                            const std::string name;

                            /** The instruction byte. */
                            const char instructionbyte;

                            /** The command builder class. */
                            const std::type_info commandBuilderClass;

                            /** The response parser class. */
                            const std::type_info responseParserClass;

                            /**
                             * The generic constructor of CalypsoCommands.
                             *
                             * @param name the name
                             * @param instructionByte the instruction byte
                             * @param commandBuilderClass the command builder class
                             * @param responseParserClass the response parser class
                             */
                        public:
                            CalypsoPoCommands(const std::string &name, InnerEnum innerEnum, const std::string &name, char instructionByte, std::type_info commandBuilderClass, std::type_info responseParserClass);


                            /**
                             * Gets the name.
                             *
                             * @return the command name
                             */
                            virtual std::string getName();

                            /**
                             * Gets the instruction byte.
                             *
                             * @return the value of INS byte
                             */
                            virtual char getInstructionByte();

                            /**
                             * Gets the command builder class.
                             *
                             * @return the corresponding command builder class
                             */
                            virtual std::type_info getCommandBuilderClass();

                            /**
                             * Gets the response parser class.
                             *
                             * @return the corresponding response parser class
                             */
                            virtual std::type_info getResponseParserClass();


                            /**
                             * Get the right open-session command for a given {@link PoRevision}
                             *
                             * @param rev Command revision
                             * @return Returned command
                             */
                            static CalypsoPoCommands getOpenSessionForRev(PoRevision rev);

public:
                            bool operator == (const CalypsoPoCommands &other);

                            bool operator != (const CalypsoPoCommands &other);

                            static std::vector<CalypsoPoCommands> values();

                            int ordinal();

                            std::string toString();

                            static CalypsoPoCommands valueOf(const std::string &name);
                        };

                    }
                }
            }
        }
    }
}