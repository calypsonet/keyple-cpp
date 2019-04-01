#include "MatchingSe.h"
#include "SeResponse.h"
#include "SeSelectionRequest.h"

namespace org {
    namespace eclipse {
        namespace keyple {
            namespace transaction {
                using SeResponse = org::eclipse::keyple::seproxy::message::SeResponse;

                MatchingSe::MatchingSe(std::shared_ptr<SeSelectionRequest> seSelectionRequest) : channelIsKeptOpen(seSelectionRequest->getSelectionRequest()->isKeepChannelOpen()), extraInfo(seSelectionRequest->getSeSelector()->getExtraInfo()) {
                }

                void MatchingSe::setSelectionResponse(std::shared_ptr<SeResponse> selectionResponse) {
                    this->selectionSeResponse = selectionResponse;
                }

                std::shared_ptr<SeResponse> MatchingSe::getSelectionSeResponse() {
                    return selectionSeResponse;
                }

                bool MatchingSe::isSelectable() {
                    return channelIsKeptOpen;
                }

                bool MatchingSe::isSelected() {
                    return channelIsKeptOpen && selectionSeResponse != nullptr && selectionSeResponse->getSelectionStatus() != nullptr && selectionSeResponse->getSelectionStatus()->hasMatched();
                }

                std::string MatchingSe::getExtraInfo() {
                    return extraInfo;
                }

                void MatchingSe::reset() {
                    selectionSeResponse.reset();
                }
            }
        }
    }
}
