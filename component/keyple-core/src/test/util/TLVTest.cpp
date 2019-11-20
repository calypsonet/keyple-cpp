
#include "TLVTest.h"

using namespace keyple::core::util;

        namespace keyple {
            namespace core {
                namespace util {

                    using namespace testing;
                    using namespace bertlv;

                    int TLVTest::sample()
                    {
                        std::vector<char> local = {'A', 'B', 'C', 'D'};
                        std::shared_ptr<Tag> tag = std::make_shared<Tag>(local, 0);

                        TLV pLocal = TLV( local );
                        int iOffset = pLocal.getPosition();
                        bool bLocal = pLocal.parse(tag, iOffset);
                        pLocal.toString();
                        local = pLocal.getValue();

                        if ( bLocal ) iOffset = 0;
                        return iOffset;
                    }
                }
            }
        }

TEST(TLVTest, testA) 
{
    std::shared_ptr<TLVTest> LocalTest = std::make_shared<TLVTest>();
    int local = LocalTest->sample();

    ASSERT_NE( local, 1);
    ASSERT_EQ( local, 0);
}
