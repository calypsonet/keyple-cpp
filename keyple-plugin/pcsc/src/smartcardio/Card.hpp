/*
 * Copyright (c) 2018 Calypso Networks Association https://www.calypsonet-asso.org/
 *
 * All rights reserved. This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License version 2.0 which accompanies this distribution, and is
 * available at https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 */

#ifndef KEYPLE_PLUGIN_PCSC_CARD_H
#define KEYPLE_PLUGIN_PCSC_CARD_H

#include "CardChannel.hpp"
#include "Export.hpp"

namespace keyple {
    namespace plugin {
        namespace pcsc {

            /**
             * @class Card
             *
             */
            class EXPORT Card {
            public:
                /**
                 * Constructor
                 *
                 * Constructs a new Card object.
                 *
                 * This constructor is called by subclasses only. Application should call list() or
                 * getTerminal() to obtain a CardTerminal object.
                 */
                Card();

                /**
                 * Destructor
                 *
                 */
                ~Card();

                /**
                 * Returns the CardChannel for the basic logical channel. The basic logical
                 * channel has a channel number of 0.
                 * 
                 * @throws SecurityException if a SecurityManager exists and the caller does
                 *                           not have the required permission
                 * @throws IllegalStateException if this card object has been disposed of via
                 *                               the disconnect() method
                 */
                CardChannel& getBasicChannel();
                

                /**
                 * Returns the ATR of this card. 
                 *
                 * @return the ATR of this card.
                 */
                std::vector<uint8_t>* getATR();


                /**
                 * Releases the exclusive access previously established using beginExclusive.
                 *
                 * @throws SecurityException if a SecurityManager exists and the caller does not have the required
                 *                           permission
                 * @throws llegalStateException if the active Thread does not currently have exclusive access to this
                 *                              card or if this card object has been disposed of via the disconnect()
                 *                              method
                 * @throws CardException if the operation failed
                 */
                 void endExclusive();

            private:
                /**
                 *
                 */
                CardChannel *channel;
                
                /**
                 *
                 */
                std::vector<uint8_t> *atr;
            };
        }
    }
}


 #endif /* KEYPLE_PLUGIN_PCSC_CARD_H */