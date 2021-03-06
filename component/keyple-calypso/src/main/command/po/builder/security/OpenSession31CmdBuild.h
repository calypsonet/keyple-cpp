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

#include "AbstractOpenSessionCmdBuild.h"
#include "OpenSession31RespPars.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace builder {
namespace security {

using namespace keyple::calypso::command::po::builder::security;
using namespace keyple::calypso::command::po::parser::security;
using namespace keyple::core::seproxy::message;

class OpenSession31CmdBuild final
: public AbstractOpenSessionCmdBuild<OpenSession31RespPars> {
public:
    /**
     * Instantiates a new AbstractOpenSessionCmdBuild.
     *
     * @param keyIndex the key index
     * @param samChallenge the sam challenge returned by the SAM Get Challenge
     *        APDU command
     * @param sfiToSelect the sfi to select
     * @param recordNumberToRead the record number to read
     * @param extraInfo extra information included in the logs (can be null or
     *        empty)
     * @throws IllegalArgumentException - if the request is inconsistent
     */
    OpenSession31CmdBuild(uint8_t keyIndex,
                          const std::vector<uint8_t>& samChallenge,
                          uint8_t sfiToSelect, uint8_t recordNumberToRead,
                          const std::string& extraInfo);

    /**
     *
     */
    std::shared_ptr<OpenSession31RespPars>
    createResponseParser(std::shared_ptr<ApduResponse> apduResponse) override;

protected:
    /**
     *
     */
    std::shared_ptr<OpenSession31CmdBuild> shared_from_this()
    {
        return std::static_pointer_cast<OpenSession31CmdBuild>(
            AbstractOpenSessionCmdBuild<
                OpenSession31RespPars>::shared_from_this());
    }
};

}
}
}
}
}
}
