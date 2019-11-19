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
#include "SeSelector.h"
#include "ApduRequest.h"
#include "ByteArrayUtil.h"
#include "SeRequest.h"

namespace keyple {
namespace core {
namespace seproxy {

using namespace keyple::core::seproxy::protocol;
using namespace keyple::core::util;
using namespace keyple::core::seproxy;

using FileOccurrence         = SeSelector::AidSelector::FileOccurrence;
using FileControlInformation = SeSelector::AidSelector::FileControlInformation;
using IsoAid                 = SeSelector::AidSelector::IsoAid;
using AidSelector            = SeSelector::AidSelector;
using AtrFilter              = SeSelector::AtrFilter;

FileOccurrence FileOccurrence::FIRST("FIRST", InnerEnum::FIRST,
                                     static_cast<char>(0x00));
FileOccurrence FileOccurrence::LAST("LAST", InnerEnum::LAST,
                                    static_cast<char>(0x01));
FileOccurrence FileOccurrence::NEXT("NEXT", InnerEnum::NEXT,
                                    static_cast<char>(0x02));
FileOccurrence FileOccurrence::PREVIOUS("PREVIOUS", InnerEnum::PREVIOUS,
                                        static_cast<char>(0x03));

std::vector<FileOccurrence> FileOccurrence::valueList;

FileOccurrence::StaticConstructor::StaticConstructor() {
    valueList.push_back(FIRST);
    valueList.push_back(LAST);
    valueList.push_back(NEXT);
    valueList.push_back(PREVIOUS);
}

FileOccurrence::StaticConstructor FileOccurrence::staticConstructor;
int FileOccurrence::nextOrdinal = 0;

FileOccurrence::FileOccurrence(const std::string &name, InnerEnum innerEnum,
                               char isoBitMask)
: innerEnumValue(innerEnum), nameValue(name), ordinalValue(nextOrdinal++)
{
    this->isoBitMask = isoBitMask;
}

FileOccurrence::FileOccurrence(const FileOccurrence& o)
: innerEnumValue(o.innerEnumValue), nameValue(o.nameValue),
  ordinalValue(o.ordinalValue), isoBitMask(o.isoBitMask)
{
}

char FileOccurrence::getIsoBitMask()
{
    return this->isoBitMask;
}

bool FileOccurrence::operator==(const FileOccurrence &other)
        {
    return this->ordinalValue == other.ordinalValue;
}

bool FileOccurrence::operator!=(const FileOccurrence &other)
        {
    return this->ordinalValue != other.ordinalValue;
}

std::vector<FileOccurrence> FileOccurrence::values()
{
    return valueList;
}

int FileOccurrence::ordinal()
{
    return ordinalValue;
}

std::string FileOccurrence::toString()
{
    return nameValue;
}

FileOccurrence FileOccurrence::valueOf(const std::string &name)
{
    for (auto enumInstance : FileOccurrence::valueList) {
        if (enumInstance.nameValue == name) {
            return enumInstance;
        }
    }

    /* Make compiler happy */
    return FileOccurrence::valueList.front();
}

FileControlInformation FileControlInformation::FCI("FCI", InnerEnum::FCI,
                                                   static_cast<char>(0x00));
FileControlInformation FileControlInformation::FCP("FCP", InnerEnum::FCP,
                                                   static_cast<char>(0x04));
FileControlInformation FileControlInformation::FMD("FMD", InnerEnum::FMD,
                                                   static_cast<char>(0x08));
FileControlInformation FileControlInformation::NO_RESPONSE(
    "NO_RESPONSE", InnerEnum::NO_RESPONSE, static_cast<char>(0x0C));

std::vector<FileControlInformation> FileControlInformation::valueList;

FileControlInformation::StaticConstructor::StaticConstructor()
{
    valueList.push_back(FCI);
    valueList.push_back(FCP);
    valueList.push_back(FMD);
    valueList.push_back(NO_RESPONSE);
}

FileControlInformation::StaticConstructor
FileControlInformation::staticConstructor;
int FileControlInformation::nextOrdinal = 0;

FileControlInformation::FileControlInformation(const std::string &name,
                                               InnerEnum innerEnum,
                                               char isoBitMask)
: innerEnumValue(innerEnum), nameValue(name), ordinalValue(nextOrdinal++)
{
    this->isoBitMask = isoBitMask;
}

FileControlInformation::FileControlInformation(const FileControlInformation& o)
: innerEnumValue(o.innerEnumValue), nameValue(o.nameValue),
  ordinalValue(o.ordinalValue), isoBitMask(o.isoBitMask)
{
}

char FileControlInformation::getIsoBitMask()
{
    return this->isoBitMask;
}

bool FileControlInformation::operator==(const FileControlInformation &other)
        {
    return this->ordinalValue == other.ordinalValue;
}

bool FileControlInformation::operator!=(const FileControlInformation &other)
        {
    return this->ordinalValue != other.ordinalValue;
}

std::vector<FileControlInformation> FileControlInformation::values()
{
    return valueList;
}

int FileControlInformation::ordinal()
{
    return ordinalValue;
}

std::string FileControlInformation::toString() {
    return nameValue;
    }

FileControlInformation FileControlInformation::valueOf(const std::string &name) {
    for (auto enumInstance : FileControlInformation::valueList) {
        if (enumInstance.nameValue == name) {
            return enumInstance;
        }
    }

    /* Make compiler happy */
    return FileControlInformation::valueList.front();
}

SeSelector::AidSelector::IsoAid::IsoAid(std::vector<char> aid)
{
    if (aid.size() < AID_MIN_LENGTH || aid.size() > AID_MAX_LENGTH) {
        value.clear();
        throw std::invalid_argument("Bad AID length: "            +
                                    std::to_string(aid.size())    +
                                    ". The AID length should be " +
                                    "between 5 and 15.");
    } else {
        value = aid;
    }
}

IsoAid::IsoAid(const std::string &aid) : IsoAid(ByteArrayUtil::fromHex(aid))
{
}

std::vector<char> IsoAid::getValue()
{
    return value;
}

bool IsoAid::startsWith(std::shared_ptr<IsoAid> aid)
{
    if (this->value.size() > aid->getValue().size()) {
        return false;
    }

    for (int i = 0; i < (int)aid->getValue().size(); i++) {
        if (this->value[i] != aid->getValue()[i]) {
            return false;
        }
    }

    return true;
}

AidSelector::AidSelector(
  std::shared_ptr<IsoAid> aidToSelect,
  std::shared_ptr<std::set<int>> successfulSelectionStatusCodes,
  FileOccurrence fileOccurrence,
  FileControlInformation fileControlInformation)
: fileOccurrence(fileOccurrence),
  fileControlInformation(fileControlInformation)
{
    this->aidToSelect = aidToSelect;
    this->successfulSelectionStatusCodes = successfulSelectionStatusCodes;
}

AidSelector::AidSelector(
  std::shared_ptr<IsoAid> aidToSelect,
  std::shared_ptr<std::set<int>> successfulSelectionStatusCodes)
: AidSelector(aidToSelect, successfulSelectionStatusCodes,
  FileOccurrence::FIRST, FileControlInformation::FCI)
{
}

std::shared_ptr<IsoAid> AidSelector::getAidToSelect()
{
    return aidToSelect;
}

FileOccurrence AidSelector::getFileOccurrence()
{
    return fileOccurrence;
}

FileControlInformation AidSelector::getFileControlInformation() {
    return fileControlInformation;
}

std::shared_ptr<std::set<int>> AidSelector::getSuccessfulSelectionStatusCodes()
{
    return successfulSelectionStatusCodes;
}

std::string SeSelector::AidSelector::toString()
{
    return StringHelper::formatSimple(
              "AID:%s", aidToSelect == nullptr ? "null" :
              ByteArrayUtil::toHex(aidToSelect->getValue()));
}

SeSelector::AtrFilter::AtrFilter(const std::string &atrRegex)
{
    this->atrRegex = atrRegex;
}

void SeSelector::AtrFilter::setAtrRegex(const std::string &atrRegex)
{
    this->atrRegex = atrRegex;
}

std::string SeSelector::AtrFilter::getAtrRegex()
{
    return atrRegex;
}

bool SeSelector::AtrFilter::atrMatches(std::vector<char> &atr)
{
    bool m;

    if (atrRegex.length() != 0) {
        Pattern *p = Pattern::compile(atrRegex);
        std::string atrString = ByteArrayUtil::toHex(atr);
        m = p->matcher(atrString)->matches();
    } else {
            m = true;
    }

    return m;
}

std::string SeSelector::AtrFilter::toString()
{
    return StringHelper::formatSimple("ATR regex:%s", atrRegex.length() != 0 ?
                                      atrRegex : "empty");
}

SeSelector::SeSelector(SeProtocol& seProtocol,
                       std::shared_ptr<AtrFilter> atrFilter,
                       std::shared_ptr<AidSelector> aidSelector,
                       const std::string &extraInfo)
: seProtocol(seProtocol), aidSelector(aidSelector), atrFilter(atrFilter),
  extraInfo(extraInfo)
{
    if (logger->isTraceEnabled()) {
        logger->trace(
          "Selection data: AID = %s ATRREGEX = %s, EXTRAINFO = %s\n",
          this->aidSelector == nullptr ? "null" :
          ByteArrayUtil::toHex(
              this->aidSelector->getAidToSelect()->getValue()).c_str(),
          this->atrFilter == nullptr ? "null" :
          this->atrFilter->getAtrRegex().c_str(),
          extraInfo.c_str());
    }
}

const SeProtocol& SeSelector::getSeProtocol()
{
    return seProtocol;
}

std::shared_ptr<AtrFilter> SeSelector::getAtrFilter()
{
    return atrFilter;
}

std::shared_ptr<AidSelector> SeSelector::getAidSelector()
{
    return aidSelector;
} 

std::string SeSelector::getExtraInfo()
{
    return extraInfo;
}

std::string SeSelector::toString()
{
    return "SeSelector: AID_SELECTOR = "                                +
            (aidSelector == nullptr ? "null" : aidSelector->toString()) +
            ", ATR_FILTER " + "= "                                      +
            (atrFilter == nullptr ? "null" : atrFilter->toString());
}

}
}
}
