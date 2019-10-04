#pragma once

#include <stdexcept>
#include <memory>
#include <typeinfo>
#include <chrono>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

/* Common */
#include "Logger.h"
#include "LoggerFactory.h"


//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace org { namespace eclipse { namespace keyple { namespace plugin { namespace stub { class StubPlugin; } } } } }
namespace org { namespace eclipse { namespace keyple { namespace seproxy { namespace exception { class KeypleReaderException; } } } } }
namespace testing {}

/********************************************************************************
 * Copyright (c) 2019 Calypso Networks Association https://www.calypsonet-asso.org/
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
            namespace plugin {
                namespace stub {
                    using Logger                = org::eclipse::keyple::common::Logger;
                    using LoggerFactory         = org::eclipse::keyple::common::LoggerFactory;

                    class BaseStubTest : public std::enable_shared_from_this<BaseStubTest>//, public testing::Test
                    {

                    public:
                        std::shared_ptr<StubPlugin> stubPlugin;

                    private:
                        static const std::shared_ptr<Logger> logger;


                    public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Rule public org.junit.rules.TestName name = new org.junit.rules.TestName();
                        std::shared_ptr<BaseStubTest> name = std::make_shared<BaseStubTest>();

                        void setUp();

                        void tearDown();

                        void TestBoby();
                    };
                }
            }
        }
    }
}

