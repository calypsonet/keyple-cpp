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

/* Core */
#include "AbstractObservableLocalReader.h"
#include "AbstractReader.h"
#include "KeypleBaseException.h"
#include "ObservableReader.h"
#include "SeProtocol.h"
#include "SeProxyService.h"
#include "SeReader.h"

/* Plugin */
#include "PcscPlugin.h"
#include "PcscPluginFactory.h"
#include "PcscReader.h"
#include "PcscProtocolSetting.h"

/* Example */
#include "ReaderUtilities.h"
#include "SeProtocolDetectionEngine.h"
#include "PcscReadersSettings.h"

using namespace keyple::core::seproxy;
using namespace keyple::core::seproxy::event;
using namespace keyple::core::seproxy::exception;
using namespace keyple::core::seproxy::plugin;
using namespace keyple::core::seproxy::plugin::local;
using namespace keyple::core::seproxy::protocol;
using namespace keyple::example::generic::common;
using namespace keyple::example::generic::pc;
using namespace keyple::plugin::pcsc;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    /* get the SeProxyService instance */
    SeProxyService& seProxyService = SeProxyService::getInstance();

    /* Assign PcscPlugin to the SeProxyService */
    seProxyService.registerPlugin(new PcscPluginFactory());

    /* attempt to get the SeReader (the right reader should be ready here) */
    std::shared_ptr<SeReader> poReader = ReaderUtilities::getReaderByName(
        PcscReadersSettings::PO_READER_NAME_REGEX);

    if (poReader == nullptr) {
        throw IllegalStateException("Bad PO/SAM setup");
    }

    std::cout << "PO Reader : " << poReader->getName() << std::endl;

    /* create an observer class to handle the SE operations */
    std::shared_ptr<SeProtocolDetectionEngine> observer =
        std::make_shared<SeProtocolDetectionEngine>();

    observer->setReader(poReader);

    /* configure reader */
    poReader->setParameter(PcscReader::SETTING_KEY_PROTOCOL,
                           PcscReader::SETTING_PROTOCOL_T1);

    /*
     * Protocol detection settings.
     * add 8 expected protocols with three different methods:
     * - using a custom enum
     * - addinf protocols individually
     * A real application should use only one method.
     */

    /*
     * Method 1
     * add several settings at once with settings an unordered_set
     */
    std::set<SeCommonProtocols> commonProtocols{
        SeCommonProtocols::PROTOCOL_MIFARE_CLASSIC,
        SeCommonProtocols::PROTOCOL_MIFARE_UL};
    std::map<SeProtocol, std::string> map;
    std::map<SeCommonProtocols, std::string> specificSettings =
        PcscProtocolSetting::getSpecificSettings(commonProtocols);

    for (auto pair : specificSettings)
        map.insert(std::pair<SeProtocol, std::string>(pair.first, pair.second));

    poReader->setSeProtocolSetting(map);

    /*
     * Method 2
     * add all settings at once with setting enum
     */
    poReader->addSeProtocolSetting(
        SeCommonProtocols::PROTOCOL_MEMORY_ST25,
        PcscProtocolSetting::PCSC_PROTOCOL_SETTING
            [SeCommonProtocols::PROTOCOL_MEMORY_ST25]);

    /* Regex extended */
    poReader->addSeProtocolSetting(
        SeCommonProtocols::PROTOCOL_ISO14443_4,
        PcscProtocolSetting::PCSC_PROTOCOL_SETTING
                [SeCommonProtocols::PROTOCOL_ISO14443_4] +
            "|3B8D.*");

    /* Set terminal as Observer of the first reader */
    (std::dynamic_pointer_cast<AbstractReader>(poReader))
        ->addObserver(observer);

    /* Set Default selection */
    (std::dynamic_pointer_cast<AbstractObservableLocalReader>(poReader))
        ->setDefaultSelectionRequest(observer->prepareSeSelection(),
                                     ObservableReader::NotificationMode::ALWAYS,
                                     ObservableReader::PollingMode::REPEATING);

    /* Wait for Enter key to exit */
    std::cout << "Press Enter to exit" << std::endl;

    while (true) {
        char c = 0;
        try {
            std::string input = "";
            getline(std::cin, input);
            if (input.length())
                c = input[0];

        } catch (const IOException& e) {
            (void)e;
            //e.printStackTrace();
        }
        if (c == 0x0A) {
            std::cout << "Exiting..." << std::endl;
            exit(0);
        }
    }
}
