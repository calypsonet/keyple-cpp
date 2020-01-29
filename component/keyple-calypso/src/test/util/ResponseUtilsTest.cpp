#include "ResponseUtilsTest.h"
#include "AbstractOpenSessionRespPars.h"
#include "OpenSession32RespPars.h"
#include "OpenSession24RespPars.h"
#include "ByteArrayUtil.h"

        namespace keyple {
            namespace calypso {
                namespace util {
                    using AbstractOpenSessionRespPars = keyple::calypso::command::po::parser::security::AbstractOpenSessionRespPars;
                    using OpenSession24RespPars = keyple::calypso::command::po::parser::security::OpenSession24RespPars;
                    using OpenSession32RespPars = keyple::calypso::command::po::parser::security::OpenSession32RespPars;
                    using ByteArrayUtils = keyple::core::util::ByteArrayUtils;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void TestToSecureSession()
                    void ResponseUtilsTest::TestToSecureSession() {
                        std::vector<char> apduResponse = {static_cast<char>(0x8F), 0x05, 0x75, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x7E, static_cast<char>(0x1D), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

                        std::vector<char> transactionCounter = {static_cast<char>(0x8F), 0x05, 0x75};
                        std::vector<char> randomNumber = {0x1A, 0x00, 0x00, 0x00, 0x00};
                        char kif = 0x00;
                        char kvc = static_cast<char>(0x00);

                        bool isPreviousSessionRatifiedExpected = true;
                        bool isManageSecureSessionAuthorizedExpected = false;
                        std::vector<char> originalData(0);

                        std::shared_ptr<AbstractOpenSessionRespPars::SecureSession> SecureSessionExpected = std::make_shared<AbstractOpenSessionRespPars::SecureSession>(transactionCounter, randomNumber, isPreviousSessionRatifiedExpected, isManageSecureSessionAuthorizedExpected, kif, kvc, originalData, apduResponse);
                        std::shared_ptr<AbstractOpenSessionRespPars::SecureSession> SecureSessionTested = OpenSession32RespPars::createSecureSession(apduResponse);

                        Assert::assertArrayEquals(SecureSessionExpected->getOriginalData(), SecureSessionTested->getOriginalData());
                        Assert::assertArrayEquals(SecureSessionExpected->getSecureSessionData(), SecureSessionTested->getSecureSessionData());
                        Assert::assertEquals(SecureSessionExpected->getKIF(), SecureSessionTested->getKIF());
                        Assert::assertEquals(SecureSessionExpected->getKVC(), SecureSessionTested->getKVC());
                        Assert::assertArrayEquals(SecureSessionExpected->getChallengeRandomNumber(), SecureSessionTested->getChallengeRandomNumber());
                        Assert::assertArrayEquals(SecureSessionExpected->getChallengeTransactionCounter(), SecureSessionTested->getChallengeTransactionCounter());
                    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void TestToSecureSessionRev2()
                    void ResponseUtilsTest::TestToSecureSessionRev2() {

                        // Case Else
                        std::vector<char> apduResponse = {static_cast<char>(0x7E), static_cast<char>(0x03), static_cast<char>(0x0D), static_cast<char>(0x14), static_cast<char>(0x53)};

                        std::vector<char> transactionCounter = {static_cast<char>(0x03), static_cast<char>(0x0D), static_cast<char>(0x14)};
                        std::vector<char> randomNumber = {static_cast<char>(0x53)};
                        char kvc = static_cast<char>(0x7E);

                        bool isPreviousSessionRatifiedExpected = false;
                        bool isManageSecureSessionAuthorizedExpected = false;
                        std::vector<char> originalData;

                        std::shared_ptr<AbstractOpenSessionRespPars::SecureSession> SecureSessionExpected = std::make_shared<AbstractOpenSessionRespPars::SecureSession>(transactionCounter, randomNumber, isPreviousSessionRatifiedExpected, isManageSecureSessionAuthorizedExpected, kvc, originalData, apduResponse);
                        std::shared_ptr<AbstractOpenSessionRespPars::SecureSession> SecureSessionTested = OpenSession24RespPars::createSecureSession(apduResponse);

                        Assert::assertEquals(SecureSessionExpected->getSecureSessionData(), SecureSessionTested->getSecureSessionData());
                        Assert::assertEquals(SecureSessionExpected->getKVC(), SecureSessionTested->getKVC());
                        Assert::assertArrayEquals(SecureSessionExpected->getChallengeRandomNumber(), SecureSessionTested->getChallengeRandomNumber());
                        Assert::assertArrayEquals(SecureSessionExpected->getChallengeTransactionCounter(), SecureSessionTested->getChallengeTransactionCounter());

                        // Case If Else
                        // byte[] apduResponseCaseTwo = new byte[] {(byte) 0x7E, (byte) 0x03, (byte) 0x0D, (byte)
                        // 0x14,
                        // (byte) 0x53, (byte) 0x30, 0x00, 0x04, 0x01, 0x02, 0x03, 0x04};
                        // byte[] originalDataCaseTwo = new byte[] {(byte) 0x7E, (byte) 0x03, (byte) 0x0D, (byte)
                        // 0x14,
                        // (byte) 0x53, (byte) 0xFF, 0x00, 0x04, 0x01, 0x02, 0x03, 0x04};
                        std::vector<char> apduResponseCaseTwo = ByteArrayUtils::fromHex("7E 030D1453 9999 00112233445566778899AABBCCDDEEFF 00112233445566778899AABBCC");
                        std::vector<char> originalDataCaseTwo = ByteArrayUtils::fromHex("7E 030D1453 9999 00112233445566778899AABBCCDDEEFF 00112233445566778899AABBCC");

                        std::shared_ptr<AbstractOpenSessionRespPars::SecureSession> SecureSessionExpectedCaseTwo = std::make_shared<AbstractOpenSessionRespPars::SecureSession>(transactionCounter, randomNumber, isPreviousSessionRatifiedExpected, isManageSecureSessionAuthorizedExpected, kvc, originalDataCaseTwo, apduResponseCaseTwo);
                        std::shared_ptr<AbstractOpenSessionRespPars::SecureSession> SecureSessionTestedCaseTwo = OpenSession24RespPars::createSecureSession(apduResponseCaseTwo);

                        Assert::assertEquals(SecureSessionExpectedCaseTwo->getSecureSessionData(), SecureSessionTestedCaseTwo->getSecureSessionData());
                        Assert::assertEquals(SecureSessionExpectedCaseTwo->getKVC(), SecureSessionTestedCaseTwo->getKVC());
                        Assert::assertArrayEquals(SecureSessionExpectedCaseTwo->getChallengeRandomNumber(), SecureSessionTestedCaseTwo->getChallengeRandomNumber());
                        Assert::assertArrayEquals(SecureSessionExpectedCaseTwo->getChallengeTransactionCounter(), SecureSessionTestedCaseTwo->getChallengeTransactionCounter());

                        // Case If If
                        // byte[] apduResponseCaseThree = new byte[] {(byte) 0x7E, (byte) 0x03, (byte) 0x0D,
                        // (byte) 0x14, (byte) 0x53, (byte) 0xFF, 0x00, 0x04, 0x01, 0x02, 0x03, 0x04};
                        // byte[] originalDataCaseThree = new byte[] {(byte) 0x7E, (byte) 0x03, (byte) 0x0D,
                        // (byte) 0x14, (byte) 0x53, (byte) 0xFF, 0x00, 0x04, 0x01, 0x02, 0x03, 0x04};

                        std::vector<char> apduResponseCaseThree = ByteArrayUtils::fromHex("7E 030D1453 9999 00112233445566778899AABBCCDDEEFF 00112233445566778899AABBCC");
                        std::vector<char> originalDataCaseThree = ByteArrayUtils::fromHex("7E 030D1453 9999 00112233445566778899AABBCCDDEEFF 00112233445566778899AABBCC");

                        std::shared_ptr<AbstractOpenSessionRespPars::SecureSession> SecureSessionExpectedCaseThree = std::make_shared<AbstractOpenSessionRespPars::SecureSession>(transactionCounter, randomNumber, isPreviousSessionRatifiedExpected, isManageSecureSessionAuthorizedExpected, kvc, originalDataCaseThree, apduResponseCaseThree);
                        std::shared_ptr<AbstractOpenSessionRespPars::SecureSession> SecureSessionTestedCaseThree = OpenSession24RespPars::createSecureSession(apduResponseCaseThree);

                        Assert::assertEquals(SecureSessionExpectedCaseThree->getSecureSessionData(), SecureSessionTestedCaseThree->getSecureSessionData());
                        Assert::assertEquals(SecureSessionExpectedCaseThree->getKVC(), SecureSessionTestedCaseThree->getKVC());
                        Assert::assertArrayEquals(SecureSessionExpectedCaseThree->getChallengeRandomNumber(), SecureSessionTestedCaseThree->getChallengeRandomNumber());
                        Assert::assertArrayEquals(SecureSessionExpectedCaseThree->getChallengeTransactionCounter(), SecureSessionTestedCaseThree->getChallengeTransactionCounter());
                    }
                }
            }
        }
