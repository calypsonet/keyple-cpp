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

#pragma once

#include <string>
#include <vector>
#include <memory>

/* Common */
#include "Export.h"

/* Core */
#include "AbstractDefaultSelectionsRequest.h"
#include "Observable.h"
#include "NotificationMode.h"
#include "PollingMode.h"
#include "ReaderEvent_Import.h"
#include "SeReader.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace event {

using namespace keyple::core::seproxy;
using namespace keyple::core::seproxy::event;

/**
 * The ObservableReader interface provides the API for observable readers.
 * <ul>
 * <li>Observer management
 * <li>Start/stop of SE detection
 * <li>Managing the default selection
 * <li>Definition of polling and notification modes
 * </ul>
 */
class EXPORT ObservableReader : public virtual SeReader {
public:
    /**
     * Interface to be implemented by reader observers.
     */
    class ReaderObserver : public virtual Observer<ReaderEvent> {
    public:
        /**
         *
         */
        virtual ~ReaderObserver()
        {
        }

        /**
         *
         */
        virtual void update(std::shared_ptr<ReaderEvent> event) = 0;
    };

    /**
     *
     */
    virtual ~ObservableReader()
    {
    }

    /**
     * Add a reader observer.
     * <p>
     * The observer will receive all the events produced by this reader (card
     * insertion, removal, etc.)
     *
     * @param observer the observer object
     */
    virtual void addObserver(std::shared_ptr<ReaderObserver> observer) = 0;

    /**
     * Remove a reader observer.
     * <p>
     * The observer will not receive any of the events produced by this reader.
     *
     * @param observer the observer object
     */
    virtual void removeObserver(std::shared_ptr<ReaderObserver> observer) = 0;

    /**
     * Push a ReaderEvent of the {@link ObservableReader} to its registered
     * observers.
     *
     * @param event the event (see {@link ReaderEvent})
     */
    virtual void notifyObservers(std::shared_ptr<ReaderEvent> event) = 0;

    /**
     * Remove all observers at once
     */
    virtual void clearObservers() = 0;

    /**
     * @return the number of observers
     */
    virtual int countObservers() = 0;

    /**
     * Starts the SE detection. Once activated, the application can be notified
     * of the arrival of an SE.
     *
     * @param pollingMode indicates the action to be followed after processing
     *        the SE: if REPEATING, the SE detection is restarted, if
     *        SINGLESHOT, the SE detection is stopped until a new call to
     *        startSeDetection is made.
     */
    virtual void startSeDetection(PollingMode pollingMode) = 0;

    /**
     * Stops the SE detection.
     * <p>
     * This method must be overloaded by readers depending on the particularity
     * of their management of the start of SE detection.
     */
    virtual void stopSeDetection() = 0;

    /**
     * Defines the selection request to be processed when an SE is inserted.
     * Depending on the SE and the notificationMode parameter, a SE_INSERTED,
     * SE_MATCHED or no event at all will be notified to the application
     * observers.
     *
     * @param defaultSelectionsRequest the selection request to be operated
     * @param notificationMode indicates whether a SE_INSERTED event should be
     *        notified even if the selection has failed (ALWAYS) or whether the
     *        SE insertion should be ignored in this case (MATCHED_ONLY).
     */
    virtual void
    setDefaultSelectionRequest(std::shared_ptr<AbstractDefaultSelectionsRequest>
                                   defaultSelectionsRequest,
                               NotificationMode notificationMode) = 0;

    /**
     * A combination of defining the default selection request and starting the
     * SE detection.
     *
     * @param defaultSelectionsRequest the selection request to be operated
     * @param notificationMode indicates whether a SE_INSERTED event should be
     *        notified even if the selection has failed (ALWAYS) or whether the
     *        SE insertion should be ignored in this case (MATCHED_ONLY).
     * @param pollingMode indicates the action to be followed after processing
     *        the SE: if CONTINUE, the SE detection is restarted, if STOP, the
     *        SE detection is stopped until a new call to startSeDetection is
     *        made.
     */
    virtual void setDefaultSelectionRequest(
        std::shared_ptr<AbstractDefaultSelectionsRequest>
            defaultSelectionsRequest,
        NotificationMode notificationMode, PollingMode pollingMode) = 0;

    /**
     * Signal sent by the application to the reader to indicate the end of the
     * application processing.
     * <p>
     * Depending on whether a request with the indication CLOSE_AFTER has been
     * executed before or not, a closing message will be sent to the reader in
     * order to proceed with the closing of the physical channel.
     * <p>
     * The action to be continued will be the one defined by the PollingMode
     * used to start the SE detection.
     * <p>
     * The call of this method is mandatory only if the current transaction
     * performed via an observed reader did not end with a call to an operation
     * causing a physical channel closing (CLOSE_AFTER). The main objective here
     * is to achieve the closing of the physical channel. A typical use of this
     * method is in handling exceptions (catch) that may occur during a
     * transaction that would prevent reaching the last operation closing the
     * physical channel.
     * <p>
     * The channel closing here refers to the application's intention to no
     * longer communicate with the SE. This may take the form of an immediate
     * physical channel closing in the case of an unobserved reader or a delayed
     * closing upon removal of the SE (removal sequence).
     */
    virtual void notifySeProcessed() = 0;
};

}
}
}
}
