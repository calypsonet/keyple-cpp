#include "CalypsoBuilderParserTest.h"


using namespace keyple::calypso::command;

        namespace keyple {
            namespace calypso {
                namespace command {   
                    using namespace testing;

                    int CalypsoBuilderParserTest::sample()
                    {
                        std::shared_ptr<CalypsoBuilderParser> pLocal = std::make_shared<CalypsoBuilderParser>();

                        return (int)pLocal->getKvc();
                    }
                }
            }
        }


TEST(CalypsoBuilderParserTest, testA) 
{
    std::shared_ptr<CalypsoBuilderParserTest> LocalTest = std::make_shared<CalypsoBuilderParserTest>();
    int local = LocalTest->sample();

    ASSERT_NE( local, 1);
    ASSERT_EQ( local, 0);
}
