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

#include <ostream>

namespace keyple {
namespace calypso {
namespace command {
namespace po {

/**
 * Calypso revisions
 */
enum class PoRevision {
    /* Default value */
    NO_REV,

    /**
     * Calypso Revision 1 (CLA 0x94)
     */
    REV1_0,

    /**
     * Calypso Revision 2.4 (CLA 0x94)
     */
    REV2_4,

    /**
     * Calypso Revision 3.1 (CLA 0x00)
     */
    REV3_1,

    /**
     * Calypso Revision 3.1 CLAP (CLA 0x00, application type 0x90)
     */
    REV3_1_CLAP,

    /**
     * Calypso Revision 3.2 (CLA 0x00)
     */
    REV3_2
};

std::ostream& operator<<(std::ostream& os, const PoRevision& pr);

}
}
}
}
