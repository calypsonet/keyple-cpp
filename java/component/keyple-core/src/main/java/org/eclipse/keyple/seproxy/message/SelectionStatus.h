#pragma once

#include <stdexcept>
#include <memory>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace org { namespace eclipse { namespace keyple { namespace seproxy { namespace message { class AnswerToReset; } } } } }
namespace org { namespace eclipse { namespace keyple { namespace seproxy { namespace message { class ApduResponse; } } } } }

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
            namespace seproxy {
                namespace message {


                    class SelectionStatus : public std::enable_shared_from_this<SelectionStatus> {
                    private:
                        const std::shared_ptr<AnswerToReset> atr;
                        const std::shared_ptr<ApduResponse> fci;
//JAVA TO C++ CONVERTER NOTE: Fields cannot have the same name as methods:
                        const bool hasMatched_Renamed;

                    public:
                        SelectionStatus(std::shared_ptr<AnswerToReset> atr, std::shared_ptr<ApduResponse> fci, bool hasMatched);

                        virtual std::shared_ptr<AnswerToReset> getAtr();

                        virtual std::shared_ptr<ApduResponse> getFci();

                        virtual bool hasMatched();

                        bool equals(std::shared_ptr<void> o) override;

                        int hashCode() override;
                    };

                }
            }
        }
    }
}