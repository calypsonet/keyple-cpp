#include "CalypsoSamTest.h"
#include "SeCommonProtocols_Import.h"
#include "SamSelectionRequest.h"
#include "ChannelState.h"
#include "CalypsoSam.h"
#include "AnswerToReset.h"
#include "SelectionStatus.h"
#include "ByteArrayUtil.h"
#include "SeResponse.h"

using namespace keyple::calypso::transaction;

        namespace keyple {
            namespace calypso {
                namespace transaction {

                    using SamSelectionRequest = keyple::calypso::transaction::SamSelectionRequest;
                    using ChannelState = keyple::core::seproxy::ChannelState;
                    using SeSelector = keyple::core::seproxy::SeSelector;
                    using AnswerToReset = keyple::core::seproxy::message::AnswerToReset;
                    using SeResponse = keyple::core::seproxy::message::SeResponse;
                    using SelectionStatus = keyple::core::seproxy::message::SelectionStatus;
                    using ByteArrayUtils = keyple::core::util::ByteArrayUtil;
                    using ContactlessProtocols = SeCommonProtocols;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test_CalypsoSam_1()
                    void CalypsoSamTest::test_CalypsoSam_1() {
                        std::shared_ptr<SeSelector> seSelector = std::make_shared<SeSelector>(nullptr, nullptr, "Dummy SeSelector");
                        std::shared_ptr<SamSelectionRequest> samSelectionRequest = std::make_shared<SamSelectionRequest>(seSelector, ChannelState::KEEP_OPEN, SeCommonProtocols::PROTOCOL_ISO14443_4);
                        std::shared_ptr<CalypsoSam> calypsoSam = std::make_shared<CalypsoSam>(samSelectionRequest);
                        std::shared_ptr<SelectionStatus> selectionStatus = std::make_shared<SelectionStatus>(std::make_shared<AnswerToReset>(ByteArrayUtils::fromHex("3B001122805A0180D002030411223344829000")), nullptr, true);
                        calypsoSam->setSelectionResponse(std::make_shared<SeResponse>(true, selectionStatus, nullptr));
                        ASSERT_EQ(SamRevision::S1D, calypsoSam->getSamRevision());
                        ASSERT_EQ(static_cast<char>(0x80), calypsoSam->getApplicationType());
                        ASSERT_EQ(static_cast<char>(0xD0), calypsoSam->getApplicationSubType());
                        ASSERT_EQ(static_cast<char>(0x01), calypsoSam->getPlatform());
                        ASSERT_EQ(static_cast<char>(0x02), calypsoSam->getSoftwareIssuer());
                        ASSERT_EQ(static_cast<char>(0x03), calypsoSam->getSoftwareVersion());
                        ASSERT_EQ(static_cast<char>(0x04), calypsoSam->getSoftwareRevision());
                        ASSERT_EQ("11223344", ByteArrayUtils::toHex(calypsoSam->getSerialNumber()));
                    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test_CalypsoSam_2()
                    void CalypsoSamTest::test_CalypsoSam_2() {
                        std::shared_ptr<SeSelector> seSelector = std::make_shared<SeSelector>(nullptr, nullptr, "Dummy SeSelector");
                        std::shared_ptr<SamSelectionRequest> samSelectionRequest = std::make_shared<SamSelectionRequest>(seSelector, ChannelState::KEEP_OPEN, ContactlessProtocols::PROTOCOL_ISO14443_4);
                        std::shared_ptr<CalypsoSam> calypsoSam = std::make_shared<CalypsoSam>(samSelectionRequest);
                        std::shared_ptr<SelectionStatus> selectionStatus = std::make_shared<SelectionStatus>(std::make_shared<AnswerToReset>(ByteArrayUtils::fromHex("3B001122805A0180D102030411223344829000")), nullptr, true);
                        calypsoSam->setSelectionResponse(std::make_shared<SeResponse>(true, selectionStatus, nullptr));
                        ASSERT_EQ(SamRevision::S1D, calypsoSam->getSamRevision());
                        ASSERT_EQ(static_cast<char>(0xD1), calypsoSam->getApplicationSubType());
                    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test_CalypsoSam_3()
                    void CalypsoSamTest::test_CalypsoSam_3() {
                        std::shared_ptr<SeSelector> seSelector = std::make_shared<SeSelector>(nullptr, nullptr, "Dummy SeSelector");
                        std::shared_ptr<SamSelectionRequest> samSelectionRequest = std::make_shared<SamSelectionRequest>(seSelector, ChannelState::KEEP_OPEN, ContactlessProtocols::PROTOCOL_ISO14443_4);
                        std::shared_ptr<CalypsoSam> calypsoSam = std::make_shared<CalypsoSam>(samSelectionRequest);
                        std::shared_ptr<SelectionStatus> selectionStatus = std::make_shared<SelectionStatus>(std::make_shared<AnswerToReset>(ByteArrayUtils::fromHex("3B001122805A0180D202030411223344829000")), nullptr, true);
                        calypsoSam->setSelectionResponse(std::make_shared<SeResponse>(true, selectionStatus, nullptr));
                        ASSERT_EQ(SamRevision::S1D, calypsoSam->getSamRevision());
                        ASSERT_EQ(static_cast<char>(0xD2), calypsoSam->getApplicationSubType());
                    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test_CalypsoSam_4()
                    void CalypsoSamTest::test_CalypsoSam_4() {
                        std::shared_ptr<SeSelector> seSelector = std::make_shared<SeSelector>(nullptr, nullptr, "Dummy SeSelector");
                        std::shared_ptr<SamSelectionRequest> samSelectionRequest = std::make_shared<SamSelectionRequest>(seSelector, ChannelState::KEEP_OPEN, ContactlessProtocols::PROTOCOL_ISO14443_4);
                        std::shared_ptr<CalypsoSam> calypsoSam = std::make_shared<CalypsoSam>(samSelectionRequest);
                        std::shared_ptr<SelectionStatus> selectionStatus = std::make_shared<SelectionStatus>(std::make_shared<AnswerToReset>(ByteArrayUtils::fromHex("3B001122805A0180C102030411223344829000")), nullptr, true);
                        calypsoSam->setSelectionResponse(std::make_shared<SeResponse>(true, selectionStatus, nullptr));
                        ASSERT_EQ(SamRevision::C1, calypsoSam->getSamRevision());
                        ASSERT_EQ(static_cast<char>(0xC1), calypsoSam->getApplicationSubType());
                    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test_CalypsoSam_5()
                    void CalypsoSamTest::test_CalypsoSam_5() {
                        std::shared_ptr<SeSelector> seSelector = std::make_shared<SeSelector>(nullptr, nullptr, "Dummy SeSelector");
                        std::shared_ptr<SamSelectionRequest> samSelectionRequest = std::make_shared<SamSelectionRequest>(seSelector, ChannelState::KEEP_OPEN, ContactlessProtocols::PROTOCOL_ISO14443_4);
                        std::shared_ptr<CalypsoSam> calypsoSam = std::make_shared<CalypsoSam>(samSelectionRequest);
                        std::shared_ptr<SelectionStatus> selectionStatus = std::make_shared<SelectionStatus>(std::make_shared<AnswerToReset>(ByteArrayUtils::fromHex("3B001122805A0180E102030411223344829000")), nullptr, true);
                        calypsoSam->setSelectionResponse(std::make_shared<SeResponse>(true, selectionStatus, nullptr));
                        ASSERT_EQ(SamRevision::S1E, calypsoSam->getSamRevision());
                        ASSERT_EQ(static_cast<char>(0xE1), calypsoSam->getApplicationSubType());
                    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test(expected = IllegalStateException.class) public void test_CalypsoSam_6()
                    void CalypsoSamTest::test_CalypsoSam_6() {
                        std::shared_ptr<SeSelector> seSelector = std::make_shared<SeSelector>(nullptr, nullptr, "Dummy SeSelector");
                        std::shared_ptr<SamSelectionRequest> samSelectionRequest = std::make_shared<SamSelectionRequest>(seSelector, ChannelState::KEEP_OPEN, ContactlessProtocols::PROTOCOL_ISO14443_4);
                        std::shared_ptr<CalypsoSam> calypsoSam = std::make_shared<CalypsoSam>(samSelectionRequest);
                        std::shared_ptr<SelectionStatus> selectionStatus = std::make_shared<SelectionStatus>(std::make_shared<AnswerToReset>(ByteArrayUtils::fromHex("3B001122805A0180E202030411223344829000")), nullptr, true);
                        calypsoSam->setSelectionResponse(std::make_shared<SeResponse>(true, selectionStatus, nullptr));
                    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test(expected = IllegalStateException.class) public void test_CalypsoSam_7()
                    void CalypsoSamTest::test_CalypsoSam_7() {
                        std::shared_ptr<SeSelector> seSelector = std::make_shared<SeSelector>(nullptr, nullptr, "Dummy SeSelector");
                        std::shared_ptr<SamSelectionRequest> samSelectionRequest = std::make_shared<SamSelectionRequest>(seSelector, ChannelState::KEEP_OPEN, ContactlessProtocols::PROTOCOL_ISO14443_4);
                        std::shared_ptr<CalypsoSam> calypsoSam = std::make_shared<CalypsoSam>(samSelectionRequest);
                        std::shared_ptr<SelectionStatus> selectionStatus = std::make_shared<SelectionStatus>(std::make_shared<AnswerToReset>(ByteArrayUtils::fromHex("3B001122805A0180E202030411223344820000")), nullptr, true);
                        calypsoSam->setSelectionResponse(std::make_shared<SeResponse>(true, selectionStatus, nullptr));
                    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test(expected = IllegalStateException.class) public void test_CalypsoSam_8()
                    void CalypsoSamTest::test_CalypsoSam_8() {
                        std::shared_ptr<SeSelector> seSelector = std::make_shared<SeSelector>(nullptr, nullptr, "Dummy SeSelector");
                        std::shared_ptr<SamSelectionRequest> samSelectionRequest = std::make_shared<SamSelectionRequest>(seSelector, ChannelState::KEEP_OPEN, ContactlessProtocols::PROTOCOL_ISO14443_4);
                        std::shared_ptr<CalypsoSam> calypsoSam = std::make_shared<CalypsoSam>(samSelectionRequest);
                        std::shared_ptr<SelectionStatus> selectionStatus = std::make_shared<SelectionStatus>(std::make_shared<AnswerToReset>(ByteArrayUtils::fromHex("")), nullptr, true);
                        calypsoSam->setSelectionResponse(std::make_shared<SeResponse>(true, selectionStatus, nullptr));
                    }
                }
            }
        }

TEST(CalypsoSamTest, testA) 
{
    std::shared_ptr<CalypsoSamTest> LocalTest = std::make_shared<CalypsoSamTest>();
    LocalTest->test_CalypsoSam_1();
}

TEST(CalypsoSamTest, testB) 
{
    std::shared_ptr<CalypsoSamTest> LocalTest = std::make_shared<CalypsoSamTest>();
    LocalTest->test_CalypsoSam_2();
}

TEST(CalypsoSamTest, testC) 
{
    std::shared_ptr<CalypsoSamTest> LocalTest = std::make_shared<CalypsoSamTest>();
    LocalTest->test_CalypsoSam_3();
}

TEST(CalypsoSamTest, testD) 
{
    std::shared_ptr<CalypsoSamTest> LocalTest = std::make_shared<CalypsoSamTest>();
    LocalTest->test_CalypsoSam_4();
}

TEST(CalypsoSamTest, testE) 
{
    std::shared_ptr<CalypsoSamTest> LocalTest = std::make_shared<CalypsoSamTest>();
    LocalTest->test_CalypsoSam_5();
}

TEST(CalypsoSamTest, testF) 
{
    std::shared_ptr<CalypsoSamTest> LocalTest = std::make_shared<CalypsoSamTest>();
    LocalTest->test_CalypsoSam_6();
}

TEST(CalypsoSamTest, testG) 
{
    std::shared_ptr<CalypsoSamTest> LocalTest = std::make_shared<CalypsoSamTest>();
    LocalTest->test_CalypsoSam_7();
}

TEST(CalypsoSamTest, testH) 
{
    std::shared_ptr<CalypsoSamTest> LocalTest = std::make_shared<CalypsoSamTest>();
    LocalTest->test_CalypsoSam_8();
}
