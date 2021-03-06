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

#include <set>
#include <string>
#include <map>
#include <memory>

/* Plugin */
#include "KeyplePluginPcscExport.h"

/* Core */
#include "SeCommonProtocols.h"

/* Forward class declarations */
namespace keyple {
namespace core {
namespace seproxy {
namespace protocol {
class SeProtocol;
}
}
}
}

namespace keyple {
namespace plugin {
namespace pcsc {

using namespace keyple::core::seproxy::protocol;

/**
 * This class contains all the parameters to identify the communication
 * protocols supported by PC/SC readers.
 * <p>
 * The application can choose to add all parameters or only a subset.
 * <p>
 * Since they are based on the virtual ATR created by the reader, the protocol
 * identification values are provided as is, they may vary from one reader and
 * SE to another.
 * <p>
 * It may be necessary to create a custom parameter set specific to the context.
*/
class KEYPLEPLUGINPCSC_API PcscProtocolSetting
: public std::enable_shared_from_this<PcscProtocolSetting> {
public:
    /**
     *
     */
    static std::map<SeCommonProtocols, std::string> PCSC_PROTOCOL_SETTING;

    /**
     * Return a subset of the settings map
     *
     * @param specificProtocols subset of protocols
     * @return a settings map
     */
    static std::map<SeCommonProtocols, std::string>
    getSpecificSettings(std::set<SeCommonProtocols>& specificProtocols);

    /**
     * Return the whole settings map
     *
     * @return a settings map
     */
    static std::map<SeCommonProtocols, std::string> getAllSettings();

private:
    /**
     * Associates a protocol and a string defining how to identify it (here a
     * regex to be applied on the ATR)
     */
    class StaticConstructor
    : public std::enable_shared_from_this<StaticConstructor> {
    public:
        StaticConstructor();
    };

    /**
     *
     */
    static PcscProtocolSetting::StaticConstructor staticConstructor;
};

}
}
}
