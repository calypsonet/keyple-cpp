/* Example */
#include "StubMifareClassic.h"

/* Core */
#include "ByteArrayUtils.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace example {
                namespace generic {
                    namespace pc {
                        namespace stub {
                            namespace se {
                                using StubSecureElement = org::eclipse::keyple::plugin::stub::StubSecureElement;
                                using ByteArrayUtils = org::eclipse::keyple::util::ByteArrayUtils;

                                const std::string StubMifareClassic::seProtocol = "PROTOCOL_MIFARE_CLASSIC";

                                StubMifareClassic::StubMifareClassic() {
                                    /* Get data */
                                    addHexCommand("FFCA 000000", "112233449000");
                                }

                                std::vector<char> StubMifareClassic::getATR() {
                                    return ByteArrayUtils::fromHex(ATR_HEX);
                                }

                                std::string StubMifareClassic::getSeProcotol() {
                                    return seProtocol;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
