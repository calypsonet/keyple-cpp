#pragma once

#include "../../rm/RemoteMethodInvoker.h"
#include <string>
#include <memory>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace org { namespace eclipse { namespace keyple { namespace plugin { namespace remotese { namespace transport { namespace model { class KeypleDto; } } } } } } }

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
            namespace plugin {
                namespace remotese {
                    namespace nativese {
                        namespace method {

                            using RemoteMethodInvoker = org::eclipse::keyple::plugin::remotese::rm::RemoteMethodInvoker;
                            using KeypleDto = org::eclipse::keyple::plugin::remotese::transport::model::KeypleDto;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Deprecated public class RmDisconnectReaderInvoker implements org.eclipse.keyple.plugin.remotese.rm.RemoteMethodInvoker
                            class RmDisconnectReaderInvoker : public std::enable_shared_from_this<RmDisconnectReaderInvoker>, public RemoteMethodInvoker {

                            private:
                                const std::string sessionId;
                                const std::string nativeReaderName;
                                const std::string slaveNodeId;

                            public:
                                RmDisconnectReaderInvoker(const std::string &sessionId, const std::string &nativeReaderName, const std::string &slaveNodeId);

                                std::shared_ptr<KeypleDto> dto() override;
                            };

                        }
                    }
                }
            }
        }
    }
}