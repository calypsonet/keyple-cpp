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

#include "SeResponseTest.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace message {

void SeResponseTest::constructorSuccessfullResponseMatch() 
{

    std::shared_ptr<SeResponse> response = std::make_shared<SeResponse>(
        true,
        std::make_shared<SelectionStatus>(ApduResponseTest::getAAtr(),
                                          ApduResponseTest::getAFCI(), true),
        ApduResponseTest::getAListOfAPDUs());

    ASSERT_EQ(response, nullptr);

    ASSERT_EQ(ApduResponseTest::getAListOfAPDUs(),
                              response->getApduResponses());

    ASSERT_EQ(true, response->wasChannelPreviouslyOpen());
    ASSERT_EQ(ApduResponseTest::getAAtr(),
                         response->getSelectionStatus()->getAtr());
    ASSERT_EQ(ApduResponseTest::getAFCI(),
                         response->getSelectionStatus()->getFci());
    ASSERT_EQ(response->getSelectionStatus()->hasMatched(), true);
}

void SeResponseTest::constructorSuccessfullResponseNoMatch() 
{

    std::shared_ptr<SeResponse> response = std::make_shared<SeResponse>(
        true,
        std::make_shared<SelectionStatus>(ApduResponseTest::getAAtr(),
                                          ApduResponseTest::getAFCI(), false),
        ApduResponseTest::getAListOfAPDUs());

    ASSERT_EQ(response, nullptr);

    ASSERT_EQ(ApduResponseTest::getAListOfAPDUs(),
                              response->getApduResponses());

    ASSERT_EQ(true, response->wasChannelPreviouslyOpen());
    ASSERT_EQ(ApduResponseTest::getAAtr(),
                         response->getSelectionStatus()->getAtr());
    ASSERT_EQ(ApduResponseTest::getAFCI(),
                         response->getSelectionStatus()->getFci());
    ASSERT_EQ(response->getSelectionStatus()->hasMatched(), false);
}

void SeResponseTest::constructorATRNull() 
{
    std::shared_ptr<SeResponse> response = std::make_shared<SeResponse>(
        true,
        std::make_shared<SelectionStatus>(nullptr, ApduResponseTest::getAFCI(),
                                          true),
        ApduResponseTest::getAListOfAPDUs());
    ASSERT_EQ(response, nullptr);
}

void SeResponseTest::constructorFCINull() 
{
    std::shared_ptr<SeResponse> response = std::make_shared<SeResponse>(
        true,
        std::make_shared<SelectionStatus>(ApduResponseTest::getAAtr(), nullptr,
                                          true),
        ApduResponseTest::getAListOfAPDUs());
    ASSERT_EQ(response, nullptr);
}

void SeResponseTest::constructorFCIAndATRNull() 
{
    std::shared_ptr<SeResponse> response = std::make_shared<SeResponse>(
        true, std::make_shared<SelectionStatus>(nullptr, nullptr, true),
        ApduResponseTest::getAListOfAPDUs());
    ASSERT_EQ(response, nullptr);
}

void SeResponseTest::testEquals() 
{
    ASSERT_TRUE(getASeResponse()->equals(getASeResponse()));
}

void SeResponseTest::testThisEquals() 
{
    std::shared_ptr<SeResponse> resp = getASeResponse();
    ASSERT_TRUE(resp->equals(resp));
}

void SeResponseTest::testNotEquals() 
{
    std::shared_ptr<SeResponse> resp = getASeResponse();
    std::shared_ptr<void> any;
    ASSERT_FALSE(resp->equals(any));
}

void SeResponseTest::testNotEqualsNull()
{
    std::shared_ptr<SeResponse> resp     = getASeResponse();
    std::shared_ptr<SeResponse> respNull = std::make_shared<SeResponse>(
        true,
        std::make_shared<SelectionStatus>(nullptr, ApduResponseTest::getAFCI(),
                                          true),
        nullptr);
    std::shared_ptr<SeResponse> respNull2 = std::make_shared<SeResponse>(
        true,
        std::make_shared<SelectionStatus>(ApduResponseTest::getAAtr(), nullptr,
                                          true),
        nullptr);
    std::shared_ptr<SeResponse> respNull3 = std::make_shared<SeResponse>(
        true,
        std::make_shared<SelectionStatus>(ApduResponseTest::getAAtr(),
                                          ApduResponseTest::getAFCI(), true),
        nullptr);
    ASSERT_FALSE(resp->equals(respNull));
    ASSERT_FALSE(resp->equals(respNull2));
    ASSERT_FALSE(resp->equals(respNull3));
}

void SeResponseTest::hashcode() 
{
    std::shared_ptr<SeResponse> resp  = getASeResponse();
    std::shared_ptr<SeResponse> resp2 = getASeResponse();
    ASSERT_TRUE(resp->hashCode() == resp2->hashCode());
}

void SeResponseTest::hashcodeNull() 
{
    std::shared_ptr<SeResponse> resp = std::make_shared<SeResponse>(
        true,
        std::make_shared<SelectionStatus>(nullptr, ApduResponseTest::getAFCI(),
                                          true),
        nullptr);
    ASSERT_NE(resp->hashCode(), 0);
}

std::shared_ptr<SeResponse>
SeResponseTest::getASeResponse() 
{
    return std::make_shared<SeResponse>(
        true,
        std::make_shared<SelectionStatus>(ApduResponseTest::getAAtr(),
                                          ApduResponseTest::getAFCI(), true),
        ApduResponseTest::getAListOfAPDUs());
}
}
}
}
}

