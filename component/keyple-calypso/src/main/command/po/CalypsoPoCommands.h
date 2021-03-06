/******************************************************************************
 * Copyright (c) 2018 Calypso Networks Association                            *
 * https://www.calypsonet-asso.org/                                           *
 *                                                                            *
 * See the NOTICE file(s) distributed with this work for additional           *
 * information regarding copyright ownership.                                 *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the Eclipse Public License 2.0 which is available at              *
 * http://www.eclipse.org/legal/epl-2.0                                       *
 *                                                                            *
 * SPDX-License-Identifier: EPL-2.0                                           *
 ******************************************************************************/

#pragma once

#include <string>
#include <vector>
#include "exceptionhelper.h"
#include <memory>

/* Core */
#include "CommandsTable.h"
#include "PoRevision.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {

using namespace keyple::core::command;
using namespace keyple::calypso::command::po;

class CalypsoPoCommands final : public CommandsTable {
public:
    /** The po get data. */
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

    /** The po write record. */
    static CalypsoPoCommands WRITE_RECORD;

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

    /* The po change key */
    static CalypsoPoCommands CHANGE_KEY;

    /**
     *
     */
    enum class InnerEnum {
        GET_DATA_FCI,
        OPEN_SESSION_10,
        OPEN_SESSION_24,
        OPEN_SESSION_31,
        OPEN_SESSION_32,
        CLOSE_SESSION,
        READ_RECORDS,
        UPDATE_RECORD,
        WRITE_RECORD,
        APPEND_RECORD,
        GET_CHALLENGE,
        INCREASE,
        DECREASE,
        SELECT_FILE,
        CHANGE_KEY
    };

    /**
     *
     */
    const InnerEnum innerEnumValue;

    /**
     * The generic constructor of CalypsoCommands.
     *
     * @param name the name
     * @param instructionByte the instruction byte
     */
    CalypsoPoCommands(const std::string& nameValue, InnerEnum innerEnum,
                      const std::string& name, uint8_t instructionByte);

    /**
     *
     */
    CalypsoPoCommands(const CalypsoPoCommands& other);

    /**
     * Gets the name.
     *
     * @return the command name
     */
    virtual const std::string& getName() const override;

    /**
     * Gets the instruction byte.
     *
     * @return the value of INS byte
     */
    virtual uint8_t getInstructionByte() const override;

    /**
     * Get the right open-session command for a given {@link PoRevision}
     *
     * @param rev Command revision
     * @return Returned command
     */
    static CalypsoPoCommands& getOpenSessionForRev(PoRevision rev);

    /**
     *
     */
    bool operator==(const CalypsoPoCommands& other);

    /**
     *
     */
    bool operator!=(const CalypsoPoCommands& other);

    /**
     *
     */
    static std::vector<CalypsoPoCommands> values();

    /**
     *
     */
    int ordinal();

    /**
     *
     */
    std::string toString();

    /**
     *
     */
    static CalypsoPoCommands valueOf(const std::string& name);

    /*
     * Alex: had to add these for the compiler to authorize instanciation of
     * class. Not present in Java code.
     */
    const std::type_info& getCommandBuilderClass() const override
    {

        /* Fixme! */
        return typeid(this);
    }

    /**
     *
     */
    const std::type_info& getResponseParserClass() const override
    {
        /* Fixe me! */
        return typeid(this);
    }

private:
    /**
     *
     */
    static std::vector<CalypsoPoCommands> valueList;

    /**
     *
     */
    class StaticConstructor {
    public:
        StaticConstructor();
    };

    /**
     *
     */
    static StaticConstructor staticConstructor;

    /**
     *
     */
    const std::string nameValue;

    /**
     *
     */
    const int ordinalValue;

    /**
     *
     */
    static int nextOrdinal;
    /**
     * The name
     */
    const std::string name;

    /**
     * The instruction byte
     */
    const char instructionbyte;
};

}
}
}
}
