#pragma once

#include "../../../../../../main/java/org/eclipse/keyple/util/Observable.h"
#include <string>
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
            namespace util {


                class ObservableTest : public std::enable_shared_from_this<ObservableTest> {
                public:
                    class Event : public std::enable_shared_from_this<Event> {
                    private:
                        const std::string name;

                    public:
                        Event(const std::string &name);

                        virtual std::string getName();

                        std::string toString() override;
                    };

                public:
                    class EventPlus : public Event {

                    public:
                        EventPlus(const std::string &name);

                        std::string toString() override;

protected:
                        std::shared_ptr<EventPlus> shared_from_this() {
                            return std::static_pointer_cast<EventPlus>(Event::shared_from_this());
                        }
                    };

                public:
                    class Observer : public std::enable_shared_from_this<Observer>, public Observable::Observer<std::shared_ptr<Event>> {
                    private:
                        int nbCalls = 0;

                    public:
                        virtual int getNbCalls();

                        void update(std::shared_ptr<Event> arg) override;
                    };

                public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void sample()
                    virtual void sample();
                };

            }
        }
    }
}