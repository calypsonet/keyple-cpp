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

#include <memory>
#include <set>
#include <string>

/* Common*/
#include "Export.h"
#include "Logger.h"
#include "LoggerFactory.h"

/* Core*/
#include "AbstractLoggedObservable.h"
#include "ReaderPlugin.h"
#include "ObservablePlugin.h"
#include "PluginEvent.h"

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace event {
                    class PluginEvent;
                }
            } // namespace seproxy
        }     // namespace keyple
    }         // namespace eclipse
} // namespace org
namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace plugin {
                    class AbstractObservableReader;
                }
            } // namespace seproxy
        }     // namespace keyple
    }         // namespace eclipse
} // namespace org
namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace exception {
                    class KeypleReaderException;
                }
            } // namespace seproxy
        }     // namespace keyple
    }         // namespace eclipse
} // namespace org
namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace event {
                    class PluginObserver;
                }
            } // namespace seproxy
        }     // namespace keyple
    }         // namespace eclipse
} // namespace org
namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                class ReaderPlugin;
            }
        } // namespace keyple
    }     // namespace eclipse
} // namespace org
namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace exception {
                    class KeypleReaderNotFoundException;
                }
            } // namespace seproxy
        }     // namespace keyple
    }         // namespace eclipse
} // namespace org
namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace message {
                    class ProxyReader;
                }
            } // namespace seproxy
        }     // namespace keyple
    }         // namespace eclipse
} // namespace org

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace plugin {

                    using ReaderPlugin     = org::eclipse::keyple::seproxy::ReaderPlugin;
                    using ObservablePlugin = org::eclipse::keyple::seproxy::event::ObservablePlugin;
                    using PluginEvent      = org::eclipse::keyple::seproxy::event::PluginEvent;
                    using KeypleReaderException =
                        org::eclipse::keyple::seproxy::exception::KeypleReaderException;
                    using KeypleReaderNotFoundException =
                        org::eclipse::keyple::seproxy::exception::KeypleReaderNotFoundException;
                    using ProxyReader   = org::eclipse::keyple::seproxy::message::ProxyReader;
                    using Logger        = org::eclipse::keyple::common::Logger;
                    using LoggerFactory = org::eclipse::keyple::common::LoggerFactory;

                    /**
                     * Observable plugin. These plugin can report when a reader is added or removed.
                     */
                    class EXPORT AbstractObservablePlugin
                        : public org::eclipse::keyple::seproxy::plugin::AbstractLoggedObservable<PluginEvent>,
                          public virtual ReaderPlugin {

                      private:
                        const std::shared_ptr<Logger> logger = LoggerFactory::getLogger(typeid(AbstractObservablePlugin));

                        /**
                         * The list of readers
                         */
                      protected:
                        std::shared_ptr<SortedSet<std::shared_ptr<AbstractObservableReader>>> readers = nullptr;


                        /**
                         * Instanciates a new ReaderPlugin. Retrieve the current readers list.
                         *
                         * Gets the list for the native method the first time (null)
                         *
                         * @param name name of the plugin
                         */
                        AbstractObservablePlugin(const std::string &name);

                        /**
                         *
                         */
                        ~AbstractObservablePlugin();

                      public:
                        /**
                         *
                         */
                        void initReaders();

                        /**
                         * Returns the current readers list.
                         *
                         * The list is initialized in the constructor and may be updated in background in the case of a
                         * threaded plugin {@link AbstractThreadedObservablePlugin}
                         *
                         * @return the current reader list, can be null if the
                         */
                      public:
                        std::shared_ptr<std::set<std::shared_ptr<AbstractObservableReader>>> getReaders() throw(KeypleReaderException) override;

                        /**
                         * Returns the current list of reader names.
                         *
                         * The list of names is built from the current readers list
                         *
                         * @return a list of String
                         */
                        std::shared_ptr<SortedSet<std::string>> getReaderNames() override;

                        /**
                         * Fetch connected native readers (from third party library) and returns a list of corresponding
                         * {@link org.eclipse.keyple.seproxy.plugin.AbstractObservableReader}
                         * {@link org.eclipse.keyple.seproxy.plugin.AbstractObservableReader} are new instances.
                         *
                         * @return the list of AbstractObservableReader objects.
                         * @throws KeypleReaderException if a reader error occurs
                         */
                    protected:
                        virtual std::shared_ptr<SortedSet<std::shared_ptr<AbstractObservableReader>>> initNativeReaders() = 0;

                        /**
                         * Fetch connected native reader (from third party library) by its name Returns the current
                         * {@link org.eclipse.keyple.seproxy.plugin.AbstractObservableReader} if it is already listed.
                         * Creates and returns a new {@link org.eclipse.keyple.seproxy.plugin.AbstractObservableReader}
                         * if not.
                         *
                         * @return the list of AbstractObservableReader objects.
                         * @throws KeypleReaderException if a reader error occurs
                         */
                        virtual std::shared_ptr<AbstractObservableReader> fetchNativeReader(const std::string &name) = 0;

                        /**
                         * Starts the monitoring thread
                         * <p>
                         * This abstract method has to be implemented by the class that handle the monitoring thread. It
                         * will be called when a first observer is added.
                         */
                        virtual void startObservation() = 0;

                        /**
                         * Ends the monitoring thread
                         * <p>
                         * This abstract method has to be implemented by the class that handle the monitoring thread. It
                         * will be called when the observer is removed.
                         */
                        virtual void stopObservation() = 0;

                        /**
                         * Add a plugin observer.
                         * <p>
                         * The observer will receive all the events produced by this plugin (reader insertion, removal,
                         * etc.)
                         * <p>
                         * The monitoring thread is started when the first observer is added.
                         *
                         * @param observer the observer object
                         */
                      public:
                        void addObserver(std::shared_ptr<ObservablePlugin::PluginObserver> observer);

                        /**
                         * Remove a plugin observer.
                         * <p>
                         * The observer will do not receive any of the events produced by this plugin.
                         * <p>
                         * The monitoring thread is ended when the last observer is removed.
                         *
                         * @param observer the observer object
                         */
                        void removeObserver(std::shared_ptr<ObservablePlugin::PluginObserver> observer);

                        /**
                         * Compare the name of the current ReaderPlugin to the name of the ReaderPlugin provided in
                         * argument
                         *
                         * @param plugin a {@link ReaderPlugin} object
                         * @return true if the names match (The method is needed for the SortedSet lists)
                         */
                        int compareTo(std::shared_ptr<ReaderPlugin> plugin);

                        /**
                         * Gets a specific reader designated by its name in the current readers list
                         *
                         * @param name of the reader
                         * @return the reader
                         * @throws KeypleReaderNotFoundException if the wanted reader is not found
                         */
                        std::shared_ptr<ProxyReader> getReader(const std::string &name) throw(KeypleReaderNotFoundException);

                      protected:
                        std::shared_ptr<AbstractObservablePlugin> shared_from_this() {
                            return std::static_pointer_cast<AbstractObservablePlugin>(AbstractLoggedObservable<org.eclipse.keyple.seproxy.event_Renamed.PluginEvent>::shared_from_this());
                        }
                    };

                } // namespace plugin
            }     // namespace seproxy
        }         // namespace keyple
    }             // namespace eclipse
} // namespace org
