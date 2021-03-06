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

#include "AbstractObservableReaderTest.h"
#include "ReaderEvent.h"
#include "AbstractObservableReader.h"
#include "SeProtocol.h"
#include "SeSelector.h"
#include "SelectionStatus.h"

namespace org {
namespace eclipse {
namespace keyple {
namespace seproxy {
namespace plugin {

using CoreBaseTest = org::eclipse::keyple::CoreBaseTest;
using SeSelector   = keyple::core::seproxy::SeSelector;
using ObservableReader =
    org::eclipse::keyple::seproxy::event_Renamed::ObservableReader;
using ReaderEvent = org::eclipse::keyple::seproxy::event_Renamed::ReaderEvent;
using namespace org::eclipse::keyple::seproxy::exception;
using SelectionStatus = org::eclipse::keyple::seproxy::message::SelectionStatus;
using SeProtocol      = org::eclipse::keyple::seproxy::protocol::SeProtocol;
using TransmissionMode =
    org::eclipse::keyple::seproxy::protocol::TransmissionMode;
using org::slf4j::Logger;
using org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> AbstractObservableReaderTest::logger =
    org::slf4j::LoggerFactory::getLogger(AbstractObservableReaderTest::typeid);

void AbstractObservableReaderTest::setUp()
{
    logger->info("------------------------------");
    logger->info("Test {}", name->getMethodName() + "");
    logger->info("------------------------------");
    spyReader = Mockito::spy(
        getBlankAbstractObservableReader(PLUGIN_NAME, READER_NAME));
    initSpyReader();
}

void AbstractObservableReaderTest::testAddObserver()
{
    startObservationCall = std::make_shared<CountDownLatch>(5);
    stopObservationCall  = std::make_shared<CountDownLatch>(5);
    spyReader->addObserver(obs1);
    Assert::assertEquals(1, spyReader->countObservers());
    Assert::assertEquals(
        4, startObservationCall->getCount()); // should be called once
    Assert::assertEquals(
        5, stopObservationCall->getCount()); // should not be called
}

void AbstractObservableReaderTest::testRemoveObserver()
{
    startObservationCall = std::make_shared<CountDownLatch>(5);
    stopObservationCall  = std::make_shared<CountDownLatch>(5);
    spyReader->addObserver(obs1);
    spyReader->removeObserver(obs1);
    Assert::assertEquals(0, spyReader->countObservers());
    Assert::assertEquals(
        4, startObservationCall->getCount()); // should be called once
    Assert::assertEquals(
        4, stopObservationCall->getCount()); // should be called once
}

void AbstractObservableReaderTest::testAddRemoveObserver()
{
    startObservationCall = std::make_shared<CountDownLatch>(5);
    stopObservationCall  = std::make_shared<CountDownLatch>(5);
    spyReader->addObserver(obs1);
    spyReader->addObserver(obs2);
    spyReader->removeObserver(obs2);
    Assert::assertEquals(1, spyReader->countObservers());
    Assert::assertEquals(
        4, startObservationCall->getCount()); // should be called once
    Assert::assertEquals(
        5, stopObservationCall->getCount()); // should not be called
}

std::shared_ptr<AbstractObservableReader>
AbstractObservableReaderTest::getBlankAbstractObservableReader(
    const std::string& pluginName, const std::string& readerName)
{

    return std::make_shared<AbstractLocalReaderAnonymousInnerClass>(
        shared_from_this(), pluginName, readerName);
}

AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    AbstractLocalReaderAnonymousInnerClass(
        std::shared_ptr<AbstractObservableReaderTest> outerInstance,
        const std::string& pluginName, const std::string& readerName)
: AbstractLocalReader(pluginName, readerName)
{
    this->outerInstance = outerInstance;
}

void AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    startObservation()
{
}

void AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    stopObservation()
{
}

void AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    closePhysicalChannel() throw(KeypleChannelStateException)
{
}

bool AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    isPhysicalChannelOpen()
{
    return false;
}

std::vector<char>
AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    transmitApdu(std::vector<char>& apduIn) throw(KeypleIOReaderException)
{
    return std::vector<char>(0);
}

bool AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    protocolFlagMatches(std::shared_ptr<SeProtocol> protocolFlag) throw(
        KeypleReaderException)
{
    return false;
}

bool AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    checkSePresence() throw(NoStackTraceThrowable)
{
    return false;
}

std::vector<char>
AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::getATR()
{
    return std::vector<char>(0);
}

std::shared_ptr<SelectionStatus>
AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    openLogicalChannel(std::shared_ptr<SeSelector> selector)
{
    return nullptr;
}

void AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    openPhysicalChannel() throw(KeypleChannelStateException)
{
}

TransmissionMode AbstractObservableReaderTest::
    AbstractLocalReaderAnonymousInnerClass::getTransmissionMode()
{
    return nullptr;
}

std::unordered_map<std::string, std::string> AbstractObservableReaderTest::
    AbstractLocalReaderAnonymousInnerClass::getParameters()
{
    return nullptr;
}

void AbstractObservableReaderTest::AbstractLocalReaderAnonymousInnerClass::
    setParameter(const std::string& key,
                 const std::string& value) throw(std::invalid_argument,
                                                 KeypleBaseException)
{
}

std::shared_ptr<ObservableReader::ReaderObserver>
AbstractObservableReaderTest::getObserver()
{
    return std::make_shared<ReaderObserverAnonymousInnerClass>(
        shared_from_this());
}

AbstractObservableReaderTest::ReaderObserverAnonymousInnerClass::
    ReaderObserverAnonymousInnerClass(
        std::shared_ptr<AbstractObservableReaderTest> outerInstance)
{
    this->outerInstance = outerInstance;
}

void AbstractObservableReaderTest::ReaderObserverAnonymousInnerClass::update(
    std::shared_ptr<ReaderEvent> readerEvent)
{
}

void AbstractObservableReaderTest::initSpyReader()
{

    // track when startObservation is called
    doAnswer(std::make_shared<AnswerAnonymousInnerClass>(shared_from_this()))
        .when(spyReader)
        .startObservation();

    // track when stopObservation is called
    doAnswer(std::make_shared<AnswerAnonymousInnerClass2>(shared_from_this()))
        .when(spyReader)
        .stopObservation();
}

AbstractObservableReaderTest::AnswerAnonymousInnerClass::
    AnswerAnonymousInnerClass(
        std::shared_ptr<AbstractObservableReaderTest> outerInstance)
{
    this->outerInstance = outerInstance;
}

std::shared_ptr<void>
AbstractObservableReaderTest::AnswerAnonymousInnerClass::answer(
    std::shared_ptr<InvocationOnMock> invocation) throw(std::runtime_error)
{
    outerInstance->startObservationCall->countDown();
    return nullptr;
}

AbstractObservableReaderTest::AnswerAnonymousInnerClass2::
    AnswerAnonymousInnerClass2(
        std::shared_ptr<AbstractObservableReaderTest> outerInstance)
{
    this->outerInstance = outerInstance;
}

std::shared_ptr<void>
AbstractObservableReaderTest::AnswerAnonymousInnerClass2::answer(
    std::shared_ptr<InvocationOnMock> invocation) throw(std::runtime_error)
{
    outerInstance->stopObservationCall->countDown();
    return nullptr;
}
}
}
}
}
}
