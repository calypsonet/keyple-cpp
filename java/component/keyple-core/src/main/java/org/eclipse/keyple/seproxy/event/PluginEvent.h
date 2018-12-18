#pragma once

#include <string>
#include <vector>
#include <memory>

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
namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace event_Renamed {

                    class PluginEvent final : public std::enable_shared_from_this<PluginEvent> {
                        /**
                         * The name of the plugin handling the reader that produced the event
                         */
                    private:
                        const std::string pluginName;

                        /**
                         * The name of the reader involved
                         */
                        const std::string readerName;

                        /**
                         * The type of event
                         */
                        const EventType eventType;

                        /**
                         * The different types of reader event
                         */
                    public:
                        class EventType final {
                            /**
                             * A reader has been connected.
                             */
public:
                            static EventType READER_CONNECTED;

                            /**
                             * A reader has been disconnected.
                             */
                            static EventType READER_DISCONNECTED;

private:
                            static std::vector<EventType> valueList;

                            class StaticConstructor {
                            public:
                                StaticConstructor();
                            };

                            static StaticConstructor staticConstructor;

public:
                            enum class InnerEnum {
                                READER_CONNECTED,
                                READER_DISCONNECTED
                            };

                            const InnerEnum innerEnumValue;
private:
                            const std::string nameValue;
                            const int ordinalValue;
                            static int nextOrdinal;

                            /** The event name. */
                        private:
                            std::string name;

                        public:
                            EventType(const std::string &name, InnerEnum innerEnum, std::shared_ptr<PluginEvent> outerInstance, const std::string &name);

                            virtual std::string getName();

public:
                            bool operator == (const EventType &other);

                            bool operator != (const EventType &other);

                            static std::vector<EventType> values();

                            int ordinal();

                            std::string toString();

                            static EventType valueOf(const std::string &name);
                        };

                    public:
                        PluginEvent(const std::string &pluginName, const std::string &readerName, EventType eventType);

                        std::string getPluginName();

                        std::string getReaderName();

                        EventType getEventType();
                    };

                }
            }
        }
    }
}