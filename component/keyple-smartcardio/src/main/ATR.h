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

#include <algorithm>
#include <string>

/* Common */
#include "Arrays.h"
#include "Export.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "Object.h"
#include "stringhelper.h"

namespace keyple {
namespace smartcardio {

using namespace keyple::common;

class EXPORT ATR : public Object {
public:
    /**
     * Constructs an ATR from a byte array.
     *
     * @param atr the byte array containing the answer-to-reset bytes
     * @throws NullPointerException if <code>atr</code> is null
     */
    ATR(std::vector<char> atr);

    /**
     * Returns a copy of the bytes in this ATR.
     *
     * @return a copy of the bytes in this ATR.
     */
    std::vector<char> getBytes();

    /**
     * Returns a copy of the historical bytes in this ATR.
     * If this ATR does not contain historical bytes, an array of length
     * zero is returned.
     *
     * @return a copy of the historical bytes in this ATR.
     */
    std::vector<char> getHistoricalBytes();

    /**
     * Returns a string representation of this ATR.
     *
     * @return a String representation of this ATR.
     */
    std::string toString();

    /**
     * Compares the specified object with this ATR for equality.
     * Returns true if the given object is also an ATR and its bytes are
     * identical to the bytes in this ATR.
     *
     * @param obj the object to be compared for equality with this ATR
     * @return true if the specified object is equal to this ATR
     */
    bool equals(Object& obj);

    /**
     * Returns the hash code value for this ATR.
     *
     * @return the hash code value for this ATR.
     */
    int hashCode();

    /**
     * 
     */
    bool equals(std::shared_ptr<void> o);

protected:
    /**
     * 
     */
    void finalize();

private:
    /**
     * 
     */
    std::vector<char> atr;

    /**
     *
     */
    int startHistorical, nHistorical;
    /**
     *
     */
    void parse();
};

}
}