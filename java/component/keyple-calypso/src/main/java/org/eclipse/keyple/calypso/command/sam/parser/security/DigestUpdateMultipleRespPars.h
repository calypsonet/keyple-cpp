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

/* Core */
#include "AbstractSamResponseParser.h"

namespace org {
namespace eclipse {
namespace keyple {
namespace calypso {
namespace command {
namespace sam {
namespace parser {
namespace security {


using AbstractSamResponseParser = org::eclipse::keyple::calypso::command::sam::AbstractSamResponseParser;
using ApduResponse = org::eclipse::keyple::core::seproxy::message::ApduResponse;

/**
 * Digest update multiple response parser. See specs: Calypso / page 54 / 7.4.2 - Session MAC
 * computation
 */
class DigestUpdateMultipleRespPars : public AbstractSamResponseParser {
    /**
     * Instantiates a new DigestUpdateMultipleRespPars.
     *
     * @param response the response
     */
public:
    DigestUpdateMultipleRespPars(std::shared_ptr<ApduResponse> response);

protected:
    std::shared_ptr<DigestUpdateMultipleRespPars> shared_from_this() {
        return std::static_pointer_cast<DigestUpdateMultipleRespPars>(AbstractSamResponseParser::shared_from_this());
    }
};

}
}
}
}
}
}
}
}