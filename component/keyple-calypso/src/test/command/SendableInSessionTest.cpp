#include "SendableInSessionTest.h"


using namespace keyple::calypso::command;

        namespace keyple {
            namespace calypso {
                namespace command {
                    using namespace testing;

                    int SendableInSessionTest::sample()
                    {
                        std::shared_ptr<SendableInSession> pLocal = std::make_shared<SendableInSession>();
                        return 0;
                    }
                }
            }
        }


TEST(SendableInSessionTest, testA) 
{
    std::shared_ptr<SendableInSessionTest> LocalTest = std::make_shared<SendableInSessionTest>();
    int local = LocalTest->sample();

    ASSERT_NE( local, 1);
    ASSERT_EQ( local, 0);
}
