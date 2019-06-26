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

#include <iostream>
#include <ostream>
#include <memory>
#include <set>
#include <unordered_set>

/* Core */
#include "ReaderEvent_Import.h"

namespace org {
namespace eclipse {
namespace keyple {
namespace core {
namespace util {

template<typename T>
class Observer {
public:
    virtual void update(std::shared_ptr<T> event)
    {
        (void)event;
    }
};

/**
 * Generic Observable class
 *
 * @param <T> Generic event
 *
 */

template<typename T>
class Observable : public std::enable_shared_from_this<Observable<T>> {

public:
    /**
     *
     */
    virtual void addObserver(std::shared_ptr<Observer<T>> observer)
    {
        std::cout << "[DEBUG]   [class Observable]   [addObserver]" << std::endl;

        if (observer == nullptr) {
            std::cout << "[DEBUG]   [class Observable]   [addObserver] observer is null, skipping it" << std::endl;
            return;
        }

        /* Multithread locking is not converted to native C++ */

        if (!observers.size())
            std::cout << "[DEBUG]   [class Observable]   [addObserver] observers is empty, creating new set" << std::endl;
           

        std::cout << "[DEBUG]   [class Observable]   [addObserver] adding observer to set" << std::endl;
        observers.insert(observer);
    }

    /**
     *
     */
    virtual void removeObserver(std::shared_ptr<Observer<T>> observer)
    {
        std::cout << "[DEBUG]   [class Observable]   [addObserver]" << std::endl;

        if (observer == nullptr) {
            std::cout << "[DEBUG]   [class Observable]   [addObserver] observer is null, skipping it" << std::endl;
            return;
        }

        /* Multithread locking is not converted to native C++ */
        if (observers.size()) {
            std::cout << "[DEBUG]   [class Observable]   [addObserver] removing observer from set" << std::endl;
            observers.erase(observer);
        }
    }

    /**
     *
     */
    virtual void clearObservers()
    {
        std::cout << "[DEBUG]   [class Observable]   [clearObservers]" << std::endl;

        if (observers.size()) {
            std::cout << "[DEBUG]   [class Observable]   [clearObservers] clearing observers set" << std::endl;
            this->observers.clear();
        }
    }

    /**
     *
     */
    virtual void setChanged()
    {
        this->changed = true;
    }

    /**
     *
     */
    virtual void clearChanged()
    {
        this->changed = false;
    }

    virtual bool hasChanged()
    {
        return this->changed;
    }

    /**
     *
     */
    virtual int countObservers()
    {
        std::cout << "[DEBUG]   [class Observable] " << observers.size() << "observers" << std::endl;

        return observers.size();
    }

    /**
     *
     */
    virtual void notifyObservers()
    {
        std::cout << "[DEBUG]   [class Observable] notify observers (no event)" << std::endl;

        notifyObservers(nullptr);
    }

    /**
     *
     */
    virtual void notifyObservers(std::shared_ptr<T> event)
    {
        std::cout << "[DEBUG]   [class Observable] notify observers" << std::endl;

        /* Multithread locking is not converted to native C++ */

        if (!observers.size())
            return;

        /* Alex: Not sure I need the copy */
        std::set<std::shared_ptr<Observer<T>>> observersCopy;
        observersCopy.insert(observers.begin(), observers.end());

        for (auto observer : observersCopy)
            observer->update(event);
    }

private:
    /**
     *
     */
    bool changed = false;

    /*
     * this object will be used to synchronize the access to the observers list in order to be
     * thread safe
     */
    const std::shared_ptr<void> SYNC = nullptr;

    /**
     *
     */
    std::set<std::shared_ptr<Observer<T>>> observers;
};

}
}
}
}
}