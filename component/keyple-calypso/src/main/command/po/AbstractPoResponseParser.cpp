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

#include "AbstractPoResponseParser.h"
#include "ApduResponse.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {

using namespace keyple::core::command;
using namespace keyple::core::seproxy::message;

AbstractPoResponseParser::AbstractPoResponseParser(
    std::shared_ptr<ApduResponse> response)
: AbstractApduResponseParser(response)
{
}

}
}
}
}
