#include "ChangeKeyCmdBuild.h"
#include "ChangeKeyRespPars.h"
#include "ApduResponse.h"

namespace org {
namespace eclipse {
namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace builder {
namespace security {

using namespace org::eclipse::keyple::calypso::command::po;

using PoClass                  = org::eclipse::keyple::calypso::command::PoClass;
using CalypsoPoCommands        = org::eclipse::keyple::calypso::command::po::CalypsoPoCommands;
using ChangeKeyRespPars        = org::eclipse::keyple::calypso::command::po::parser::security::ChangeKeyRespPars;
using ApduResponse             = org::eclipse::keyple::core::seproxy::message::ApduResponse;

ChangeKeyCmdBuild::ChangeKeyCmdBuild(PoClass poClass, char keyIndex, std::vector<char> &cryptogram)
: AbstractPoCommandBuilder<ChangeKeyRespPars>(std::make_shared<CalypsoPoCommands>(command), nullptr) {

    if (cryptogram.empty() || (cryptogram.size() != 0x18 && cryptogram.size() != 0x20)) {
        throw std::invalid_argument("Bad cryptogram value.");
    }

    char cla = poClass.getValue();
    char p1 = static_cast<char>(0x00);
    char p2 = keyIndex;

    this->request = setApduRequest(cla, std::make_shared<CalypsoPoCommands>(command), p1, p2,
                                   cryptogram, -1);
    this->addSubName("Change Key");
}

std::shared_ptr<ChangeKeyRespPars> ChangeKeyCmdBuild::createResponseParser(std::shared_ptr<ApduResponse> apduResponse) {
    return std::make_shared<ChangeKeyRespPars>(apduResponse);
}

}
}
}
}
}
}
}
}
