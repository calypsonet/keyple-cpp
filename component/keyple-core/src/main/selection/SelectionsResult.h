/******************************************************************************
 * Copyright (c) 2018 Calypso Networks Association                            *
 * https://www.calypsonet-asso.org/                                           *
 *                                                                            *
 * See the NOTICE file(s) distributed with this work for additional           *
 * information regarding copyright ownership.                                 *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the Eclipse Public License 2.0 which is available at              *
 * http://www.eclipse.org/legal/epl-2.0                                       *
 *                                                                            *
 * SPDX-License-Identifier: EPL-2.0                                           *
 ******************************************************************************/

#pragma once

#include <vector>
#include <memory>

#include "KeypleCoreExport.h"

/* Forward class declarations */
namespace keyple {
namespace core {
namespace selection {
class MatchingSelection;
}
}
}

namespace keyple {
namespace core {
namespace selection {

/**
 * The SelectionsResult class holds the result of a selection process.
 * <p>
 * embeds a list of {@link MatchingSelection}
 * <p>
 * provides a set of methods to retrieve the active selection
 * (getActiveSelection) or a particular selection specified by its index.
 */
class KEYPLECORE_API SelectionsResult final
: public std::enable_shared_from_this<SelectionsResult> {
public:
    /**
     * Constructor
     */

    SelectionsResult();

    /**
     * Append a {@link MatchingSelection} to the internal list
     *
     * @param matchingSelection the item to add
     */
    void
    addMatchingSelection(std::shared_ptr<MatchingSelection> matchingSelection);

    /**
     * @return the currently active (matching) selection
     */
    std::shared_ptr<MatchingSelection> getActiveSelection();

    /**
     * @return the {@link MatchingSelection} list
     */
    std::vector<std::shared_ptr<MatchingSelection>> getMatchingSelections();

    /**
     * Gets the {@link MatchingSelection} for the specified index.
     * <p>
     * Returns null if no {@link MatchingSelection} was found.
     *
     * @param selectionIndex the selection index
     * @return the {@link MatchingSelection} or null
     */
    std::shared_ptr<MatchingSelection> getMatchingSelection(int selectionIndex);

    /**
     * @return true if an active selection is present
     */
    bool hasActiveSelection();

private:
    /**
     *
     */
    bool hasActiveSelection_Renamed = false;

    /**
     *
     */
    std::vector<std::shared_ptr<MatchingSelection>> matchingSelectionList =
        std::vector<std::shared_ptr<MatchingSelection>>();
};

}
}
}
