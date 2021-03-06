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

/* Core */
#include "CardPresentMonitoringJob.h"

/* Common */
#include "InterruptedException.h"
#include "Thread.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace plugin {
namespace local {
namespace monitoring {

CardPresentMonitoringJob::CardPresentMonitoringJob(SeReader* reader,
                                                   long waitTimeout,
                                                   bool monitorInsertion)
: reader(reader), waitTimeout(waitTimeout), monitorInsertion(monitorInsertion)
{
}

void CardPresentMonitoringJob::monitoringJob(
    AbstractObservableState* state, std::atomic<bool>& cancellationFlag)
{
    long retries = 0;

    logger->debug("[%] Polling from isSePresentPing\n", reader->getName());

    /* Re-init loop value to true */
    loop = true;

    while (loop) {
        if (cancellationFlag) {
            logger->debug("[%] monitoring job cancelled\n", reader->getName());
            return;
        }

        try {
            /* Polls for SE_INSERTED */
            if (monitorInsertion && reader->isSePresent()) {
                logger->debug("[%] The SE is present\n", reader->getName());
                loop = false;
                state->onEvent(InternalEvent::SE_INSERTED);
                return;
            }

            /* Polls for SE_REMOVED */
            if (!monitorInsertion && !reader->isSePresent()) {
                logger->debug("[%] The SE is not present\n", reader->getName());
                loop = false;
                state->onEvent(InternalEvent::SE_REMOVED);
                return;
            }

        } catch (KeypleIOReaderException& e) {
            (void)e;
            loop = false;
            /* What do do here */
        }

        retries++;

        logger->trace("[%] isSePresent polling retries : %\n",
                      reader->getName(), retries);

        try {
            /* Wait a bit */
            Thread::sleep(waitTimeout);
        } catch (InterruptedException& ignored) {
            (void)ignored;
            /* Restore interrupted state... */
            //Thread.currentThread().interrupt();
            loop = false;
        }
    }

    logger->trace("[%] Looping has been stopped\n", reader->getName());
}

void CardPresentMonitoringJob::stop()
{
    logger->debug("[%] Stop Polling\n", reader->getName());
    loop = false;
}

std::future<void>
CardPresentMonitoringJob::startMonitoring(AbstractObservableState* state,
                                          std::atomic<bool>& cancellationFlag)
{
    return std::async(std::launch::async,
                      &CardPresentMonitoringJob::monitoringJob, this, state,
                      std::ref(cancellationFlag));
}

}
}
}
}
}
}
