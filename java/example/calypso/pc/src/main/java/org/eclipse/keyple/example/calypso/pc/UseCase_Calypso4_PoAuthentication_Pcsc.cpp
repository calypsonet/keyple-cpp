#include "CalypsoClassicInfo.h"
#include "CalypsoUtilities.h"
#include "KeypleBaseException.h"
#include "ReaderUtilities.h"
#include "KeypleReaderNotFoundException.h"
#include "Logger.h"
#include "LoggerFactory.h"
#include "MatchingSelection.h"
#include "ObservableReader.h"
#include "PcscPlugin.h"
#include "PcscReader.h"
#include "PcscReadersSettings.h"
#include "PcscReaderSettings_Import.h"
#include "PcscReadersSettings.h"
#include "PcscProtocolSetting.h"
#include "PcscReadersSettings.h"
#include "PoSelectionRequest.h"
#include "PoTransaction.h"
#include "ReaderEvent_Import.h"
#include "SamResource.h"
#include "SeProxyService.h"
#include "SeReader.h"
#include "SeSelection.h"

/* Common */
#include "ByteArrayUtil.h"
#include "stringhelper.h"

using namespace org::eclipse::keyple::common;
using namespace org::eclipse::keyple::core::seproxy;
using namespace org::eclipse::keyple::core::seproxy::event;
using namespace org::eclipse::keyple::core::seproxy::exception;
using namespace org::eclipse::keyple::core::seproxy::protocol;
using namespace org::eclipse::keyple::example::calypso::common::postructure;
using namespace org::eclipse::keyple::example::calypso::common::transaction;
using namespace org::eclipse::keyple::example::calypso::pc;
using namespace org::eclipse::keyple::example::generic::pc;
using namespace org::eclipse::keyple::plugin::pcsc;

class UseCase_Calypso4_PoAuthentication_Pcsc {
};

