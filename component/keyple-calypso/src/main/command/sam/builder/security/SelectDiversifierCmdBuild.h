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

#include "AbstractSamCommandBuilder.h"
#include "CalypsoSamCommands.h"
#include "SamRevision.h"

namespace keyple {
namespace calypso {
namespace command {
namespace sam {
namespace builder {
namespace security {

using namespace keyple::calypso::command::sam;

/**
 * This class provides the dedicated constructor to build the SAM Select
 * Diversifier APDU command.
 */
class SelectDiversifierCmdBuild : public AbstractSamCommandBuilder {
public:
    /**
     * Instantiates a new SelectDiversifierCmdBuild.
     *
     * @param revision the SAM revision
     * @param diversifier the application serial number
     * @throws IllegalArgumentException - if the diversifier is null or has a
     *         wrong length
     * @throws IllegalArgumentException - if the request is inconsistent
     */
    SelectDiversifierCmdBuild(SamRevision revision,
                              std::vector<uint8_t>& diversifier);

    /**
     *
     */
    virtual ~SelectDiversifierCmdBuild()
    {
    }

protected:
    /**
     *
     */
    std::shared_ptr<SelectDiversifierCmdBuild> shared_from_this()
    {
        return std::static_pointer_cast<SelectDiversifierCmdBuild>(
            AbstractSamCommandBuilder::shared_from_this());
    }

private:
    /**
     * The command
     */
    CalypsoSamCommands& command = CalypsoSamCommands::SELECT_DIVERSIFIER;
};

}
}
}
}
}
}
