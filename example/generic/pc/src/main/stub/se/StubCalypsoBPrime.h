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
#include <memory>

#include "StubSecureElement.h"

namespace keyple {
namespace example {
namespace generic {
namespace pc {
namespace stub {
namespace se {

using namespace keyple::plugin::stub;

/**
 * Simple contact stub SE (no command)
 */
class StubCalypsoBPrime : public StubSecureElement {
public:
    /**
     *
     */
    static const std::string seProtocol;

    /**
     *
     */
    const std::string ATR_HEX = "3B8F8001805A0A01032003111122334482900082";

    /**
     *
     */
    StubCalypsoBPrime();

    /**
     *
     */
    std::vector<char> getATR() override;

    /**
     *
     */
    std::string getSeProcotol() override;

protected:
    /**
     *
     */
    std::shared_ptr<StubCalypsoBPrime> shared_from_this()
    {
        return std::static_pointer_cast<StubCalypsoBPrime>(
            org.eclipse.keyple.plugin.stub
                .StubSecureElement::shared_from_this());
    }
};

}
}
}
}
}
}
