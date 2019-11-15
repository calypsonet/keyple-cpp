
#include "NameableTest.h"

        namespace keyple {
            namespace core {
                namespace util {

                    using namespace testing;

                    int NameableTest::sample()
                    {
                        NameableTest pLocal = NameableTest();
                        //pLocal.parse();
                        std::string szName = pLocal.getName();

                        return szName.length();
                    }
                }
            }
        }
