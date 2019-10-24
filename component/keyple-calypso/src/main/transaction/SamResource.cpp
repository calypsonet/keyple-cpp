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

#include "SamResource.h"
#include "CalypsoSam.h"
#include "SeReader.h"

namespace keyple {
namespace calypso {
namespace transaction {

using namespace keyple::core::seproxy;
using namespace keyple::core::selection;

SamResource::SamResource(std::shared_ptr<SeReader> seReader,
                         std::shared_ptr<CalypsoSam> calypsoSam)
: SeResource<CalypsoSam>(seReader, calypsoSam)
{
}

}
}
}
