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
#include <vector>
#include <limits>
#include <stdexcept>
#include <memory>

/* Common */
#include "Export.h"
#include "Object.h"
#include "Serializable.h"
#include "stringhelper.h"
#include "Logger.h"
#include "LoggerFactory.h"

namespace org {
namespace eclipse {
namespace keyple {
namespace core {
namespace seproxy {
namespace message {

/**
    * Single APDU response wrapper
    */
class EXPORT ApduResponse : public std::enable_shared_from_this<ApduResponse>, public Serializable, public Object {

    using Logger = org::eclipse::keyple::common::Logger;
    using LoggerFactory = org::eclipse::keyple::common::LoggerFactory;

public:
    static constexpr long long serialVersionUID = 6418469841122636812LL;

    /***
        * the success result of the processed APDU command to allow chaining responses in a group of
        * APDUs
        */
private:
    bool successful;

    /*
        *
        */
    const std::shared_ptr<Logger> logger = LoggerFactory::getLogger(typeid(ApduResponse));

    /**
        * apdu response data buffer (including sw1sw2)
        */
    std::vector<char> const bytes;


    /**
        * Create a new ApduResponse from the provided byte array
        *
        * The internal successful status is determined by the current status code and the optional
        * successful status codes list.
        *
        * The list of additional successful status codes is used to set the successful flag if not
        * equal to 0x9000
        *
        * @param buffer apdu response data buffer (including sw1sw2)
        * @param successfulStatusCodes optional list of successful status codes other than 0x9000
        */
public:
    ApduResponse(std::vector<char> &buffer, std::shared_ptr<std::set<int>> successfulStatusCodes);

    virtual ~ApduResponse() { }

    /**
        * Checks if is successful.
        *
        * @return the status of the command transmission.
        */
    bool isSuccessful();

    int getStatusCode();

    std::vector<char> getBytes() const;

    /**
        * Get the data before the statusCode
        *
        * @return slice of the buffer before the status code
        */
    std::vector<char> getDataOut();

    std::string toString() override;

    bool equals(std::shared_ptr<void> o) override;

    int hashCode() override;

    friend std::ostream &operator<<(std::ostream &os, const ApduResponse &r)
    {
        os << std::string("r-apdu: ");
        const std::vector<char> b = r.getBytes();
        for (int i = 0; i < (int)b.size(); i++)
            os << StringHelper::formatSimple("%02x ", b[i]);
        return os;
    }

protected:
    void finalize() override;
};

}
}
}
}
}
}