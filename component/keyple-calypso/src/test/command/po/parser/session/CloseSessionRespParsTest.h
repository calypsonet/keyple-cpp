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

#include <vector>
#include <stdexcept>
#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace parser {
namespace security {

class CloseSessionRespParsTest
: public std::enable_shared_from_this<CloseSessionRespParsTest> {
public:
    virtual void closeSessionRespPars();

    virtual void TestToPOHalfSessionSignature();

    virtual void existingTestConverted();

    virtual void abortingASession();

    virtual void lc4withoutPostponedData();

    virtual void lc4WithPostponedData();
};

}
}
}
}
}
}
