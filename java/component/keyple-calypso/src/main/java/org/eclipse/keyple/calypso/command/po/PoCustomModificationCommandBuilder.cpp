#include "PoCustomModificationCommandBuilder.h"
#include "../../../../../../../../../../keyple-core/src/main/java/org/eclipse/keyple/seproxy/message/ApduRequest.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace calypso {
                namespace command {
                    namespace po {
                        using AbstractIso7816CommandBuilder = org::eclipse::keyple::command::AbstractIso7816CommandBuilder;
                        using ApduRequest = org::eclipse::keyple::seproxy::message::ApduRequest;

                        PoCustomModificationCommandBuilder::PoCustomModificationCommandBuilder(const std::string &name, std::shared_ptr<ApduRequest> request) : org::eclipse::keyple::command::AbstractIso7816CommandBuilder("PO Custom Modification Command: " + name, request) {
                        }
                    }
                }
            }
        }
    }
}
