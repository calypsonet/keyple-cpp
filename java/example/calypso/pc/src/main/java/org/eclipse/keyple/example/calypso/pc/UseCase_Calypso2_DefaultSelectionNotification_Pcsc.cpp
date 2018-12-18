#include "UseCase_Calypso2_DefaultSelectionNotification_Pcsc.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/SeReader.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/transaction/SeSelection.h"
#include "../../../../../../../../../../../../component/keyple-calypso/src/main/java/org/eclipse/keyple/calypso/command/po/parser/ReadRecordsRespPars.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/exception/KeypleBaseException.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/SeProxyService.h"
#include "../../../../../../../../../../../../component/keyple-plugin/pcsc/src/main/java/org/eclipse/keyple/plugin/pcsc/PcscPlugin.h"
#include "../../../../../../../../../../common/src/main/java/org/eclipse/keyple/example/calypso/common/transaction/CalypsoUtilities.h"
#include "../../../../../../../../../../../../component/keyple-calypso/src/main/java/org/eclipse/keyple/calypso/transaction/PoSelector.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/ChannelState.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/protocol/ContactlessProtocols.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/transaction/SeSelector.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/util/ByteArrayUtils.h"
#include "../../../../../../../../../../common/src/main/java/org/eclipse/keyple/example/calypso/common/postructure/CalypsoClassicInfo.h"
#include "../../../../../../../../../../../../component/keyple-calypso/src/main/java/org/eclipse/keyple/calypso/command/po/parser/ReadDataStructure.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/event/ReaderEvent.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/transaction/MatchingSe.h"
#include "../../../../../../../../../../../../component/keyple-calypso/src/main/java/org/eclipse/keyple/calypso/transaction/CalypsoPo.h"
#include "../../../../../../../../../../../../component/keyple-calypso/src/main/java/org/eclipse/keyple/calypso/transaction/PoTransaction.h"
#include "../../../../../../../../../../../../component/keyple-core/src/main/java/org/eclipse/keyple/seproxy/exception/KeypleReaderException.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace example {
                namespace calypso {
                    namespace pc {
                        using ReadDataStructure = org::eclipse::keyple::calypso::command::po::parser::ReadDataStructure;
                        using ReadRecordsRespPars = org::eclipse::keyple::calypso::command::po::parser::ReadRecordsRespPars;
                        using CalypsoPo = org::eclipse::keyple::calypso::transaction::CalypsoPo;
                        using PoSelector = org::eclipse::keyple::calypso::transaction::PoSelector;
                        using PoTransaction = org::eclipse::keyple::calypso::transaction::PoTransaction;
                        using CalypsoClassicInfo = org::eclipse::keyple::example::calypso::common::postructure::CalypsoClassicInfo;
                        using CalypsoUtilities = org::eclipse::keyple::example::calypso::common::transaction::CalypsoUtilities;
                        using PcscPlugin = org::eclipse::keyple::plugin::pcsc::PcscPlugin;
                        using ChannelState = org::eclipse::keyple::seproxy::ChannelState;
                        using SeProxyService = org::eclipse::keyple::seproxy::SeProxyService;
                        using SeReader = org::eclipse::keyple::seproxy::SeReader;
                        using ObservableReader = org::eclipse::keyple::seproxy::event_Renamed::ObservableReader;
                        using ReaderObserver = org::eclipse::keyple::seproxy::event_Renamed::ObservableReader::ReaderObserver;
                        using ReaderEvent = org::eclipse::keyple::seproxy::event_Renamed::ReaderEvent;
                        using KeypleBaseException = org::eclipse::keyple::seproxy::exception::KeypleBaseException;
                        using KeypleReaderException = org::eclipse::keyple::seproxy::exception::KeypleReaderException;
                        using ContactlessProtocols = org::eclipse::keyple::seproxy::protocol::ContactlessProtocols;
                        using MatchingSe = org::eclipse::keyple::transaction::MatchingSe;
                        using SeSelection = org::eclipse::keyple::transaction::SeSelection;
                        using SeSelector = org::eclipse::keyple::transaction::SeSelector;
                        using ByteArrayUtils = org::eclipse::keyple::util::ByteArrayUtils;
                        using org::slf4j::Logger;
                        using org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> UseCase_Calypso2_DefaultSelectionNotification_Pcsc::logger = org::slf4j::LoggerFactory::getLogger(UseCase_Calypso2_DefaultSelectionNotification_Pcsc::typeid);
const std::shared_ptr<void> UseCase_Calypso2_DefaultSelectionNotification_Pcsc::waitForEnd = nullptr;

                        UseCase_Calypso2_DefaultSelectionNotification_Pcsc::UseCase_Calypso2_DefaultSelectionNotification_Pcsc() throw(KeypleBaseException, InterruptedException) {
                            /* Get the instance of the SeProxyService (Singleton pattern) */
                            std::shared_ptr<SeProxyService> seProxyService = SeProxyService::getInstance();

                            /* Get the instance of the PC/SC plugin */
                            std::shared_ptr<PcscPlugin> pcscPlugin = PcscPlugin::getInstance();

                            /* Assign PcscPlugin to the SeProxyService */
                            seProxyService->addPlugin(pcscPlugin);

                            /*
                             * Get a PO reader ready to work with Calypso PO. Use the getReader helper method from the
                             * CalypsoUtilities class.
                             */
                            poReader = CalypsoUtilities::getDefaultPoReader(seProxyService);

                            /* Check if the reader exists */
                            if (poReader == nullptr) {
                                throw std::make_shared<IllegalStateException>("Bad PO reader setup");
                            }

                            logger->info("=============== UseCase Calypso #2: AID based default selection ===================");
                            logger->info("= PO Reader  NAME = {}", poReader->getName());

                            /*
                             * Prepare a Calypso PO selection
                             */
                            seSelection = std::make_shared<SeSelection>(poReader);

                            /*
                             * Setting of an AID based selection of a Calypso REV3 PO
                             *
                             * Select the first application matching the selection AID whatever the SE communication
                             * protocol keep the logical channel open after the selection
                             */

                            /*
                             * Calypso selection: configures a PoSelector with all the desired attributes to make the
                             * selection and read additional information afterwards
                             */
                            std::shared_ptr<PoSelector> poSelector = std::make_shared<PoSelector>(ByteArrayUtils::fromHex(CalypsoClassicInfo::AID), SeSelector::SelectMode::FIRST, ChannelState::KEEP_OPEN, ContactlessProtocols::PROTOCOL_ISO14443_4, "AID: " + CalypsoClassicInfo::AID);

                            /*
                             * Prepare the reading order and keep the associated parser for later use once the selection
                             * has been made.
                             */
                            readEnvironmentParser = poSelector->prepareReadRecordsCmd(CalypsoClassicInfo::SFI_EnvironmentAndHolder, ReadDataStructure::SINGLE_RECORD_DATA, CalypsoClassicInfo::RECORD_NUMBER_1, std::string::format("EnvironmentAndHolder (SFI=%02X))", CalypsoClassicInfo::SFI_EnvironmentAndHolder));

                            /*
                             * Add the selection case to the current selection (we could have added other cases here)
                             */
                            seSelection->prepareSelection(poSelector);

                            /*
                             * Provide the SeReader with the selection operation to be processed when a PO is inserted.
                             */
                            (std::static_pointer_cast<ObservableReader>(poReader))->setDefaultSelectionRequest(seSelection->getSelectionOperation(), ObservableReader::NotificationMode::MATCHED_ONLY);

                            /* Set the current class as Observer of the first reader */
//JAVA TO C++ CONVERTER TODO TASK: You cannot use 'shared_from_this' in a constructor:
                            (std::static_pointer_cast<ObservableReader>(poReader))->addObserver(shared_from_this());

                            logger->info("==================================================================================");
                            logger->info("= Wait for a PO. The default AID based selection with reading of Environment     =");
                            logger->info("= file is ready to be processed as soon as the PO is detected.                   =");
                            logger->info("==================================================================================");

                            /* Wait for ever (exit with CTRL-C) */
//JAVA TO C++ CONVERTER TODO TASK: Multithread locking is not converted to native C++ unless you choose one of the options on the 'Modern C++ Options' dialog:
                            synchronized(waitForEnd) {
                                waitForEnd->wait();
                            }
                        }

                        void UseCase_Calypso2_DefaultSelectionNotification_Pcsc::update(std::shared_ptr<ReaderEvent> event_Renamed) {
                            switch (event_Renamed->getEventType()) {
                                case SE_MATCHED:
                                    if (seSelection->processDefaultSelection(event_Renamed->getDefaultSelectionResponse())) {
                                        std::shared_ptr<MatchingSe> selectedSe = seSelection->getSelectedSe();

                                        logger->info("Observer notification: the selection of the PO has succeeded.");

                                        /*
                                         * Retrieve the data read from the parser updated during the selection process
                                         */
                                        std::vector<char> environmentAndHolder = (readEnvironmentParser->getRecords())->get(static_cast<int>(CalypsoClassicInfo::RECORD_NUMBER_1));

                                        /* Log the result */
                                        logger->info("Environment file data: {}", ByteArrayUtils::toHex(environmentAndHolder));

                                        /* Go on with the reading of the first record of the EventLog file */
                                        logger->info("==================================================================================");
                                        logger->info("= 2nd PO exchange: reading transaction of the EventLog file.                     =");
                                        logger->info("==================================================================================");

                                        std::shared_ptr<PoTransaction> poTransaction = std::make_shared<PoTransaction>(poReader, std::static_pointer_cast<CalypsoPo>(selectedSe));

                                        /*
                                         * Prepare the reading order and keep the associated parser for later use once
                                         * the transaction has been processed.
                                         */
                                        std::shared_ptr<ReadRecordsRespPars> readEventLogParser = poTransaction->prepareReadRecordsCmd(CalypsoClassicInfo::SFI_EventLog, ReadDataStructure::SINGLE_RECORD_DATA, CalypsoClassicInfo::RECORD_NUMBER_1, std::string::format("EventLog (SFI=%02X, recnbr=%d))", CalypsoClassicInfo::SFI_EventLog, CalypsoClassicInfo::RECORD_NUMBER_1));

                                        /*
                                         * Actual PO communication: send the prepared read order, then close the channel
                                         * with the PO
                                         */
                                        try {
                                            if (poTransaction->processPoCommands(ChannelState::CLOSE_AFTER)) {
                                                logger->info("The reading of the EventLog has succeeded.");

                                                /*
                                                 * Retrieve the data read from the parser updated during the transaction
                                                 * process
                                                 */
                                                std::vector<char> eventLog = (readEventLogParser->getRecords())->get(static_cast<int>(CalypsoClassicInfo::RECORD_NUMBER_1));

                                                /* Log the result */
                                                logger->info("EventLog file data: {}", ByteArrayUtils::toHex(eventLog));
                                            }
                                        }
                                        catch (const KeypleReaderException &e) {
                                            e->printStackTrace();
                                        }
                                        logger->info("==================================================================================");
                                        logger->info("= End of the Calypso PO processing.                                              =");
                                        logger->info("==================================================================================");
                                    }
                                    else {
                                        logger->error("The selection of the PO has failed. Should not have occurred due to the MATCHED_ONLY selection mode.");
                                    }
                                    break;
                                case SE_INSERTED:
                                    logger->error("SE_INSERTED event: should not have occurred due to the MATCHED_ONLY selection mode.");
                                    break;
                                case SE_REMOVAL:
                                    logger->info("The PO has been removed.");
                                    break;
                                default:
                                    break;
                            }
                        }

                        void UseCase_Calypso2_DefaultSelectionNotification_Pcsc::main(std::vector<std::string> &args) throw(InterruptedException, KeypleBaseException) {
                            /* Create the observable object to handle the PO processing */
                            std::shared_ptr<UseCase_Calypso2_DefaultSelectionNotification_Pcsc> m = std::make_shared<UseCase_Calypso2_DefaultSelectionNotification_Pcsc>();
                        }
                    }
                }
            }
        }
    }
}