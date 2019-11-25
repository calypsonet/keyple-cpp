#include "AbstractPoCommandBuilderTest.h"


using namespace keyple::calypso::command::po;

    namespace keyple {
        namespace calypso {
            namespace command {
                namespace po {
                    using namespace testing;

                    int AbstractPoCommandBuilderTest::sample()
                    {
                        std::shared_ptr<AbstractPoCommandBuilder> pLocal = std::make_shared<AbstractPoCommandBuilder>();
                        return (int)pLocal->getValue();
                    }
                }
            }
        }
    }


TEST(AbstractPoCommandBuilderTest, testA) 
{
    std::shared_ptr<AbstractPoCommandBuilderTest> LocalTest = std::make_shared<AbstractPoCommandBuilderTest>();
    int local = LocalTest->sample();

    ASSERT_NE( local, 1);
    ASSERT_EQ( local, 'X');
}
