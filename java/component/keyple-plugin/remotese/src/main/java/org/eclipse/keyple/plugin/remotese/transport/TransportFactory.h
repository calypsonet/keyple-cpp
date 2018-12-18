#pragma once

#include <memory>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace org { namespace eclipse { namespace keyple { namespace plugin { namespace remotese { namespace transport { class ClientNode; } } } } } }
namespace org { namespace eclipse { namespace keyple { namespace plugin { namespace remotese { namespace transport { class ServerNode; } } } } } }

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
                    namespace transport {


                        /**
                         * Factory for Clients and Servers sharing a protocol and a configuration to connectAReader each
                         * others
                         */
                        class TransportFactory : public std::enable_shared_from_this<TransportFactory> {

                        public:
                            virtual std::shared_ptr<ClientNode> getClient() = 0;

                            virtual std::shared_ptr<ServerNode> getServer() = 0;



                        };

                    }
                }
            }
        }
    }
}
