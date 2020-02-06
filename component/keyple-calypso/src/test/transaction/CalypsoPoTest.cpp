#include "CalypsoPoTest.h"

using namespace keyple::calypso::transaction;

        namespace keyple {
            namespace calypso {
                namespace transaction {
                    using PoRevision = keyple::calypso::command::po::PoRevision;
                    using ChannelState = keyple::core::seproxy::ChannelState;
                    using SeSelector = keyple::core::seproxy::SeSelector;
                    using ApduResponse = keyple::core::seproxy::message::ApduResponse;
                    using SeResponse = keyple::core::seproxy::message::SeResponse;
                    using SelectionStatus = keyple::core::seproxy::message::SelectionStatus;
                    using SeCommonProtocols = keyple::core::seproxy::protocol::SeCommonProtocols;
                    using ByteArrayUtils = keyple::core::util::ByteArrayUtil;
                    using IsoAid = keyple::core::seproxy::SeSelector::AidSelector::IsoAid;


                    std::shared_ptr<CalypsoPo> CalypsoPoTest::getPoApplicationByte(char applicationByte) {
                        std::string szResp = std::string("6F 22 84 08 315449432E494341 A5 16 BF0C 13 C7 08 0000000011223344 53 07 060A %02X 02200311 9000", applicationByte);
                        std::vector<char> cResp = ByteArrayUtils::fromHex(szResp);
                        std::shared_ptr<IsoAid> cAID = std::make_shared<IsoAid>(ByteArrayUtils::fromHex("315449432E494341"));
                        std::shared_ptr<ApduResponse> fciData = std::make_shared<ApduResponse>(cResp, nullptr);
                        std::vector<std::shared_ptr<ApduResponse>> apduVecteurReponseVide;
                        std::shared_ptr<SeResponse> selectionData = std::make_shared<SeResponse>(false, true, std::make_shared<SelectionStatus>(nullptr, fciData, true), apduVecteurReponseVide);
                        std::shared_ptr<PoSelectionRequest> poSelectionRequest = std::make_shared<PoSelectionRequest>(std::make_shared<SeSelector>(std::make_shared<SeSelector::AidSelector>(cAID, nullptr), nullptr, nullptr), ChannelState::KEEP_OPEN, SeCommonProtocols::PROTOCOL_ISO14443_4);
                        std::shared_ptr<CalypsoPo> calypsoPo = std::make_shared<CalypsoPo>(poSelectionRequest);
                        calypsoPo->SetSelectionResponse(selectionData);
                        return calypsoPo;
                    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void computePoRevision()
                    void CalypsoPoTest::computePoRevision() {
                        ASSERT_EQ(getPoApplicationByte(static_cast<char>(0x01))->getRevision(), PoRevision::REV2_4);

                        ASSERT_EQ(getPoApplicationByte(static_cast<char>(0x04))->getRevision(), PoRevision::REV2_4);

                        ASSERT_EQ(getPoApplicationByte(static_cast<char>(0x06))->getRevision(), PoRevision::REV2_4);

                        ASSERT_EQ(getPoApplicationByte(static_cast<char>(0x1F))->getRevision(), PoRevision::REV2_4);

                        ASSERT_EQ(getPoApplicationByte(static_cast<char>(0x20))->getRevision(), PoRevision::REV3_1);

                        ASSERT_EQ(getPoApplicationByte(static_cast<char>(0x27))->getRevision(), PoRevision::REV3_1);

                        ASSERT_EQ(getPoApplicationByte(static_cast<char>(0x28))->getRevision(), PoRevision::REV3_2);

                        ASSERT_EQ(getPoApplicationByte(static_cast<char>(0x2F))->getRevision(), PoRevision::REV3_2);
                    }
                }
            }
        }

TEST(CalypsoPoTest, testA) 
{
    std::shared_ptr<CalypsoPoTest> LocalTest = std::make_shared<CalypsoPoTest>();
    LocalTest->computePoRevision();
}
