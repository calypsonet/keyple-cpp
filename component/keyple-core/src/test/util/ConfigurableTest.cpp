
#include "ConfigurableTest.h"

        namespace keyple {
            namespace core {
                namespace util {

                    using namespace testing;

                    int ConfigurableTest::sample()
                    {
                        std::vector<char> local = {'A', 'B', 'C', 'D'};
                        std::string szValue = "X"; 

                        //Configurable pLocal = Configurable( local );
                        //pLocal.parse();
                        int iOffset = 0;//pLocal::setParameter( "TEST", szValue );

                        return iOffset;
                    }
                }
            }
        }
