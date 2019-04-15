#pragma once

#include "../../../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/command/AbstractApduResponseParser.h"
#include "../../PoRevision.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <memory>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace org { namespace eclipse { namespace keyple { namespace command { class AbstractApduResponseParser; } } } }
namespace org { namespace eclipse { namespace keyple { namespace command { class StatusProperties; } } } }
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
            namespace calypso {
                namespace command {
                    namespace po {
                        namespace parser {
                            namespace session {

                                using PoRevision = org::eclipse::keyple::calypso::command::po::PoRevision;
                                using AbstractApduResponseParser = org::eclipse::keyple::command::AbstractApduResponseParser;
                                using ApduResponse = org::eclipse::keyple::seproxy::message::ApduResponse;

                                /**
                                 * Open session response parser. See specs: Calypso / page 100 / 9.5.1 - Open secure session
                                 *
                                 */
                                class AbstractOpenSessionRespPars : public AbstractApduResponseParser {

                                       /**
                                     * The Class SecureSession. A secure session is returned by a open secure session command
                                     */
                                public:
                                    class SecureSession : public std::enable_shared_from_this<SecureSession> {

                                        /** Challenge transaction counter */
                                    private:
                                        std::vector<char> const challengeTransactionCounter;

                                        /** Challenge random number */
                                        std::vector<char> const challengeRandomNumber;

                                        /** The previous session ratified boolean. */
                                        const bool previousSessionRatified;

                                        /** The manage secure session authorized boolean. */
                                        const bool manageSecureSessionAuthorized;

                                        /** The kif. */
                                        const char kif;

                                        /** The kvc (may be null if it doesn't exist in the considered PO [rev 1.0]). */
                                        const char kvc;

                                        /** The original data. */
                                        std::vector<char> const originalData;

                                        /** The secure session data. */
                                        std::vector<char> const secureSessionData;

                                        /**
                                         * Instantiates a new SecureSession for a Calypso application revision 3
                                         *
                                         * @param challengeTransactionCounter Challenge transaction counter
                                         * @param challengeRandomNumber Challenge random number
                                         * @param previousSessionRatified the previous session ratified
                                         * @param manageSecureSessionAuthorized the manage secure session authorized
                                         * @param kif the KIF from the response of the open secure session APDU command
                                         * @param kvc the KVC from the response of the open secure session APDU command
                                         * @param originalData the original data from the response of the open secure session APDU
                                         *        command
                                         * @param secureSessionData the secure session data from the response of open secure session
                                         *        APDU command
                                         */
                                    public:
                                        SecureSession(std::vector<char> &challengeTransactionCounter, std::vector<char> &challengeRandomNumber, bool previousSessionRatified, bool manageSecureSessionAuthorized, char kif,
                                                      char kvc, std::vector<char> &originalData, std::vector<char> &secureSessionData);

                                        /**
                                         * Instantiates a new SecureSession for a Calypso application revision 2.4
                                         * 
                                         * @param challengeTransactionCounter Challenge transaction counter
                                         * @param challengeRandomNumber Challenge random number
                                         * @param previousSessionRatified the previous session ratified
                                         * @param manageSecureSessionAuthorized the manage secure session authorized
                                         * @param kvc the KVC from the response of the open secure session APDU command
                                         * @param originalData the original data from the response of the open secure session APDU
                                         *        command
                                         * @param secureSessionData the secure session data from the response of open secure session
                                         *        APDU command
                                         */
                                        SecureSession(std::vector<char> &challengeTransactionCounter, std::vector<char> &challengeRandomNumber, bool previousSessionRatified, bool manageSecureSessionAuthorized, char kvc,
                                                      std::vector<char> &originalData, std::vector<char> &secureSessionData);

                                        virtual std::vector<char> getChallengeTransactionCounter();

                                        virtual std::vector<char> getChallengeRandomNumber();

                                        /**
                                         * Checks if is previous session ratified.
                                         *
                                         * @return the boolean
                                         */
                                        virtual bool isPreviousSessionRatified();

                                        /**
                                         * Checks if is manage secure session authorized.
                                         *
                                         * @return the boolean
                                         */
                                        virtual bool isManageSecureSessionAuthorized();

                                        /**
                                         * Gets the kif.
                                         *
                                         * @return the kif
                                         */
                                        virtual char getKIF();

                                        /**
                                         * Gets the kvc.
                                         *
                                         * @return the kvc
                                         */
                                        virtual char getKVC();

                                        /**
                                         * Gets the original data.
                                         *
                                         * @return the original data
                                         */
                                        virtual std::vector<char> getOriginalData();

                                        /**
                                         * Gets the secure session data.
                                         *
                                         * @return the secure session data
                                         */
                                        virtual std::vector<char> getSecureSessionData();
                                    };

                                private:
                                    static std::unordered_map<int, std::shared_ptr<AbstractApduResponseParser::StatusProperties>> STATUS_TABLE;

                                private:
                                    class StaticConstructor : public std::enable_shared_from_this<StaticConstructor> {
                                    public:
                                        StaticConstructor();
                                    };

                                private:
                                    static AbstractOpenSessionRespPars::StaticConstructor staticConstructor;


                                protected:
                                    std::unordered_map<int, std::shared_ptr<AbstractApduResponseParser::StatusProperties>> getStatusTable() override;

                                private:
                                    const PoRevision revision;

                                    /** The secure session. */
                                public:
                                    std::shared_ptr<SecureSession> secureSession;

                                    /**
                                     * Instantiates a new AbstractOpenSessionRespPars.
                                     *
                                     * @param response the response from Open secure session APDU command
                                     * @param revision the revision of the PO
                                     */
                                    AbstractOpenSessionRespPars(std::shared_ptr<ApduResponse> response, PoRevision revision);

                                    static std::shared_ptr<AbstractOpenSessionRespPars> create(std::shared_ptr<ApduResponse> response, PoRevision revision);

                                    virtual std::shared_ptr<SecureSession> toSecureSession(std::vector<char> &apduResponseData)
                                    {
                                        (void)apduResponseData;
                                        return nullptr;
                                    }

                                    virtual std::vector<char> getPoChallenge();


                                    virtual int getTransactionCounterValue();

                                    virtual bool wasRatified();

                                    virtual bool isManageSecureSessionAuthorized();

                                    virtual char getSelectedKif();

                                    virtual char getSelectedKvc();

                                    virtual std::vector<char> getRecordDataRead();

                                 

protected:
                                    std::shared_ptr<AbstractOpenSessionRespPars> shared_from_this() {
                                        return std::static_pointer_cast<AbstractOpenSessionRespPars>(AbstractApduResponseParser::shared_from_this());
                                    }
                                };

                            }
                        }
                    }
                }
            }
        }
    }
}
