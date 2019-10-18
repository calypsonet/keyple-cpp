/*
 * Copyright (c) 2018 Calypso Networks Association https://www.calypsonet-asso.org/
 *
 * All rights reserved. This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License version 2.0 which accompanies this distribution, and is
 * available at https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "BaseStubTest.h"
#include "StubPluginTest.h"
#include "StubPlugin.h"

using namespace testing;
using org::eclipse::keyple::plugin::stub::StubPluginTest;
using org::eclipse::keyple::plugin::stub::StubPlugin;
using org::eclipse::keyple::plugin::stub::BaseStubTest;

TEST(StubPluginTest, testA_PlugOneReaderCount) 
{
    StubPlugin stubplugin = StubPlugin::getInstance();
    stubplugin.initReaders();

    std::shared_ptr<StubPluginTest> LocalTest = std::make_shared<StubPluginTest>();

    ASSERT_NE( LocalTest, nullptr);
    LocalTest->testA_PlugOneReaderCount();
}

TEST(StubPluginTest, testA_PlugOneReaderEvent) 
{
    std::shared_ptr<StubPluginTest> LocalTest = std::make_shared<StubPluginTest>();

    LocalTest->testA_PlugOneReaderEvent();
}

TEST(StubPluginTest, testA_UnplugOneReaderCount) 
{
    std::shared_ptr<StubPluginTest> LocalTest = std::make_shared<StubPluginTest>();

    LocalTest->testA_UnplugOneReaderCount();
}

TEST(StubPluginTest, testB_UnplugOneReaderEvent) 
{
    std::shared_ptr<StubPluginTest> LocalTest = std::make_shared<StubPluginTest>();

    LocalTest->testB_UnplugOneReaderEvent();
}

int main(int argc, char **argv)
{
    /* Initialize GTest */
    ::InitGoogleTest(&argc, argv);

    /* Run */
    return RUN_ALL_TESTS();
}
