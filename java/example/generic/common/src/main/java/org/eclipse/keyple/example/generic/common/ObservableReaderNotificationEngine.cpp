/* Core */
#include "KeyplePluginNotFoundException.h"
#include "KeypleReaderNotFoundException.h"
#include "PluginEvent.h"
#include "ReaderEvent_Import.h"
#include "SeProxyService.h"
#include "SeReader.h"

/* Example */
#include "ObservableReaderNotificationEngine.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace example {
                namespace generic {
                    namespace common {

                        using ReaderPlugin     = org::eclipse::keyple::seproxy::ReaderPlugin;
                        using SeProxyService   = org::eclipse::keyple::seproxy::SeProxyService;
                        using SeReader         = org::eclipse::keyple::seproxy::SeReader;
                        using ObservablePlugin = org::eclipse::keyple::seproxy::event::ObservablePlugin;
                        using ObservableReader = org::eclipse::keyple::seproxy::event::ObservableReader;
                        using PluginEvent      = org::eclipse::keyple::seproxy::event::PluginEvent;
                        using ReaderEvent      = org::eclipse::keyple::seproxy::event::ReaderEvent;
                        using KeyplePluginNotFoundException =
                            org::eclipse::keyple::seproxy::exception::KeyplePluginNotFoundException;
                        using KeypleReaderNotFoundException =
                            org::eclipse::keyple::seproxy::exception::KeypleReaderNotFoundException;

                        ObservableReaderNotificationEngine::ObservableReaderNotificationEngine()
                        {
                            /* initializes observers */
                            logger->debug("casting readerObserver\n");
                            std::shared_ptr<SpecificReaderObserver> readerObserver =
                                std::shared_ptr<SpecificReaderObserver>(new SpecificReaderObserver(this));

                            logger->debug("instanciating pluginObserver\n");
                            pluginObserver = std::shared_ptr<SpecificPluginObserver>(
                                new SpecificPluginObserver(this, readerObserver));
                        }

                        ObservableReaderNotificationEngine::~ObservableReaderNotificationEngine()
                        {
                            logger->debug("destructor\n");
                        }

                        void ObservableReaderNotificationEngine::setPluginObserver()
                        {
                            logger->debug("\n");

                            /*
                             * We add an observer to each plugin (only one in this example) the readers observers will
                             * be added dynamically upon plugin notification (see SpecificPluginObserver.update)
                             */
                            for (auto plugin : SeProxyService::getInstance().getPlugins())
                            {

                                if (std::dynamic_pointer_cast<ObservablePlugin>(plugin) != nullptr)
                                {
                                    logger->info("add observer PLUGINNAME = %s\n", plugin->getName());
                                    logger->info("this->pluginObserver: %p\n", this->pluginObserver);
                                    (std::dynamic_pointer_cast<ObservablePlugin>(plugin))->addObserver(this->pluginObserver);
                                }
                                else
                                {
                                    logger->info("PLUGINNAME = %s isn't observable\n", plugin->getName());
                                }
                            }
                        }

                        //JAVA TO C++ CONVERTER TODO TASK: No base class can be determined:
                        ObservableReaderNotificationEngine::SpecificReaderObserver::SpecificReaderObserver(
                            ObservableReaderNotificationEngine *outerInstance)
                            : outerInstance(outerInstance)
                        {
                        }

                        void ObservableReaderNotificationEngine::SpecificReaderObserver::update(
                            std::shared_ptr<ReaderEvent> event)
                        {
                            /* just log the event */
                            outerInstance->logger->info(
                                "event -> pluginname: %s, readername: %s, eventname: %s\n",
                                event->getPluginName(), event->getReaderName(),
                                event->getEventType().getName());
                        }

                        ObservableReaderNotificationEngine::SpecificPluginObserver::SpecificPluginObserver(
                            ObservableReaderNotificationEngine *outerInstance,
                            std::shared_ptr<SpecificReaderObserver> readerObserver)
                            : outerInstance(outerInstance)
                        {
                            this->readerObserver = readerObserver;
                        }

                        void ObservableReaderNotificationEngine::SpecificPluginObserver::update(
                            std::shared_ptr<PluginEvent> event)
                        {
                            std::shared_ptr<SeReader> reader = nullptr;
                            outerInstance->logger->info(
                                "PluginEvent: PLUGINNAME = %s, READERNAME = %s, EVENTTYPE = %s\n",
                                event->getPluginName(), event->getReaderName(), event->getEventType());

                            /* We retrieve the reader object from its name. */
                            try
                            {
                                reader = SeProxyService::getInstance()
                                             .getPlugin(event->getPluginName())
                                             ->getReader(event->getReaderName());
                            } catch (KeyplePluginNotFoundException &e)
                            {
                                e.printStackTrace();
                            } catch (KeypleReaderNotFoundException &e)
                            {
                                e.printStackTrace();
                            }

                            switch (event->getEventType().innerEnumValue)
                            {
                            case PluginEvent::EventType::InnerEnum::READER_CONNECTED:
                                outerInstance->logger->info("new reader! READERNAME = %s\n",
                                                            reader->getName());

                                /*
                                 * We are informed here of a disconnection of a reader.
                                 *
                                 * We add an observer to this reader if this is possible.
                                 */
                                if (std::dynamic_pointer_cast<ObservableReader>(reader) != nullptr)
                                {
                                    if (readerObserver != nullptr)
                                    {
                                        outerInstance->logger->info("add observer READERNAME = %s\n",
                                                                    reader->getName());
                                        (std::dynamic_pointer_cast<ObservableReader>(reader))
                                            ->addObserver(readerObserver);
                                    }
                                    else
                                    {
                                        outerInstance->logger->info("no observer to add READERNAME = %s\n",
                                                                    reader->getName());
                                    }
                                }
                                break;
                            case PluginEvent::EventType::InnerEnum::READER_DISCONNECTED:
                                /*
                                 * We are informed here of a disconnection of a reader.
                                 *
                                 * The reader object still exists but will be removed from the reader list right
                                 * after. Thus, we can properly remove the observer attached to this reader
                                 * before the list update.
                                 */
                                outerInstance->logger->info("reader removed. READERNAME = %s\n",
                                                            event->getReaderName());
                                if (std::dynamic_pointer_cast<ObservableReader>(reader) != nullptr)
                                {
                                    if (readerObserver != nullptr)
                                    {
                                        outerInstance->logger->info("remove observer READERNAME = %s\n",
                                                                    event->getReaderName());
                                        (std::dynamic_pointer_cast<ObservableReader>(reader))
                                            ->removeObserver(readerObserver);
                                    }
                                    else
                                    {
                                        outerInstance->logger->info(
                                            "unplugged reader READERNAME = %s wasn't observed\n",
                                            event->getReaderName());
                                    }
                                }
                                break;
                            default:
                                outerInstance->logger->info("unexpected reader event. EVENT = %s\n",
                                                            event->getEventType().getName());
                                break;
                            }
                        }

                    } // namespace common
                }     // namespace generic
            }         // namespace example
        }             // namespace keyple
    }                 // namespace eclipse
} // namespace org
