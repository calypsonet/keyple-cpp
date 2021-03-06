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
#include <stdexcept>
#include <memory>

/* Core */
#include "AbstractApduCommandBuilder.h"
#include "KeypleCoreExport.h"

namespace keyple {
namespace core {
namespace command {

using namespace keyple::core::command;
using namespace keyple::core::seproxy::message;

/**
 * Iso7816 APDU command builder.
 * <p>
 * It has to be extended by all PO and SAM command builder classes.
 * <p>
 * It provides, through the AbstractApduCommandBuilder superclass, the generic
 * getters to retrieve:
 * <ul>
 * <li>the name of the command,</li>
 * <li>the built APDURequest,</li>
 * <li>the corresponding AbstractApduResponseParser class.</li>
 * </ul>
 */
class KEYPLECORE_API AbstractIso7816CommandBuilder
: public AbstractApduCommandBuilder {
public:
    /**
     * Abstract constructor to build a command with a command reference and an
     * {@link ApduRequest}.
     *
     * @param commandReference command reference
     * @param request ApduRequest
     */
    AbstractIso7816CommandBuilder(CommandsTable& commandReference,
                                  std::shared_ptr<ApduRequest> request);

    /**
     * Abstract constructor to build a command with a command name and an
     * {@link ApduRequest}
     *
     * @param name name of command
     * @param request ApduRequest
     */
    AbstractIso7816CommandBuilder(const std::string& name,
                                  std::shared_ptr<ApduRequest> request);

    /**
     *
     */
    virtual ~AbstractIso7816CommandBuilder()
    {
    }

protected:
    /**
     * Helper method to create an ApduRequest from separated elements.
     * <p>
     * The ISO7816-4 case for data in a command-response pair is determined from
     * the provided
     * arguments:
     * <ul>
     * <li><code>dataIn &nbsp;= null, le &nbsp;= null</code>&nbsp;&nbsp;&rarr;
     * &nbsp;&nbsp;case 1: no command data, no response data expected.</li>
     * <li><code>dataIn &nbsp;= null, le != null</code>&nbsp;&nbsp;&rarr;&nbsp;
     * &nbsp;case 2: no command data, expected response data.</li>
     * <li><code>dataIn != null, le &nbsp;= null</code>&nbsp;&nbsp;&rarr;&nbsp;
     * &nbsp;case 3: command data, no response data expected.</li>
     * <li><code>dataIn != null, le &nbsp;= 0&nbsp;&nbsp;&nbsp;</code>&nbsp;
     * &nbsp;&rarr;&nbsp;&nbsp;case 4: command data, expected response data.
     * </li>
     * </ul>
     * <p>
     * If dataIn is not null and Le &gt; 0 an IllegalArgumentException is thrown
     *
     * @param cla class of instruction
     * @param command instruction code
     * @param p1 instruction parameter 1
     * @param p2 instruction parameter 2
     * @param dataIn bytes sent in the data field of the command. dataIn.limit
     *        will be Lc (Number of bytes present in the data field of the
     *        command)
     * @return an ApduRequest
     */
    virtual std::shared_ptr<ApduRequest>
    setApduRequest(uint8_t cla, const CommandsTable& command, uint8_t p1,
                   uint8_t p2, const std::vector<uint8_t>& dataIn);

    /**
     * Helper method to create an ApduRequest from separated elements.
     * <p>
     * The ISO7816-4 case for data in a command-response pair is determined from
     * the provided
     * arguments:
     * <ul>
     * <li><code>dataIn &nbsp;= null, le &nbsp;= null</code>&nbsp;&nbsp;&rarr;
     * &nbsp;&nbsp;case 1: no command data, no response data expected.</li>
     * <li><code>dataIn &nbsp;= null, le != null</code>&nbsp;&nbsp;&rarr;&nbsp;
     * &nbsp;case 2: no command data, expected response data.</li>
     * <li><code>dataIn != null, le &nbsp;= null</code>&nbsp;&nbsp;&rarr;&nbsp;
     * &nbsp;case 3: command data, no response data expected.</li>
     * <li><code>dataIn != null, le &nbsp;= 0&nbsp;&nbsp;&nbsp;</code>&nbsp;
     * &nbsp;&rarr;&nbsp;&nbsp;case 4: command data, expected response data.
     * </li>
     * </ul>
     * <p>
     * If dataIn is not null and Le &gt; 0 an IllegalArgumentException is thrown
     *
     * @param cla class of instruction
     * @param command instruction code
     * @param p1 instruction parameter 1
     * @param p2 instruction parameter 2
     * @param le maximum number of bytes expected in the data field of the
     *        response to the command (set to 0 is the case where ingoing and
     *        outgoing are present. Let the lower layer to handle the actual
     *        length [case4])
     * @return an ApduRequest
     */
    virtual std::shared_ptr<ApduRequest>
    setApduRequest(uint8_t cla, const CommandsTable& command, uint8_t p1,
                   uint8_t p2, uint8_t le);

    /**
     * Helper method to create an ApduRequest from separated elements.
     * <p>
     * The ISO7816-4 case for data in a command-response pair is determined from
     * the provided
     * arguments:
     * <ul>
     * <li><code>dataIn &nbsp;= null, le &nbsp;= null</code>&nbsp;&nbsp;&rarr;
     * &nbsp;&nbsp;case 1: no command data, no response data expected.</li>
     * <li><code>dataIn &nbsp;= null, le != null</code>&nbsp;&nbsp;&rarr;&nbsp;
     * &nbsp;case 2: no command data, expected response data.</li>
     * <li><code>dataIn != null, le &nbsp;= null</code>&nbsp;&nbsp;&rarr;&nbsp;
     * &nbsp;case 3: command data, no response data expected.</li>
     * <li><code>dataIn != null, le &nbsp;= 0&nbsp;&nbsp;&nbsp;</code>&nbsp;
     * &nbsp;&rarr;&nbsp;&nbsp;case 4: command data, expected response data.
     * </li>
     * </ul>
     * <p>
     * If dataIn is not null and Le &gt; 0 an IllegalArgumentException is thrown
     *
     * @param cla class of instruction
     * @param command instruction code
     * @param p1 instruction parameter 1
     * @param p2 instruction parameter 2
     * @param dataIn bytes sent in the data field of the command. dataIn.limit
     *        will be Lc (Number of bytes present in the data field of the
     *        command)
     * @param le maximum number of bytes expected in the data field of the
     *        response to the command (set to 0 is the case where ingoing and
     *        outgoing are present. Let the lower layer to handle the actual
     *        length [case4])
     * @return an ApduRequest
     */
    virtual std::shared_ptr<ApduRequest>
    setApduRequest(uint8_t cla, const CommandsTable& command, uint8_t p1,
                   uint8_t p2, const std::vector<uint8_t>& dataIn, uint8_t le);

    /**
     *
     */
    std::shared_ptr<AbstractIso7816CommandBuilder> shared_from_this()
    {
        return std::static_pointer_cast<AbstractIso7816CommandBuilder>(
            AbstractApduCommandBuilder::shared_from_this());
    }
};

}
}
}
