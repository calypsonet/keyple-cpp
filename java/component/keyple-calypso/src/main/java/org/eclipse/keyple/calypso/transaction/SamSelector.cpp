/* Core */
#include "SeCommonProtocols.h"

/* Calypso */
#include "SamSelector.h"

namespace org {
namespace eclipse {
namespace keyple {
namespace calypso {
namespace transaction {

using namespace org::eclipse::keyple::calypso::command::sam;
using namespace org::eclipse::keyple::core::seproxy;
using namespace org::eclipse::keyple::core::seproxy::protocol;

SamSelector::SamSelector(SamRevision samRevision, const std::string &serialNumber, const std::string &extraInfo)
: SeSelector(std::shared_ptr<SeProtocol>(std::make_shared<SeCommonProtocols>(SeCommonProtocols::PROTOCOL_ISO7816_3)), nullptr, nullptr,
             extraInfo)
{
    std::string atrRegex;
    std::string snRegex;

    /* check if serialNumber is defined */
    if (serialNumber == "" || serialNumber.empty()) {
        /* match all serial numbers */
        snRegex = ".{8}";
    } else {
        /* match the provided serial number (could be a regex substring) */
        snRegex = serialNumber;
    }

    /*
     * build the final Atr regex according to the SAM subtype and serial number if any.
     *
     * The header is starting with 3B, its total length is 4 or 6 bytes (8 or 10 hex digits)
     */
    switch (samRevision.innerEnumValue) {
    case SamRevision::InnerEnum::C1:
    case SamRevision::InnerEnum::S1D:
    case SamRevision::InnerEnum::S1E:
        atrRegex = "3B(.{6}|.{10})805A..80" + samRevision.getApplicationTypeMask() + "20.{4}" + snRegex + "829000";
        break;
    case SamRevision::InnerEnum::AUTO:
        /* match any ATR */
        atrRegex = ".*";
        break;
    default:
        throw std::invalid_argument("Unknown SAM subtype.");
    }

    this->getAtrFilter()->setAtrRegex(atrRegex);
}

}
}
}
}
}
