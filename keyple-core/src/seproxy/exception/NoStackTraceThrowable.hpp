/*
 * Copyright (c) 2018 Calypso Networks Association https://www.calypsonet-asso.org/
 *
 * All rights reserved. This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License version 2.0 which accompanies this distribution, and is
 * available at https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 */

#ifndef KEYPLE_SEPROXY_EXCEPTION_NO_STACK_TRACE_H
#define KEYPLE_SEPROXY_EXCEPTION_NO_STACK_TRACE_H

#include <exception>

namespace keyple {
    namespace seproxy {
        namespace exception {

            class NoStackTraceThrowable : public std::exception {

            };
        }
    }
}

#endif /* KEYPLE_SEPROXY_EXCEPTION_NO_STACK_TRACE_H */