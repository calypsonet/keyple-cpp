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

#include "StubHoplink.h"
#include "ByteArrayUtil.h"

namespace keyple {
namespace example {
namespace calypso {
namespace pc {
namespace stub {
namespace se {

using namespace keyple::plugin::stub;
using namespace keyple::util;

const std::string StubHoplink::seProtocol = "PROTOCOL_ISO14443_4";

StubHoplink::StubHoplink()
{
    /* Select Application */
    addHexCommand("00A4040005AABBCCDDEE00", "6A82");
    /* Select Application */
    addHexCommand("00A404000AA000000291A00000019100",
                  "6F25840BA000000291A00000019102A516BF0C13C708 "
                  "0000000011223344 53070A3C230C1410019000");
    /* Read Records */
    addHexCommand(
        "00B201A420",
        "00000000000000000000000000000000000000000000000000000000000000009000");
    /* Open Secure Session V3.1 */
    addHexCommand("008A0BD104C1C2C3C400",
                  "03082ED700300E300102030405060708090A0B0C0D0E0F10111213141516"
                  "1718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F309000");
    /* Read Records */
    addHexCommand(
        "00B201A420",
        "00000000000000000000000000000000000000000000000000000000000000009000");
    /* Read Records */
    addHexCommand("00B201D430",
                  "0102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E"
                  "1F202122232425262728292A2B2C2D2E2F309000");
    /* Read Records */
    addHexCommand(
        "00B201A420",
        "00000000000000000000000000000000000000000000000000000000000000009000");
    /* Read Records */
    addHexCommand("00B201D430",
                  "0102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E"
                  "1F202122232425262728292A2B2C2D2E2F309000");
    /* Close Secure Session */
    /* no ratification asked */
    addHexCommand("008E0000040506070800", "010203049000");
    /* ratification asked */
    addHexCommand("008E8000040506070800", "010203049000");
    /* Ratification */
    addHexCommand("00B2000000", "6B00");
}

std::vector<char> StubHoplink::getATR()
{
    return ByteArrayUtils::fromHex(ATR_HEX);
}

std::string StubHoplink::getSeProcotol()
{
    return seProtocol;
}
}
}
}
}
}
}
