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

#include "KeypleBaseException.h"
#include "SeProxyService.h"
#include "PcscPlugin.h"
#include "CalypsoClassicTransactionEngine.h"
#include "SeReader.h"
#include "PcscReadersSettings.h"
#include "ReaderUtilities.h"
#include "KeypleReaderNotFoundException.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "PcscReader_Import.h"
#include "PcscReaderSettings_Import.h"
#include "PcscReadersSettings.h"
#include "PcscProtocolSetting_Import.h"
#include "PcscReadersSettings.h"
#include "ObservableReader_Import.h"

using namespace keyple::common;
using namespace keyple::core::seproxy;
using namespace keyple::core::seproxy::event;
using namespace keyple::core::seproxy::exception;
using namespace keyple::core::seproxy::protocol;
using namespace keyple::example::calypso::common::transaction;
using namespace keyple::example::calypso::pc;
using namespace keyple::example::generic::pc;
using namespace keyple::plugin::pcsc;

class Demo_CalypsoClassic_Pcsc {
};

std::shared_ptr<Logger> logger = LoggerFactory::getLogger(typeid(Demo_CalypsoClassic_Pcsc));

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

     /* Get the instance of the PC/SC plugin */
    PcscPlugin pcscPlugin = PcscPlugin::getInstance();
    pcscPlugin.initReaders();
    std::shared_ptr<PcscPlugin> shared_plugin = std::shared_ptr<PcscPlugin>(&pcscPlugin);

    /* Assign PcscPlugin to the SeProxyService */
    SeProxyService& seProxyService = SeProxyService::getInstance();
    seProxyService.addPlugin(shared_plugin);

    /* Setting up the transaction engine (implements Observer) */
    std::shared_ptr<CalypsoClassicTransactionEngine> transactionEngine = std::make_shared<CalypsoClassicTransactionEngine>();

    /*
     * Get PO and SAM readers. Apply regulars expressions to reader names to select PO / SAM
     * readers. Use the getReader helper method from the transaction engine.
     */
    std::shared_ptr<SeReader> poReader = nullptr, samReader = nullptr;
    try {
        poReader = ReaderUtilities::getReaderByName(PcscReadersSettings::PO_READER_NAME_REGEX);
        samReader = ReaderUtilities::getReaderByName(PcscReadersSettings::SAM_READER_NAME_REGEX);
    }
    catch (const KeypleReaderNotFoundException &e) {
        logger->error("update - caught KeypleReaderNotFoundException " \
                      "(msg: %s, cause: %s)\n", e.getMessage().c_str(),
                      e.getCause().what());
    }

    /* Both readers are expected not null */
    if (poReader == samReader || poReader == nullptr || samReader == nullptr) {
        throw std::make_shared<IllegalStateException>("Bad PO/SAM setup");
    }

    logger->info("PO Reader  NAME = %s\n", poReader->getName().c_str());
    logger->info("SAM Reader  NAME = %s\n", samReader->getName().c_str());

    /* Set PcSc settings per reader */
    poReader->setParameter(PcscReaderSettings::SETTING_KEY_LOGGING, "true");
    poReader->setParameter(PcscReaderSettings::SETTING_KEY_PROTOCOL, PcscReaderSettings::SETTING_PROTOCOL_T1);
    samReader->setParameter(PcscReaderSettings::SETTING_KEY_LOGGING, "true");
    samReader->setParameter(PcscReaderSettings::SETTING_KEY_PROTOCOL, PcscReaderSettings::SETTING_PROTOCOL_T0);

    /*
     * PC/SC card access mode:
     *
     * The SAM is left in the SHARED mode (by default) to avoid automatic resets due to the
     * limited time between two consecutive exchanges granted by Windows.
     *
     * This point will be addressed in a coming release of the Keyple PcSc reader plugin.
     *
     * The PO reader is set to EXCLUSIVE mode to avoid side effects (on OS Windows 8+) during
     * the selection step that may result in session failures.
     *
     * See KEYPLE-CORE.PC.md file to learn more about this point.
     *
     */
    samReader->setParameter(PcscReader::SETTING_KEY_MODE, PcscReader::SETTING_MODE_SHARED);
    poReader->setParameter(PcscReader::SETTING_KEY_MODE, PcscReader::SETTING_MODE_SHARED);

    /* Set the PO reader protocol flag */
    poReader->addSeProtocolSetting(SeCommonProtocols::PROTOCOL_ISO14443_4,
                                   PcscProtocolSetting::PCSC_PROTOCOL_SETTING[SeCommonProtocols::PROTOCOL_ISO14443_4]);
    poReader->addSeProtocolSetting(SeCommonProtocols::PROTOCOL_B_PRIME,
                                   PcscProtocolSetting::PCSC_PROTOCOL_SETTING[SeCommonProtocols::PROTOCOL_B_PRIME]);
    poReader->addSeProtocolSetting(SeCommonProtocols::PROTOCOL_ISO7816_3,
                                   PcscProtocolSetting::PCSC_PROTOCOL_SETTING[SeCommonProtocols::PROTOCOL_ISO7816_3]);

    /* Assign the readers to the Calypso transaction engine */
    transactionEngine->setReaders(poReader, samReader);

    /* Set the default selection operation */
    (std::dynamic_pointer_cast<ObservableReader>(poReader))->setDefaultSelectionRequest(transactionEngine->preparePoSelection(),
                                                                                       ObservableReader::NotificationMode::MATCHED_ONLY);

    /* Set terminal as Observer of the first reader */
    (std::dynamic_pointer_cast<ObservableReader>(poReader))->addObserver(transactionEngine);

    while(1);
}
