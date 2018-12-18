#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <memory>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace org { namespace eclipse { namespace keyple { namespace seproxy { class SeReader; } } } }

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
            namespace example {
                namespace generic_Renamed {
                    namespace pc {


                        using namespace org::eclipse::keyple::example::generic_Renamed::pc::stub::se;
                        using SeReader = org::eclipse::keyple::seproxy::SeReader;

                        /**
                         * This class handles the reader events generated by the SeProxyService
                         */
                        class Demo_SeProtocolDetection_Stub : public std::enable_shared_from_this<Demo_SeProtocolDetection_Stub> {

                        private:
                            std::shared_ptr<SeReader> poReader, samReader;

                        public:
//JAVA TO C++ CONVERTER TODO TASK: No base class can be determined:
                            Demo_SeProtocolDetection_Stub(); //super();

                            /**
                             * Application entry
                             *
                             * @param args the program arguments
                             * @throws IllegalArgumentException in case of a bad argument
                             * @throws InterruptedException if thread error occurs
                             */
                            static void main(std::vector<std::string> &args) throw(std::invalid_argument, InterruptedException);
                        };

                    }
                }
            }
        }
    }
}