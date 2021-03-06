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

#include "TagTest.h"

using namespace keyple::core::util;

namespace keyple {
namespace core {
namespace util {

using namespace testing;
using namespace bertlv;

int TagTest::sample()
{
    std::vector<uint8_t> local = {'A', 'B', 'C', 'D'};

    Tag pLocal = Tag(local, 0);
    //pLocal.parse();
    int iOffset = pLocal.getTagNumber();

    return iOffset;
}
}
}
}

TEST(TagTest, testA)
{
    std::shared_ptr<TagTest> LocalTest = std::make_shared<TagTest>();
    int local                          = LocalTest->sample();

    ASSERT_NE(local, 0);
    ASSERT_EQ(local, 1);
}
