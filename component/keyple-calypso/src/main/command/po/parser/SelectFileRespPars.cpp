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

/* Core */
#include "ByteArrayUtil.h"

/* Calypso */
#include "SelectFileRespPars.h"

/* Common */
#include "System.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace parser {

using namespace keyple::core::command;
using namespace keyple::core::util;

using StatusProperties = AbstractApduResponseParser::StatusProperties;

std::unordered_map<int, std::shared_ptr<StatusProperties>>
    SelectFileRespPars::STATUS_TABLE;

SelectFileRespPars::StaticConstructor::StaticConstructor()
{
    std::unordered_map<int, std::shared_ptr<StatusProperties>>
        m(AbstractApduResponseParser::STATUS_TABLE);
 
    m.emplace(0x6A88,
              std::make_shared<StatusProperties>(
                  false,
                  "Data object not found (optional mode not available)."));
    m.emplace(0x6B00,
            std::make_shared<StatusProperties>(
                false,
                "P1 or P2 value not supported (<>004fh, 0062h, 006Fh, 00C0h, " \
                "00D0h, 0185h and 5F52h, according to availabl optional " \
                "modes)."));
 
    STATUS_TABLE = m;
}

SelectFileRespPars::StaticConstructor SelectFileRespPars::staticConstructor;

void SelectFileRespPars::parseResponse() {
    std::vector<char> inFileParameters = response->getDataOut();
    int iter = 0;

    if (!response->isSuccessful()) {
        // the command was not successful, we stop here
        return;
    }

    if (logger->isTraceEnabled()) {
        logger->trace("Parsing FCI: {}",
                      ByteArrayUtil::toHex(inFileParameters).c_str());
    }

    // Check File TLV Tag and length
    if (inFileParameters[iter++] != static_cast<char>(0x85) ||
        inFileParameters[iter++] != static_cast<char>(0x17)) {
        throw IllegalStateException("Unexpected FCI format: " +
                                    ByteArrayUtil::toHex(inFileParameters));
    }

    fileBinaryData = std::vector<char>(inFileParameters.size());
    System::arraycopy(inFileParameters, 0, fileBinaryData, 0,
                      inFileParameters.size());

    sfi = inFileParameters[iter++];
    fileType = inFileParameters[iter++];
    efType = inFileParameters[iter++];

    if (fileType == FILE_TYPE_EF && efType == EF_TYPE_BINARY) {

        recSize = ((inFileParameters[iter] << 8) & 0x0000ff00) |
                  (inFileParameters[iter + 1]   & 0x000000ff);
        numRec = 1;
        iter += 2;

    }
    else if (fileType == FILE_TYPE_EF) {

        recSize = inFileParameters[iter++];
        numRec = inFileParameters[iter++];
    }
    else {
        // no record for non EF types
        recSize = 0;
        numRec = 0;
        iter += 2;
    }

    accessConditions = std::vector<char>(4);
    System::arraycopy(inFileParameters, iter, accessConditions, 0, 4);
    iter += 4;

    keyIndexes = std::vector<char>(4);
    System::arraycopy(inFileParameters, iter, keyIndexes, 0, 4);
    iter += 4;

    dfStatus = inFileParameters[iter++];

    if (fileType == FILE_TYPE_EF) {

        if (efType == EF_TYPE_SIMULATED_COUNTERS) {

            simulatedCounterFileSfi = inFileParameters[iter++];
            simulatedCounterNumber = inFileParameters[iter++];

        }
        else {

            sharedEf = ((inFileParameters[iter + 1] << 8) & 0x0000ff00) |
                       (inFileParameters[iter] & 0x000000ff);
            iter += 2;
        }

        rfu = std::vector<char>(5);
        System::arraycopy(inFileParameters, iter, rfu, 0, 5);
        iter += 5; // RFU fields;

    }
    else {

        kvcInfo = std::vector<char>(3);
        System::arraycopy(inFileParameters, iter, kvcInfo, 0, 3);
        iter += 3;

        kifInfo = std::vector<char>(3);
        System::arraycopy(inFileParameters, iter, kifInfo, 0, 3);
        iter += 3;


        rfu = std::vector<char>(1);
        rfu[0] = inFileParameters[iter++];
    }

    lid = ((inFileParameters[iter] << 8) & 0x0000ff00) |
          (inFileParameters[iter + 1] & 0x000000ff);

    selectionSuccessful = true;
}

SelectFileRespPars::SelectFileRespPars(std::shared_ptr<ApduResponse> response)
: AbstractPoResponseParser(response)
{
    parseResponse();
}

bool SelectFileRespPars::isSelectionSuccessful()
{
    return selectionSuccessful;
}

int SelectFileRespPars::getLid()
{
    return lid;
}

char SelectFileRespPars::getSfi()
{
    return sfi;
}

char SelectFileRespPars::getFileType()
{
    return fileType;
}

char SelectFileRespPars::getEfType()
{
    return efType;
}

int SelectFileRespPars::getRecSize()
{
    return recSize;
}

char SelectFileRespPars::getNumRec()
{
    return numRec;
}

std::vector<char> SelectFileRespPars::getAccessConditions()
{
    return accessConditions;
}

std::vector<char> SelectFileRespPars::getKeyIndexes()
{
    return keyIndexes;
}

char SelectFileRespPars::getSimulatedCounterFileSfi()
{
    return simulatedCounterFileSfi;
}

char SelectFileRespPars::getSimulatedCounterNumber()
{
    return simulatedCounterNumber;
}

int SelectFileRespPars::getSharedEf()
{
    return sharedEf;
}

char SelectFileRespPars::getDfStatus()
{
    return dfStatus;
}

std::vector<char> SelectFileRespPars::getFileBinaryData()
{
    return fileBinaryData;
}

std::vector<char> SelectFileRespPars::getRfu()
{
    return rfu;
}

std::vector<char> SelectFileRespPars::getKvcInfo()
{
    return kvcInfo;
}

std::vector<char> SelectFileRespPars::getKifInfo()
{
    return kifInfo;
}

std::vector<char> SelectFileRespPars::getSelectionData()
{
    return response->getDataOut();
}

}
}
}
}
}