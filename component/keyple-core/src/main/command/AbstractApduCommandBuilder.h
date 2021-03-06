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
#include <typeinfo>
#include <memory>

/* Common */
#include "KeypleCoreExport.h"

/* Core */
#include "ApduRequest.h"

/* Calypso */
#include "CommandsTable.h"

namespace keyple {
namespace core {
namespace command {

using namespace keyple::core::seproxy::message;
using namespace keyple::core::command;

/**
 * Generic APDU command builder.
 * <p>
 * It provides the generic getters to retrieve:
 * <ul>
 * <li>the name of the command,</li>
 * <li>the built APDURequest,</li>
 * <li>the corresponding AbstractApduResponseParser class.</li>
 * </ul>
 */
class KEYPLECORE_API AbstractApduCommandBuilder
: public std::enable_shared_from_this<AbstractApduCommandBuilder> {

private:
    /**
     * The command name (will appear in logs)
     */
    std::string name;

protected:
    /**
     * The byte array APDU request
     */
    std::shared_ptr<ApduRequest> request;

public:
    /**
    * the generic abstract constructor to build an APDU request with a command
    * reference and a byte array.
    *
    * @param commandReference command reference
    * @param request request
    */
    AbstractApduCommandBuilder(CommandsTable& commandReference,
                               std::shared_ptr<ApduRequest> request);

    /**
     *
     */
    AbstractApduCommandBuilder(const std::string& name,
                               std::shared_ptr<ApduRequest> request);

    /**
    * Append a string to the current name
    *
    * @param subName the string to append
    */
    void addSubName(const std::string& subName);

    /**
    * Gets the name.
    *
    * @return the name of the APDU command from the CalypsoCommands information.
    */
    std::string getName();

    /**
    * Gets the request.
    *
    * @return the request
    */
    std::shared_ptr<ApduRequest> getApduRequest();
};

}
}
}
