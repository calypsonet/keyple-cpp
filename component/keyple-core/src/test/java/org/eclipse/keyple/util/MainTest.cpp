/*
 * Copyright (c) 2018 Calypso Networks Association https://www.calypsonet-asso.org/
 *
 * All rights reserved. This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License version 2.0 which accompanies this distribution, and is
 * available at https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "TLVTest.h"

using namespace testing;
using namespace keyple::core::util;

//TEST(TLVTest, testA) 
//{
//    std::shared_ptr<TLVTest> LocalTest = std::make_shared<TLVTest>();
//    int local = LocalTest->sample();

//    ASSERT_NE( local, 0);
//    ASSERT_EQ( local, 4);
//}

int main(int argc, char **argv)
{
    /* Initialize GTest */
    ::InitGoogleTest(&argc, argv);

    /* Run */
    return RUN_ALL_TESTS();
}
