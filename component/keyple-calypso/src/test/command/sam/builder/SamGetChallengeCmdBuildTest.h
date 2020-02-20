#pragma once

#include <vector>
#include <stdexcept>
#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

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
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace sam {
                        namespace builder {
                            namespace security {


//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @RunWith(MockitoJUnitRunner.class) public class SamGetChallengeCmdBuildTest
                            class SamGetChallengeCmdBuildTest : public std::enable_shared_from_this<SamGetChallengeCmdBuildTest> {
                            public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void getChallengeCmdBuild() throws IllegalArgumentException
                                virtual void getChallengeCmdBuild();
                                };
                            }
                        }
                    }
                }
            }
        }