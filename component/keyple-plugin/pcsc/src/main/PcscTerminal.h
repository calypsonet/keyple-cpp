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

/* Common */
#include "LoggerFactory.h"

/* Plugin */
#include "KeyplePluginPcscExport.h"

/* PC/SC */
#if defined(WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
#include <winscard.h>
#else
#include <PCSC/winscard.h>
#include <PCSC/wintypes.h>
#endif

namespace keyple {
namespace plugin {
namespace pcsc {

using namespace keyple::common;

class KEYPLEPLUGINPCSC_API PcscTerminal {
public:
    /**
     *
     */
    PcscTerminal(const std::string& name);

    /**
     *
     */
    const std::string& getName() const;

    /**
     *
     */
    bool isCardPresent(bool release);

    /**
     *
     */
    bool waitForCardPresent(long long timeout);

    /**
     *
     */
    bool waitForCardAbsent(long long timeout);

    /**
     *
     */
    void openAndConnect(std::string protocol);

    /**
     *
     */
    void closeAndDisconnect(bool reset);

    /**
     *
     */
    static const std::vector<std::string>& listTerminals();

    /**
     *
     */
    const std::vector<uint8_t>& getATR();

    /**
     *
     */
    std::vector<uint8_t> transmitApdu(const std::vector<uint8_t>& apduIn);

    /**
     *
     */
    void beginExclusive();

    /**
     *
     */
    void endExclusive();

	/**
	 *
	 */
	friend std::ostream& operator<<(std::ostream& os, const PcscTerminal& t);

	/**
	 *
	 */
    friend std::ostream& operator<<(std::ostream& os,
                                    const std::vector<PcscTerminal>& vt);

	/**
	 *
	 */
	bool operator==(const PcscTerminal& o) const;

	/**
	 *
	 */
	bool operator!=(const PcscTerminal& o) const;

private:
    /**
     *
     */
    const std::shared_ptr<Logger> logger =
        LoggerFactory::getLogger(typeid(PcscTerminal));

    /**
     *
     */
    SCARDCONTEXT context;

    /**
     *
     */
    SCARDHANDLE handle;

    /**
     *
     */
    DWORD protocol;

    /**
     *
     */
    SCARD_IO_REQUEST pioSendPCI;

    /**
     *
     */
    DWORD state;

    /**
     *
     */
    const std::string name;

    /**
     *
     */
    std::vector<uint8_t> atr;

    /**
     *
     */
    bool contextEstablished;

    /**
     *
     */
    void establishContext();

    /**
     *
     */
    void releaseContext();
};

}
}
}
