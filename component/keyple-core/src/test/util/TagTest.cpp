
#include "TagTest.h"

        namespace keyple {
            namespace core {
                namespace util {

                    using namespace testing;
                    using namespace bertlv;

                    int TagTest::sample()
                    {
                        std::vector<char> local = {'A', 'B', 'C', 'D'};

                        Tag pLocal = Tag( local, 0 );
                        //pLocal.parse();
                        int iOffset = pLocal.getTagNumber();

                        return iOffset;
                    }
                }
            }
        }
