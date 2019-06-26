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

#include <memory>
#include <type_traits>

#include "AbstractIso7816CommandBuilder.h"
#include "CalypsoPoCommands.h"
#include "ApduRequest.h"
#include "ApduResponse.h"

namespace org {
namespace eclipse {
namespace keyple {
namespace calypso {
namespace command {
namespace po {

using AbstractApduResponseParser    = org::eclipse::keyple::core::command::AbstractApduResponseParser;
using AbstractIso7816CommandBuilder = org::eclipse::keyple::core::command::AbstractIso7816CommandBuilder;
using ApduRequest                   = org::eclipse::keyple::core::seproxy::message::ApduRequest;
using ApduResponse                  = org::eclipse::keyple::core::seproxy::message::ApduResponse;

/**
 * Abstract class for all PO command builders.
 * <p>
 */
template<typename T>
class AbstractPoCommandBuilder : public AbstractIso7816CommandBuilder {
    static_assert(std::is_base_of<org.eclipse.keyple.core.command.AbstractApduResponseParser, T>::value, "T must inherit from org.eclipse.keyple.core.command.AbstractApduResponseParser");


    /**
     * Constructor dedicated for the building of referenced Calypso commands
     * 
     * @param reference a command reference from the Calypso command table
     * @param request the ApduRequest (the instruction byte will be overwritten)
     */
public:
    AbstractPoCommandBuilder(CalypsoPoCommands reference, std::shared_ptr<ApduRequest> request) : AbstractIso7816CommandBuilder(reference, request) {
    }

    /**
     * Create the response parser matching the builder
     *
     * @param apduResponse the response data from the SE
     * @return an {@link AbstractApduResponseParser}
     */
    virtual T createResponseParser(std::shared_ptr<ApduResponse> apduResponse) = 0;

protected:
    std::shared_ptr<AbstractPoCommandBuilder> shared_from_this() {
        return std::static_pointer_cast<AbstractPoCommandBuilder>(org.eclipse.keyple.core.command.AbstractIso7816CommandBuilder::shared_from_this());
    }
};

}
}
}
}
}
}