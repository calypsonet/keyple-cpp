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

#include "ByteArrayUtil.h"
#include "CalypsoClassicInfo.h"
#include "CalypsoClassicTransactionEngine.h"
#include "KeypleReaderNotFoundException.h"
#include "LoggerFactory.h"
#include "MatchingSelection.h"
#include "ObservableReader.h"
#include "PoSelectionRequest.h"
#include "PoSelector.h"
#include "ReaderPlugin.h"
#include "ReadRecordsRespPars.h"
#include "SeCommonProtocols.h"
#include "SeProxyService.h"
#include "StubCalypsoClassic.h"
#include "StubSamCalypsoClassic.h"
#include "StubProtocolSetting.h"
#include "StubPlugin.h"
#include "StubPluginFactory.h"
#include "StubReader.h"

using namespace keyple::example::calypso::common::transaction;
using namespace keyple::example::calypso::common::postructure;
using namespace keyple::example::calypso::pc::stub::se;
using namespace keyple::plugin::stub;
using namespace keyple::core::seproxy;
using namespace keyple::core::seproxy::event;
using namespace keyple::core::seproxy::exception;
using namespace keyple::core::seproxy::protocol;

class UseCase_Calypso1_ExplicitSelectionAid_Stub {
};

std::shared_ptr<Logger> logger = LoggerFactory::getLogger(
    typeid(UseCase_Calypso1_ExplicitSelectionAid_Stub));

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    /* Get the instance of the SeProxyService (Singleton pattern) */
    SeProxyService& seProxyService = SeProxyService::getInstance();

    const std::string STUB_PLUGIN_NAME = "stub1";

    /* Register Stub plugin in the platform */
    seProxyService.registerPlugin(new StubPluginFactory(STUB_PLUGIN_NAME));
    ReaderPlugin* stubPlugin = seProxyService.getPlugin(STUB_PLUGIN_NAME);

    /* Plug the PO stub reader */
    dynamic_cast<StubPlugin*>(stubPlugin)->plugStubReader("poReader", true);

    /*
     * Get a PO reader ready to work with Calypso PO.
     */
    std::shared_ptr<StubReader> poReader =
        std::dynamic_pointer_cast<StubReader>(
            stubPlugin->getReader("poReader"));

    /* Check if the reader exists */
    if (poReader == nullptr) {
        throw std::make_shared<IllegalStateException>("Bad PO reader setup");
    }

    poReader->addSeProtocolSetting(
        SeCommonProtocols::PROTOCOL_ISO14443_4,
        StubProtocolSetting::STUB_PROTOCOL_SETTING
            [SeCommonProtocols::PROTOCOL_ISO14443_4]);

    /* Create 'virtual' Calypso PO */
    std::shared_ptr<StubSecureElement> calypsoStubSe =
        std::make_shared<StubCalypsoClassic>();

    logger->info("Insert stub PO\n");
    poReader->insertSe(calypsoStubSe);

    logger->info("=============== UseCase Calypso #1: AID based explicit "
                 "selection ==================\n");
    logger->info("= PO Reader  NAME = %\n", poReader->getName());

    /* Check if a PO is present in the reader */
    if (poReader->isSePresent()) {

        logger->info("======================================================="
                     "===========================\n");
        logger->info("= 1st PO exchange: AID based selection with reading of "
                     "Environment file.          =\n");
        logger->info("======================================================="
                     "===========================\n");

        /*
         * Prepare a Calypso PO selection
         */
        std::shared_ptr<SeSelection> seSelection =
            std::make_shared<SeSelection>();

        /*
         * Calypso selection: configures a PoSelector with all the desired
         * attributes to make the selection and read additional information
         * afterwards
         */
        std::shared_ptr<PoSelectionRequest> poSelectionRequest =
            std::make_shared<PoSelectionRequest>(
                std::make_shared<PoSelector>(
                    SeCommonProtocols::PROTOCOL_ISO14443_4, nullptr,
                    std::make_shared<PoSelector::PoAidSelector>(
                        std::make_shared<SeSelector::AidSelector::IsoAid>(
                            CalypsoClassicInfo::AID),
                        PoSelector::InvalidatedPo::REJECT),
                    StringHelper::formatSimple("AID: %s",
                                               CalypsoClassicInfo::AID)));

        /*
         * Prepare the reading order and keep the associated parser for later
         * use once the selection has been made.
         */
        int readEnvironmentParserIndex =
            poSelectionRequest->prepareReadRecordsCmd(
                CalypsoClassicInfo::SFI_EnvironmentAndHolder,
                ReadDataStructure::SINGLE_RECORD_DATA,
                CalypsoClassicInfo::RECORD_NUMBER_1,
                StringHelper::formatSimple(
                    "EnvironmentAndHolder (SFI=%02X)",
                    CalypsoClassicInfo::SFI_EnvironmentAndHolder));

        /*
         * Add the selection case to the current selection (we could have added
         * other cases here)
         *
         * Ignore the returned index since we have only one selection here.
         */
        seSelection->prepareSelection(poSelectionRequest);

        /*
         * Actual PO communication: operate through a single request the Calypso
         * PO selection and the file read
         */
        std::shared_ptr<SelectionsResult> selectionResult =
            seSelection->processExplicitSelection(poReader);

        if (selectionResult->hasActiveSelection()) {
            std::shared_ptr<MatchingSelection> matchingSelection =
                selectionResult->getActiveSelection();

            std::shared_ptr<CalypsoPo> calypsoPo =
                std::static_pointer_cast<CalypsoPo>(
                    matchingSelection->getMatchingSe());
            logger->info("The selection of the PO has succeeded\n");

            /*
             * Retrieve the data read from the parser updated during the
             * selection process
             */
            std::shared_ptr<ReadRecordsRespPars> readEnvironmentParser =
                std::dynamic_pointer_cast<ReadRecordsRespPars>(
                    matchingSelection->getResponseParser(
                        readEnvironmentParserIndex));

            std::vector<uint8_t> environmentAndHolder =
                (*(readEnvironmentParser->getRecords().get()))[static_cast<int>(
                    CalypsoClassicInfo::RECORD_NUMBER_1)];

            /* Log the result */
            logger->info("Environment file data: %\n", environmentAndHolder);

            /*
             * Go on with the reading of the first record of the EventLog file
             */
            logger->info("==================================================="
                         "===============================\n");
            logger->info("= 2nd PO exchange: reading transaction of the "
                         "EventLog file.                     =\n");
            logger->info("==================================================="
                         "===============================\n");

            std::shared_ptr<PoTransaction> poTransaction =
                std::make_shared<PoTransaction>(
                    std::make_shared<PoResource>(poReader, calypsoPo));

            /*
             * Prepare the reading order and keep the associated parser for
             * later use once the transaction has been processed.
             */
            int readEventLogParserIndex = poTransaction->prepareReadRecordsCmd(
                CalypsoClassicInfo::SFI_EventLog,
                ReadDataStructure::SINGLE_RECORD_DATA,
                CalypsoClassicInfo::RECORD_NUMBER_1,
                StringHelper::formatSimple(
                    "EventLog (SFI=%02X, recnbr=%d))",
                    CalypsoClassicInfo::SFI_EventLog,
                    CalypsoClassicInfo::RECORD_NUMBER_1));

            /*
             * Actual PO communication: send the prepared read order, then close
             * the channel with the PO
             */
            if (poTransaction->processPoCommands(ChannelControl::CLOSE_AFTER)) {
                logger->info("The reading of the EventLog has succeeded\n");

                /*
                 * Retrieve the data read from the parser updated during the
                 * transaction process
                 */
                std::shared_ptr<ReadRecordsRespPars> parser =
                    std::dynamic_pointer_cast<ReadRecordsRespPars>(
                        poTransaction->getResponseParser(
                            readEventLogParserIndex));
                std::vector<uint8_t> eventLog =
                    (*(parser->getRecords()
                           .get()))[CalypsoClassicInfo::RECORD_NUMBER_1];

                /* Log the result */
                logger->info("EventLog file data: %\n", eventLog);
            }
            logger->info("==================================================="
                         "===============================\n");
            logger->info("= End of the Calypso PO processing.                "
                         "                              =\n");
            logger->info("==================================================="
                         "===============================\n");
        } else {
            logger->error("The selection of the PO has failed\n");
        }
    } else {
        logger->error("No PO were detected\n");
    }

    logger->info("Remove stub PO\n");
    poReader->removeSe();

    return 0;
}