const std::shared_ptr<Logger> logger = LoggerFactory::getLogger(typeid(UseCase_Calypso4_PoAuthentication_Pcsc));

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

    /*
     * Get a PO reader ready to work with Calypso PO. Use the getReader helper method from the
     * CalypsoUtilities class.
     */
    std::shared_ptr<SeReader> poReader = CalypsoUtilities::getDefaultPoReader();
    /*
     * Get a SAM reader ready to work with Calypso PO. Use the getReader helper method from the
     * CalypsoUtilities class.
     */
    std::shared_ptr<SamResource> samResource = CalypsoUtilities::getDefaultSamResource();

    /* Check if the readers exists */
    if (poReader == nullptr || samResource == nullptr) {
        throw std::make_shared<IllegalStateException>("Bad PO or SAM reader setup");
    }

    logger->info("=============== UseCase Calypso #4: Po Authentication ==================\n");
    logger->info("= PO Reader  NAME = %s\n", poReader->getName());
    logger->info("= SAM Reader  NAME = %s\n", samResource->getSeReader()->getName());

    /* Check if a PO is present in the reader */
    if (poReader->isSePresent()) {

        logger->info("==================================================================================\n");
        logger->info("= 1st PO exchange: AID based selection with reading of Environment file.         =\n");
        logger->info("==================================================================================\n");

        /*
         * Prepare a Calypso PO selection
         */
        std::shared_ptr<SeSelection> seSelection = std::make_shared<SeSelection>();

        /*
         * Setting of an AID based selection of a Calypso REV3 PO
         *
         * Select the first application matching the selection AID whatever the SE communication
         * protocol keep the logical channel open after the selection
         */

        /*
         * Calypso selection: configures a PoSelector with all the desired attributes to make
         * the selection and read additional information afterwards
         */
        std::shared_ptr<PoSelectionRequest> poSelectionRequest =
            std::make_shared<PoSelectionRequest>(
                std::make_shared<PoSelector>(SeCommonProtocols::PROTOCOL_ISO14443_4, nullptr,
                    std::make_shared<PoSelector::PoAidSelector>(
                        std::make_shared<SeSelector::AidSelector::IsoAid>(CalypsoClassicInfo::AID),
                        PoSelector::InvalidatedPo::REJECT),
                    StringHelper::formatSimple("AID: %s", CalypsoClassicInfo::AID)),
                ChannelState::KEEP_OPEN);


        /*
         * Add the selection case to the current selection (we could have added other cases
         * here)
         */
        seSelection->prepareSelection(poSelectionRequest);

        /*
         * Actual PO communication: operate through a single request the Calypso PO selection
         * and the file read
         */
        std::shared_ptr<SelectionsResult> selectionResult = seSelection->processExplicitSelection(poReader);

        if (selectionResult->hasActiveSelection()) {
            std::shared_ptr<MatchingSelection> matchingSelection = selectionResult->getActiveSelection();

            std::shared_ptr<CalypsoPo> calypsoPo = std::static_pointer_cast<CalypsoPo>(matchingSelection->getMatchingSe());
            logger->info("The selection of the PO has succeeded\n");


            /* Go on with the reading of the first record of the EventLog file */
            logger->info("==================================================================================\n");
            logger->info("= 2nd PO exchange: open and close a secure session to perform authentication.    =\n");
            logger->info("==================================================================================\n");

            std::shared_ptr<PoTransaction> poTransaction =
                            std::make_shared<PoTransaction>(std::make_shared<PoResource>(poReader, calypsoPo), samResource,
                                                            CalypsoUtilities::getSecuritySettings());

            /*
             * Prepare the reading order and keep the associated parser for later use once the
             * transaction has been processed.
             */
            int readEventLogParserIndex =
                poTransaction->prepareReadRecordsCmd(CalypsoClassicInfo::SFI_EventLog, ReadDataStructure::SINGLE_RECORD_DATA,
                                                     CalypsoClassicInfo::RECORD_NUMBER_1,
                                                     StringHelper::formatSimple("EventLog (SFI=%02X, recnbr=%d))",
                                                                                CalypsoClassicInfo::SFI_EventLog,
                                                                                CalypsoClassicInfo::RECORD_NUMBER_1));

            (void)readEventLogParserIndex;

            /*
             * Open Session for the debit key
             */
            bool poProcessStatus = poTransaction->processOpening(PoTransaction::ModificationMode::ATOMIC,
                                                                 PoTransaction::SessionAccessLevel::SESSION_LVL_DEBIT,
                                                                 static_cast<char>(0), static_cast<char>(0));

            if (!poProcessStatus) {
                throw IllegalStateException("processingOpening failure.");
            }

            if (!poTransaction->wasRatified()) {
                logger->info("========= Previous Secure Session was not ratified. =====================\n");
            }
            /*
             * Prepare the reading order and keep the associated parser for later use once the
             * transaction has been processed.
             */
            int readEventLogParserIndexBis =
                poTransaction->prepareReadRecordsCmd(CalypsoClassicInfo::SFI_EventLog, ReadDataStructure::SINGLE_RECORD_DATA,
                                                     CalypsoClassicInfo::RECORD_NUMBER_1,
                                                     StringHelper::formatSimple("EventLog (SFI=%02X, recnbr=%d))",
                                                                                CalypsoClassicInfo::SFI_EventLog,
                                                                                CalypsoClassicInfo::RECORD_NUMBER_1));

            poProcessStatus = poTransaction->processPoCommandsInSession();

            /*
             * Retrieve the data read from the parser updated during the transaction process
             */
            std::shared_ptr<ReadRecordsRespPars> parser =
                std::dynamic_pointer_cast<ReadRecordsRespPars>(poTransaction->getResponseParser(readEventLogParserIndexBis));
            std::vector<char> eventLog = (*(parser->getRecords().get()))[CalypsoClassicInfo::RECORD_NUMBER_1];


            /* Log the result */
            logger->info("EventLog file data: %s\n", ByteArrayUtil::toHex(eventLog));

            if (!poProcessStatus) {
                throw std::make_shared<IllegalStateException>("processPoCommandsInSession failure.");
            }

            /*
             * Close the Secure Session.
             */
            logger->info("========= PO Calypso session ======= Closing ============================\n");

            /*
             * A ratification command will be sent (CONTACTLESS_MODE).
             */
            poProcessStatus = poTransaction->processClosing(ChannelState::CLOSE_AFTER);

            if (!poProcessStatus) {
                throw std::make_shared<IllegalStateException>("processClosing failure.");
            }

            logger->info("==================================================================================\n");
            logger->info("= End of the Calypso PO processing.                                              =\n");
            logger->info("==================================================================================\n");
        }
        else {
            logger->error("The selection of the PO has failed\n");
        }
    }
    else {
        logger->error("No PO were detected\n");
    }
    exit(0);
}
