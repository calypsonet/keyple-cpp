#include "SeRequestSet.h"
#include "SeRequest.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace seproxy {
                namespace message {

                    SeRequestSet::SeRequestSet(std::shared_ptr<Set<std::shared_ptr<SeRequest>>> seRequests) : sortedRequests(seRequests) {
                    }

                    SeRequestSet::SeRequestSet(std::shared_ptr<SeRequest> request) : sortedRequests(seRequests) {
                        std::shared_ptr<Set<std::shared_ptr<SeRequest>>> seRequests = std::make_shared<LinkedHashSet<std::shared_ptr<SeRequest>>>();
                        seRequests->add(request);
                    }

                    std::shared_ptr<Set<std::shared_ptr<SeRequest>>> SeRequestSet::getRequests() {
                        return sortedRequests;
                    }

                    std::shared_ptr<SeRequest> SeRequestSet::getSingleRequest() {
                        if (sortedRequests->size() != 1) {
                            throw std::make_shared<IllegalStateException>("This method only support ONE element");
                        }
                        return sortedRequests->begin()->next();
                    }

                    std::string SeRequestSet::toString() {
                        return std::to_string(sortedRequests->size()) + " SeRequest(s)";
                    }
                }
            }
        }
    }
}
