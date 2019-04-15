#include "DefaultSelectionRequest.h"
#include "SeRequestSet.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace event {

                    using org::eclipse::keyple::seproxy::message::SeRequestSet;

                    DefaultSelectionRequest::DefaultSelectionRequest(std::shared_ptr<SeRequestSet> selectionSeRequestSet) : selectionSeRequestSet(selectionSeRequestSet) {
                    }

                    std::shared_ptr<SeRequestSet> DefaultSelectionRequest::getSelectionSeRequestSet() {
                        return selectionSeRequestSet;
                    }
                }
            }
        }
    }
}