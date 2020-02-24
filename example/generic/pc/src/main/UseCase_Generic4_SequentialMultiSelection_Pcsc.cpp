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

#include "AbstractMatchingSe.h"
#include "ApduResponse.h"
#include "ByteArrayUtil.h"
#include "ChannelState.h"
#include "GenericSeSelectionRequest.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "KeypleBaseException.h"
#include "KeypleReaderException.h"
#include "Matcher.h"
#include "MatchingSelection.h"
#include "PcscPlugin.h"
#include "ReaderUtilities.h"
#include "SeCommonProtocols_Import.h"
#include "SelectionStatus.h"
#include "SeProtocol_Import.h"
#include "SeProxyService.h"
#include "SeReader.h"
#include "SeResponse.h"
#include "SeSelector_Import.h"
#include "SeSelection.h"

using namespace keyple::common;
using namespace keyple::core::selection;
using namespace keyple::core::seproxy;
using namespace keyple::core::seproxy::exception;
using namespace keyple::core::seproxy::message;
using namespace keyple::core::seproxy::protocol;
using namespace keyple::core::util;
using namespace keyple::plugin::pcsc;
using namespace keyple::example::generic::common;
using namespace keyple::example::generic::pc;

class UseCase_Generic4_SequentialMultiSelection_Pcsc {
};

const std::shared_ptr<Logger> logger = LoggerFactory::getLogger(
    typeid(UseCase_Generic4_SequentialMultiSelection_Pcsc));

void doAndAnalyseSelection(std::shared_ptr<SeReader> seReader,
                           std::shared_ptr<SeSelection> seSelection, int index)
{
    std::shared_ptr<SelectionsResult> selectionsResult =
        seSelection->processExplicitSelection(seReader);
    if (selectionsResult->hasActiveSelection()) {
        std::shared_ptr<AbstractMatchingSe> matchingSe =
            selectionsResult->getMatchingSelection(index)->getMatchingSe();
        logger->info("The SE matched the selection %d.", index);
        logger->info(
            "Selection status for case %d: \n\t\tATR: "
            "%s\n\t\tFCI: %s\n",
            index,
            ByteArrayUtil::toHex(
                matchingSe->getSelectionStatus()->getAtr()->getBytes())
                .c_str(),
            ByteArrayUtil::toHex(
                matchingSe->getSelectionStatus()->getFci()->getDataOut())
                .c_str());
    } else {
        logger->info(
            "The selection 2 process did not return any selected SE\n");
    }
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    /* Get the instance of the PC/SC plugin */
    PcscPlugin pcscplugin = PcscPlugin::getInstance();
    pcscplugin.initReaders();

    /* Assign PcscPlugin to the SeProxyService */
    SeProxyService& seProxyService = SeProxyService::getInstance();
    seProxyService.addPlugin(std::make_shared<PcscPlugin>(pcscplugin));

    /*
     * Get a SE reader ready to work with contactless SE. Use the getReader helper method from
     * the ReaderUtilities class.
     */
    std::shared_ptr<SeReader> seReader =
        ReaderUtilities::getDefaultContactLessSeReader();

    /* Check if the reader exists */
    if (seReader == nullptr) {
        throw std::make_shared<IllegalStateException>("Bad SE reader setup");
    }

    logger->info("=============== UseCase Generic #4: AID based sequential "
                 "explicit multiple selection ==================\n");
    logger->info("= SE Reader  NAME = %s\n", seReader->getName().c_str());

    std::shared_ptr<AbstractMatchingSe> matchingSe;

    /* Check if a SE is present in the reader */
    if (seReader->isSePresent()) {

        std::shared_ptr<SeSelection> seSelection =
            std::make_shared<SeSelection>();

        /* operate SE selection (change the AID here to adapt it to the SE used for the test) */
        //std::string seAidPrefix = "A000000404012509";
        std::string seAidPrefix = "304554502E494341";

        /* AID based selection */
        {
            std::vector<uint8_t> aid = ByteArrayUtil::fromHex(seAidPrefix);
            std::shared_ptr<SeSelector::AidSelector::IsoAid> isoAid =
                std::make_shared<SeSelector::AidSelector::IsoAid>(aid);
            std::shared_ptr<SeSelector::AidSelector> aidSelector =
                std::make_shared<SeSelector::AidSelector>(
                    isoAid, nullptr,
                    SeSelector::AidSelector::FileOccurrence::FIRST,
                    SeSelector::AidSelector::FileControlInformation::FCI);
            std::shared_ptr<SeSelector> seSelector =
                std::make_shared<SeSelector>(
                    SeCommonProtocols::PROTOCOL_ISO14443_4, nullptr,
                    aidSelector, "Initial selection #1");
            std::shared_ptr<GenericSeSelectionRequest>
                genericSeSelectionRequest =
                    std::make_shared<GenericSeSelectionRequest>(
                        seSelector, ChannelState::KEEP_OPEN);
            seSelection->prepareSelection(genericSeSelectionRequest);
            doAndAnalyseSelection(seReader, seSelection, 1);
        }

        /* next selection (2nd selection, later indexed 1) */
        {
            std::vector<uint8_t> aid = ByteArrayUtil::fromHex(seAidPrefix);
            std::shared_ptr<SeSelector::AidSelector::IsoAid> isoAid =
                std::make_shared<SeSelector::AidSelector::IsoAid>(aid);
            std::shared_ptr<SeSelector::AidSelector> aidSelector =
                std::make_shared<SeSelector::AidSelector>(
                    isoAid, nullptr,
                    SeSelector::AidSelector::FileOccurrence::NEXT,
                    SeSelector::AidSelector::FileControlInformation::FCI);
            std::shared_ptr<SeSelector> seSelector =
                std::make_shared<SeSelector>(
                    SeCommonProtocols::PROTOCOL_ISO14443_4, nullptr,
                    aidSelector, "Initial selection #2");
            std::shared_ptr<GenericSeSelectionRequest>
                genericSeSelectionRequest =
                    std::make_shared<GenericSeSelectionRequest>(
                        seSelector, ChannelState::KEEP_OPEN);
            seSelection->prepareSelection(genericSeSelectionRequest);
            doAndAnalyseSelection(seReader, seSelection, 2);
        }

        /* next selection */
        {
            std::vector<uint8_t> aid = ByteArrayUtil::fromHex(seAidPrefix);
            std::shared_ptr<SeSelector::AidSelector::IsoAid> isoAid =
                std::make_shared<SeSelector::AidSelector::IsoAid>(aid);
            std::shared_ptr<SeSelector::AidSelector> aidSelector =
                std::make_shared<SeSelector::AidSelector>(
                    isoAid, nullptr,
                    SeSelector::AidSelector::FileOccurrence::NEXT,
                    SeSelector::AidSelector::FileControlInformation::FCI);
            std::shared_ptr<SeSelector> seSelector =
                std::make_shared<SeSelector>(
                    SeCommonProtocols::PROTOCOL_ISO14443_4, nullptr,
                    aidSelector, "Initial selection #3");
            std::shared_ptr<GenericSeSelectionRequest>
                genericSeSelectionRequest =
                    std::make_shared<GenericSeSelectionRequest>(
                        seSelector, ChannelState::CLOSE_AFTER);
            seSelection->prepareSelection(genericSeSelectionRequest);
            doAndAnalyseSelection(seReader, seSelection, 3);
        }

    } else {
        logger->error("No SE were detected\n");
    }

    return 0;
}
