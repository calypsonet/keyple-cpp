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

#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

#include "AbstractPoCommandBuilder.h"
#include "CalypsoPoCommands.h"
#include "IncreaseRespPars.h"
#include "PoModificationCommand.h"
#include "PoSendableInSession.h"
#include "PoClass.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace builder {

using namespace keyple::calypso::command::po;
using namespace keyple::calypso::command;
using namespace keyple::calypso::command::po::parser;
using namespace keyple::core::seproxy::message;

/**
 * The Class IncreaseCmdBuild. This class provides the dedicated constructor to build the Increase
 * APDU command.
 *
 */
class IncreaseCmdBuild final
: public AbstractPoCommandBuilder<IncreaseRespPars>,
  public PoSendableInSession,
  public PoModificationCommand {

private:
    /**
     * The command
     */
    CalypsoPoCommands& command = CalypsoPoCommands::INCREASE;

    /**
     * Instantiates a new increase cmd build from command parameters.
     *
     * @param poClass indicates which CLA byte should be used for the Apdu
     * @param counterNumber &gt;= 01h: Counters file, number of the counter. 00h: Simulated Counter
     *        file.
     * @param sfi SFI of the file to select or 00h for current EF
     * @param incValue Value to add to the counter (defined as a positive int &lt;= 16777215
     *        [FFFFFFh])
     * @param extraInfo extra information included in the logs (can be null or empty)
     * @throws IllegalArgumentException - if the decrement value is out of range
     * @throws IllegalArgumentException - if the command is inconsistent
     */
public:
    IncreaseCmdBuild(PoClass poClass, char sfi, char counterNumber,
                     int incValue, const std::string& extraInfo);

    /**
     *
     */
    std::shared_ptr<IncreaseRespPars>
    createResponseParser(std::shared_ptr<ApduResponse> apduResponse) override;

protected:
    /**
     *
     */
    std::shared_ptr<IncreaseCmdBuild> shared_from_this()
    {
        return std::static_pointer_cast<IncreaseCmdBuild>(
            AbstractPoCommandBuilder<IncreaseRespPars>::shared_from_this());
    }
};

}
}
}
}
}
