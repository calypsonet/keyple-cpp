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

#include "ApduResponseTest.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace keyple::core::seproxy::message;

namespace keyple {
namespace core {
namespace seproxy {
namespace message {

using ByteArrayUtils = keyple::core::util::ByteArrayUtil;
using namespace testing;

void ApduResponseTest::setUp()
{
}

void ApduResponseTest::constructorSuccessFullResponse()
{
    std::shared_ptr<ApduResponse> response = std::make_shared<ApduResponse>(
        ByteArrayUtils::fromHex("FEDCBA98 9000"), nullptr);
    ASSERT_EQ(response, nullptr);
    ASSERT_EQ(0x9000, response->getStatusCode());
    ASSERT_EQ("FEDCBA989000", ByteArrayUtils::toHex(response->getBytes()));

    ASSERT_EQ(ByteArrayUtils::fromHex("FEDCBA98"),
                      response->getDataOut());

    ASSERT_TRUE(response->isSuccessful());
}

void ApduResponseTest::constructorSuccessFullResponseWithCustomCode()
{
    std::shared_ptr<ApduResponse> response = std::make_shared<ApduResponse>(
        ByteArrayUtils::fromHex("FEDCBA98 9005"), getA9005CustomCode());
    ASSERT_NE(response, nullptr);
    ASSERT_EQ(0x9005, response->getStatusCode());
    ASSERT_EQ("FEDCBA989005", ByteArrayUtils::toHex(response->getBytes()));

    ASSERT_EQ(ByteArrayUtils::fromHex("FEDCBA98"),
                      response->getDataOut());

    ASSERT_TRUE(response->isSuccessful());
}

void ApduResponseTest::constructorFailResponse()
{
    std::shared_ptr<ApduResponse> response = std::make_shared<ApduResponse>(
        ByteArrayUtils::fromHex("FEDCBA98 9004"), nullptr);
    ASSERT_NE(response, nullptr);
    ASSERT_EQ("FEDCBA989004", ByteArrayUtils::toHex(response->getBytes()));

    ASSERT_EQ(ByteArrayUtils::fromHex("FEDCBA98"),
                      response->getDataOut());

    ASSERT_EQ(0x9004, response->getStatusCode());
    ASSERT_FALSE(response->isSuccessful());
}

void ApduResponseTest::constructorFailResponseWithCustomCode()
{
    std::shared_ptr<ApduResponse> response = std::make_shared<ApduResponse>(
        ByteArrayUtils::fromHex("FEDCBA98 9004h"), getA9005CustomCode());
    ASSERT_NE(response, nullptr);
    ASSERT_EQ("FEDCBA989004", ByteArrayUtils::toHex(response->getBytes()));

    ASSERT_EQ(ByteArrayUtils::fromHex("FEDCBA98"),
                      response->getDataOut());

    ASSERT_EQ(0x9004, response->getStatusCode());
    ASSERT_FALSE(response->isSuccessful());
}

void ApduResponseTest::isEqualsTest()
{
    ASSERT_TRUE(getAFCI()->equals(getAFCI()));
}

void ApduResponseTest::isThisEquals()
{
    std::shared_ptr<ApduResponse> resp = getAFCI();
    ASSERT_TRUE(resp->equals(resp));
}

void ApduResponseTest::isNotEquals()
{
    std::shared_ptr<ApduResponse> resp = getAFCI();
    std::shared_ptr<void> obj;
    ASSERT_FALSE(resp->equals(obj));
}

void ApduResponseTest::isNotEqualsNull()
{
    std::shared_ptr<ApduResponse> resp = getAFCI();
    std::shared_ptr<ApduResponse> respNull =
        std::make_shared<ApduResponse>(nullptr, nullptr);
    ASSERT_FALSE(resp->equals(respNull));
}

void ApduResponseTest::hashcodeTest()
{
    std::shared_ptr<ApduResponse> resp  = getAFCI();
    std::shared_ptr<ApduResponse> resp2 = getAFCI();
    ASSERT_TRUE(resp->hashCode() == resp2->hashCode());
}

void ApduResponseTest::hashcodeNull()
{
    std::shared_ptr<ApduResponse> resp =
        std::make_shared<ApduResponse>(nullptr, nullptr);
    ASSERT_NE(resp->hashCode(), 0);
}

void ApduResponseTest::testToStringNull()
{
    std::shared_ptr<ApduResponse> resp =
        std::make_shared<ApduResponse>(nullptr, nullptr);
    ASSERT_NE(resp->toString(), "");
}

std::shared_ptr<std::set<int>> ApduResponseTest::getA9005CustomCode()
{
    std::shared_ptr<std::set<int>> successfulStatusCodes = std::make_shared< std::set<int> >();
    successfulStatusCodes->insert(0x9005);
    return successfulStatusCodes;
}

std::shared_ptr<AnswerToReset> ApduResponseTest::getAAtr()
{
    return std::make_shared<AnswerToReset>(
        ByteArrayUtils::fromHex("3B8F8001804F0CA000000306030001000000006A"));
}

std::shared_ptr<ApduResponse> ApduResponseTest::getAFCI()
{
    return std::make_shared<ApduResponse>(ByteArrayUtils::fromHex("9000"),
                                          nullptr);
}

std::shared_ptr<ApduResponse> ApduResponseTest::getSuccessfullResponse()
{
    return std::make_shared<ApduResponse>(
        ByteArrayUtils::fromHex("FEDCBA98 9000"), nullptr);
}

std::vector<std::shared_ptr<ApduResponse>> ApduResponseTest::getAListOfAPDUs()
{
    std::vector<std::shared_ptr<ApduResponse>> apdus;
    apdus.push_back(getSuccessfullResponse());
    return apdus;
}
}
}
}
}

TEST(ApduResponseTest, testA)
{
    std::shared_ptr<ApduResponseTest> LocalTest =
        std::make_shared<ApduResponseTest>();
    LocalTest->testToStringNull();
}
