
#include "TLVTest.h"

        namespace keyple {
            namespace core {
                namespace util {

                    using namespace testing;
                    using namespace bertlv;

                    int TLVTest::sample()
                    {
                        std::vector<char> local = {'A', 'B', 'C', 'D'};

                        TLV pLocal = TLV( local );
                        //pLocal.parse();
                        int iOffset = pLocal.getPosition();

                        return iOffset;
                    }
                }
            }
        }
