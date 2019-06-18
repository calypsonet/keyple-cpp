#include "KeypleApplicationSelectionException.h"

namespace org {
namespace eclipse {
namespace keyple {
namespace core {
namespace seproxy {
namespace exception {

KeypleApplicationSelectionException::KeypleApplicationSelectionException(const std::string &message) : KeypleReaderException(message) {
}

KeypleApplicationSelectionException::KeypleApplicationSelectionException(const std::string &message, std::runtime_error cause) : KeypleReaderException(message, cause) {
}

}
}
}
}
}
}
