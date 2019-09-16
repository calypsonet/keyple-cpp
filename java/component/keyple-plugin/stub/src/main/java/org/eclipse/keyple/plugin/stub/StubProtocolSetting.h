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

#include <set>
#include <string>
#include <unordered_map>
#include <memory>

/* Common */
#include "Export.h"

/* Core */
#include "SeCommonProtocols_Import.h"

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace org { namespace eclipse { namespace keyple { namespace core { namespace seproxy { namespace protocol { class SeProtocol; } } } } } }


namespace org {
namespace eclipse {
namespace keyple {
namespace plugin {
namespace stub {

using SeCommonProtocols = org::eclipse::keyple::core::seproxy::protocol::SeCommonProtocols;
using SeProtocol = org::eclipse::keyple::core::seproxy::protocol::SeProtocol;

/**
    * This class contains all the parameters to identify the communication protocols supported by STUB
    * readers.
    * <p>
    * The application can choose to add all parameters or only a subset.
    */
class EXPORT StubProtocolSetting : public std::enable_shared_from_this<StubProtocolSetting> {

public:
    static std::unordered_map<SeCommonProtocols, std::string> STUB_PROTOCOL_SETTING;

    /**
        * Associates a protocol and a string defining how to identify it (here a regex to be applied on
        * the ATR)
        */
private:
    class StaticConstructor : public std::enable_shared_from_this<StaticConstructor> {
    public:
        StaticConstructor();
    };

private:
    static StubProtocolSetting::StaticConstructor staticConstructor;

                        
    /**
        * Return a subset of the settings map
        *
        * @param specificProtocols
        * @return a settings map
        */
public:
    static std::unordered_map<SeCommonProtocols, std::string> getSpecificSettings(std::set<SeCommonProtocols> specificProtocols);

    /**
        * Return the whole settings map
        *
        * @return a settings map
        */
    static std::unordered_map<SeCommonProtocols, std::string> getAllSettings();
};

}
}
}
}
}
