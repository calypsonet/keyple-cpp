#include "CalypsoSam.h"
#include "SamSelectionRequest.h"
#include "../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/seproxy/message/SeResponse.h"
#include "../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/util/ByteArrayUtils.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace transaction {
                    namespace sam {
                        using namespace org::eclipse::keyple::calypso::command::sam;
//                        import static org.eclipse.keyple.calypso.command.sam.SamRevision.*;
                        using SamRevision = org::eclipse::keyple::calypso::command::sam::SamRevision;
                        using SeResponse = org::eclipse::keyple::seproxy::message::SeResponse;
                        using MatchingSe = org::eclipse::keyple::transaction::MatchingSe;
                        using ByteArrayUtils = org::eclipse::keyple::util::ByteArrayUtils;
                        using org::slf4j::Logger;
                        using org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> CalypsoSam::logger = org::slf4j::LoggerFactory::getLogger(CalypsoSam::typeid);

                        CalypsoSam::CalypsoSam(std::shared_ptr<SamSelectionRequest> samSelectionRequest) : org::eclipse::keyple::transaction::MatchingSe(samSelectionRequest) {
                        }

                        void CalypsoSam::setSelectionResponse(std::shared_ptr<SeResponse> selectionResponse) {
                            std::string atrString = ByteArrayUtils::toHex(selectionResponse->getSelectionStatus()->getAtr()->getBytes());
                            if (atrString.isEmpty()) {
                                throw std::make_shared<IllegalStateException>("ATR should not be empty.");
                            }
                            /* extract the historical bytes from T3 to T12 */
                            std::string extractRegex = "3B(.{6}|.{10})805A(.{20})829000";
                            std::shared_ptr<Pattern> pattern = Pattern::compile(extractRegex);
                            std::shared_ptr<Matcher> matcher = pattern->matcher(atrString);
                            if (matcher->find(0)) {
                                std::vector<char> atrSubElements = ByteArrayUtils::fromHex(matcher->group(2));
                                platform = atrSubElements[0];
                                applicationType = atrSubElements[1];
                                applicationSubType = atrSubElements[2];

                                // determine SAM revision from Application Subtype
                                switch (applicationSubType) {
                                    case static_cast<char>(0xC1):
                                        samRevision = C1;
                                        break;
                                    case static_cast<char>(0xD0):
                                    case static_cast<char>(0xD1):
                                    case static_cast<char>(0xD2):
                                        samRevision = S1D;
                                        break;
                                    case static_cast<char>(0xE1):
                                        samRevision = S1E;
                                        break;
                                    default:
                                        throw std::make_shared<IllegalStateException>(std::string::format("Unknown SAM revision (unrecognized application subtype 0x%02X)", applicationSubType));
                                }

                                softwareIssuer = atrSubElements[3];
                                softwareVersion = atrSubElements[4];
                                softwareRevision = atrSubElements[5];
                                System::arraycopy(atrSubElements, 6, serialNumber, 0, 4);
                                if (logger->isTraceEnabled()) {
                                    logger->trace(std::string::format(std::string("SAM %s PLATFORM = %02X, APPTYPE = %02X, APPSUBTYPE = %02X, SWISSUER = %02X, SWVERSION = ") + "%02X, SWREVISION = %02X", samRevision.getName(), platform, applicationType, applicationSubType, softwareIssuer, softwareVersion, softwareRevision));
                                    logger->trace("SAM SERIALNUMBER = {}", ByteArrayUtils::toHex(serialNumber));
                                }
                            }
                            else {
                                throw std::make_shared<IllegalStateException>("Unrecognized ATR structure: " + atrString);
                            }
                        }

                        SamRevision CalypsoSam::getSamRevision() {
                            return samRevision;
                        }

                        std::vector<char> CalypsoSam::getSerialNumber() {
                            return serialNumber;
                        }

                        char CalypsoSam::getPlatform() {
                            return platform;
                        }

                        char CalypsoSam::getApplicationType() {
                            return applicationType;
                        }

                        char CalypsoSam::getApplicationSubType() {
                            return applicationSubType;
                        }

                        char CalypsoSam::getSoftwareIssuer() {
                            return softwareIssuer;
                        }

                        char CalypsoSam::getSoftwareVersion() {
                            return softwareVersion;
                        }

                        char CalypsoSam::getSoftwareRevision() {
                            return softwareRevision;
                        }
                    }
                }
            }
        }
    }
}
