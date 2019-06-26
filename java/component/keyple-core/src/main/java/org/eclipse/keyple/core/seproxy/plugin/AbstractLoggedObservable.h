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

/* Core */
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include <type_traits>

/* Common */
#include "Logger.h"
#include "LoggerFactory.h"

/* Core */
#include "Observable.h"
#include "Configurable.h"
#include "Nameable.h"
#include "Observable.h"
#include "ReaderEvent_Import.h"
#include "PluginEvent.h"
#include "KeypleBaseException.h"

namespace org { namespace eclipse { namespace keyple { namespace core { namespace seproxy { namespace plugin { class AbstractObservableReader; }}}}}}
namespace org { namespace eclipse { namespace keyple { namespace core { namespace seproxy { namespace plugin { class AbstractObservablePlugin; }}}}}}

namespace org {
namespace eclipse {
namespace keyple {
namespace core {
namespace seproxy {
namespace plugin {

using KeypleBaseException = org::eclipse::keyple::core::seproxy::exception::KeypleBaseException;
using Configurable        = org::eclipse::keyple::core::util::Configurable;
using Nameable            = org::eclipse::keyple::core::util::Nameable;
using Logger              = org::eclipse::keyple::common::Logger;
using LoggerFactory       = org::eclipse::keyple::common::LoggerFactory;
using ReaderEvent         = org::eclipse::keyple::core::seproxy::event::ReaderEvent;
using PluginEvent         = org::eclipse::keyple::core::seproxy::event::PluginEvent;

/**
    * Intermediate observable class to handle the logging of AbstractObservableReader and
    * AbstractObservablePlugin
    *
    */
template <typename T>
class AbstractLoggedObservable
: public org::eclipse::keyple::core::util::Observable<T>, public virtual Nameable,
  public Configurable
{
    private:
    /**
        *
        */
    const std::shared_ptr<Logger> logger = LoggerFactory::getLogger(typeid(AbstractLoggedObservable));

    /**
        * The item name (must be unique)
        */
    protected:
    const std::string name;

    /**
        * Item constructor Force the definition of a name through the use of super method.
        *
        * @param name name of the observed object
        */
    public:
    AbstractLoggedObservable(const std::string &name) : name(name)
    {
        logger->debug("constructor (name: %s)\n", name);
    }

    /**
        * Gets the reader name
        *
        * @return the reader name string
        */
    std::string getName() override
    {
        return name;
    }

    /**
        * Add an observer. This will allow to be notified about all readers or plugins events.
        *
                             * @param observer Observer to notify
        */
    virtual void addObserver(std::shared_ptr<org::eclipse::keyple::core::util::Observer<T>> observer) override
    {

        logger->trace("[%s][%s] addObserver => Adding an observer\n", name, this->getName());

        org::eclipse::keyple::core::util::Observable<T>::addObserver(observer);
    }

    /**
        * Remove an observer.
        *
        * @param observer Observer to stop notifying
        */
    virtual void removeObserver(std::shared_ptr<org::eclipse::keyple::core::util::Observer<T>> observer) override
    {
        /*
            * Alex: Downcasting on both AbstractObservableReader and AbstractObservablePlugin doesn't seem possible even though
            *       templates are used because somehow the compiler knows where that comes from and doesn't want to apply the
            *       cast. Using the type of the template to switch between one or the other.
            */
        if (std::is_same<T, ReaderEvent>::value) {
        //if (std::dynamic_pointer_cast<AbstractObservableReader>(shared_from_this()) != nullptr) {
            logger->trace("[%s] removeObserver => Deleting a reader observer\n", this->getName());
        }
        else { //else if (std::reinterpret_pointer_cast<AbstractObservablePlugin>(shared_from_this()) != nullptr) {
            logger->trace("[%s] removeObserver => Deleting a plugin observer\n", this->getName());
        }

        org::eclipse::keyple::core::util::Observable<T>::removeObserver(observer);
    }

    /**
        * This method shall be called only from a SE Proxy plugin or reader implementing
        * AbstractObservableReader or AbstractObservablePlugin. Push a ReaderEvent / PluginEvent of the
        * selected AbstractObservableReader / AbstractObservablePlugin to its registered Observer.
        *
        * @param event the event
        */
    // Alex: function was final in Java (problem in PcscPlugin.cpp)
    void notifyObservers(std::shared_ptr<T> event) override
    {
        logger->debug("notifyObservers => event: %p\n", event);

        /*
            * Alex: Downcasting on both AbstractObservableReader and AbstractObservablePlugin doesn't seem possible even though
            *       templates are used because somehow the compiler knows where that comes from and doesn't want to apply the
            *       cast. Using the type of the template to switch between one or the other.
            */
        if (std::is_same<T, ReaderEvent>::value) {
        //if (std::static_pointer_cast<AbstractObservableReader>(shared_from_this()) != nullptr) {
            logger->trace("[%s] AbstractObservableReader => Notifying a reader event. EVENTNAME = %s\n",
                            this->getName(), (reinterpret_cast<ReaderEvent *>(event.get()))->getEventType().getName());
                                              
        }
        else { //else if (std::dynamic_pointer_cast<AbstractObservablePlugin>(shared_from_this()) != nullptr) {
            logger->trace("[%s] AbstractObservableReader => Notifying a plugin event. EVENTNAME = %s\n",
                            this->getName(), (reinterpret_cast<PluginEvent *>(event.get()))->getEventType().getName());
        }
 
        org::eclipse::keyple::core::util::Observable<T>::setChanged();
 
        org::eclipse::keyple::core::util::Observable<T>::notifyObservers(event);
    }

    /**
        * Set a list of parameters on a reader.
        * <p>
        * See {@link #setParameter(String, String)} for more details
        *
        * @param parameters the new parameters
        * @throws KeypleBaseException This method can fail when disabling the exclusive mode as it's
        *         executed instantly
        */
    void setParameters(std::unordered_map<std::string, std::string> &parameters) override {
        for (auto en : parameters) {
            setParameter(en.first, en.second);
        }
    }

    protected:
    std::shared_ptr<AbstractLoggedObservable> shared_from_this() {
        return std::static_pointer_cast<AbstractLoggedObservable>(org::eclipse::keyple::core::util::Observable<T>::shared_from_this());
    }
};

} // namespace plugin
}     // namespace seproxy
}         // namespace keyple
}             // namespace eclipse
} // namespace org
}