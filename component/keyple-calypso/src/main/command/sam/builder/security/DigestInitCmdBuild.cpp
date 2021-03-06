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

#include "DigestInitCmdBuild.h"

#include "System.h"

namespace keyple {
namespace calypso {
namespace command {
namespace sam {
namespace builder {
namespace security {

using namespace keyple::calypso::command::sam;

DigestInitCmdBuild::DigestInitCmdBuild(SamRevision revision,
                                       bool verificationMode, bool rev3_2Mode,
                                       uint8_t workKeyRecordNumber,
                                       uint8_t workKeyKif, uint8_t workKeyKVC,
                                       std::vector<uint8_t>& digestData)
: AbstractSamCommandBuilder(CalypsoSamCommands::DIGEST_INIT, nullptr)
{
    this->defaultRevision = revision;

    if (workKeyRecordNumber == 0x00 &&
        (workKeyKif == 0x00 || workKeyKVC == 0x00)) {
        throw std::invalid_argument("Bad key record number, kif or kvc!");
    }

    if (digestData.empty()) {
        throw std::invalid_argument("Digest data is null!");
    }

    uint8_t cla = SamRevision::S1D == (this->defaultRevision) ? 0x94 : 0x80;
    uint8_t p1  = 0x00;

    if (verificationMode) {
        p1 += 1;
    }

    if (rev3_2Mode) {
        p1 += 2;
    }

    uint8_t p2 = 0xFF;
    if (workKeyKif == 0xFF) {
        p2 = workKeyRecordNumber;
    }

    std::vector<uint8_t> dataIn;

    if (p2 == 0xFF) {
        dataIn    = std::vector<uint8_t>(2 + digestData.size());
        dataIn[0] = workKeyKif;
        dataIn[1] = workKeyKVC;
        System::arraycopy(digestData, 0, dataIn, 2, digestData.size());
    } else {
        dataIn.clear();
    }

    /*
     * CalypsoRequest calypsoRequest =
     *     new CalypsoRequest(cla, CalypsoCommands.SAM_DIGEST_INIT, p1, p2,
     *                        dataIn);
     */
    request = setApduRequest(cla, command, p1, p2, dataIn);
}

}
}
}
}
}
}
