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

#include "SelectDiversifierRespParsTest.h"
#include "ApduResponse.h"
#include "SelectDiversifierRespPars.h"
#include "AbstractApduResponseParser.h"

namespace keyple {
namespace calypso {
namespace command {
namespace sam {
namespace parser {
using SelectDiversifierRespPars =
    keyple::calypso::command::sam::parser::security::SelectDiversifierRespPars;
using AbstractApduResponseParser =
    keyple::core::command::AbstractApduResponseParser;
using ApduResponse = keyple::core::seproxy::message::ApduResponse;
//using org::hamcrest::core::IsNot;

void SelectDiversifierRespParsTest::selectDiversifierResp()
{
    /*
     * We check here that the value returned by getApduResponse matches the
     * value provided at construct time.
     */
    std::vector<uint8_t> cResp  = {0x90, 0x00};
    std::vector<uint8_t> cResp2 = {0x80, 0x00};

    std::shared_ptr<ApduResponse> apduResponse =
        std::make_shared<ApduResponse>(cResp, nullptr);
    std::shared_ptr<ApduResponse> apduResponse1 =
        std::make_shared<ApduResponse>(cResp2, nullptr);

    std::shared_ptr<AbstractApduResponseParser> apduResponseParser =
        std::make_shared<SelectDiversifierRespPars>(apduResponse);
    ASSERT_EQ(0x9000, apduResponseParser->getApduResponse()->getStatusCode());

    apduResponseParser =
        std::make_shared<SelectDiversifierRespPars>(apduResponse1);
    ASSERT_NE(apduResponseParser->getApduResponse()->getStatusCode(), 0x9000);
}
}
}
}
}
}
