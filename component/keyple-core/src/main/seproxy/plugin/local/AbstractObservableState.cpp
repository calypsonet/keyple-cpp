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

#include "AbstractObservableState.h"

#include <chrono>

/* Core */
#include "AbstractObservableLocalReader.h"

/* Common */
#include "exceptionhelper.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace plugin {
namespace local {

AbstractObservableState::AbstractObservableState(
    MonitoringState state, AbstractObservableLocalReader* reader,
    std::shared_ptr<MonitoringJob> monitoringJob,
    std::shared_ptr<MonitoringPool> executorService)
: state(state), reader(reader), monitoringJob(monitoringJob),
  monitoringEvent(nullptr), executorService(executorService), cancellationFlag()
{
}

AbstractObservableState::AbstractObservableState(
    MonitoringState state, AbstractObservableLocalReader* reader)
: state(state), reader(reader), monitoringEvent(nullptr), cancellationFlag(){
}

MonitoringState AbstractObservableState::getMonitoringState()
{
    return state;
}

void AbstractObservableState::switchState(const MonitoringState stateId)
{
    reader->switchState(stateId);
}

void AbstractObservableState::onActivate()
{
    logger->trace("[%] onActivate => %\n", reader->getName(),
                  getMonitoringState());

    cancellationFlag = false;

    /* Launch the monitoringJob is necessary */
    if (monitoringJob != nullptr) {
        if (executorService == nullptr) {
            throw AssertionError("ExecutorService must be set");
        }

        monitoringEvent =
            executorService->submit(monitoringJob, this, cancellationFlag);
    }
}

void AbstractObservableState::onDeactivate()
{
    logger->trace("[%] onDeactivate => %\n", reader->getName(),
                  getMonitoringState());

    /* Cancel the monitoringJob is necessary */
    if (monitoringEvent != nullptr &&
        monitoringEvent->wait_for(std::chrono::seconds(0)) !=
            std::future_status::ready) {

        logger->debug("onDeactivate - cancelling monitoring job\n");
        monitoringJob->stop();

        /* TODO this could be inside the stop method? */
        cancellationFlag = true;
        monitoringEvent = nullptr;
        logger->trace("[%] onDeactivate => cancel runnable waitForCarPresent"
                      " by thead interruption\n", reader->getName());
    }
}

std::ostream& operator<<(std::ostream& os, const MonitoringState& ms)
{
    switch (ms) {
    case MonitoringState::WAIT_FOR_START_DETECTION:
        os << "WAIT_FOR_START_DETECTION";
        break;
    case MonitoringState::WAIT_FOR_SE_INSERTION:
        os << "WAIT_FOR_SE_INSERTION";
        break;
    case MonitoringState::WAIT_FOR_SE_PROCESSING:
        os << "WAIT_FOR_SE_PROCESSING";
        break;
    case MonitoringState::WAIT_FOR_SE_REMOVAL:
        os << "WAIT_FOR_SE_REMOVAL";
        break;
    }

    return os;
}

}
}
}
}
}
