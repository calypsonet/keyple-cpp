/*
 * Copyright (c) 2018 Calypso Networks Association https://www.calypsonet-asso.org/
 *
 * All rights reserved. This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License version 2.0 which accompanies this distribution, and is
 * available at https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 */

// TestPlugin.cpp : Defines the entry point for the console application.
//

#include "PlatformConfig.hpp"
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <system_error>

#include "ReadersPlugin.hpp"
#include "SeProxyService.hpp"
#include "ConfigurableReader.hpp"
#include "ObservableReader.hpp"
#include "ReaderParameters.hpp"

#include "Observer.hpp"

using namespace keyple;
using namespace seproxy;
using namespace containers;
using namespace std;

/// A factory of ReadersPlugin-implementing objects
typedef ReadersPlugin *(*ReadersPluginFactory)();

/// A factory of SeProxyService-implementing objects
typedef SeProxyService *(*SeProxyServiceFactory)();

/*!
 * \fn ExecutionStatus Observer::notify(keyple::containers::ReaderEvent *event)
 *
 * \brief Observer callback, called when a reader event occurs
 *
 * \return The ExecutionStatus.
 */

ExecutionStatus Observer::notify(ReaderEvent event)
{
    ExecutionStatus status = UNEXPECTED_READER_ERROR;

    if (event.getEventType() == ReaderEvent::EventType::SE_INSERTED)
    {
        ProxyReader *reader = static_cast<ProxyReader *>(event.getReader());

        DBG_INFO_MSG("Reader " << reader->getName());

        //std::vector<uint8_t> AID = { 0xA0, 0x00, 0x00, 0x02, 0x91, 0xA0, 0x00, 0x00, 0x01, 0x91 };
        std::vector<uint8_t> AID = {0xA0, 0x00, 0x00, 0x04, 0x04, 0x01, 0x25, 0x09,
                                    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        //std::vector<uint8_t> AID = { 0x31, 0x54, 0x49, 0x43, 0x2E, 0x49, 0x43, 0x41, 0x20, 0x41, 0x49, 0x44 };

        std::list<ApduRequest> listApdu;

        DBG_INFO_MSG("Read Record - T2 Environment");
        listApdu.push_back(ApduRequest(std::vector<uint8_t>{0x00, 0xB2, 0x01, 0xA4, 0x20}, false));

        DBG_INFO_MSG("Read Record - T2 Usage");
        listApdu.push_back(ApduRequest(std::vector<uint8_t>{0x00, 0xB2, 0x01, 0xD4, 0x30}, false));

        DBG_INFO_MSG("Update Record - T2 Usage");
        listApdu.push_back(
            ApduRequest(std::vector<uint8_t>{0x00, 0xDC, 0x01, 0xD4, 0x30, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                             0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
                                             0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
                                             0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                                             0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30},
                        false));

        /*
		DBG_INFO_MSG("Mifare - Load key");
		listApdu.push_back(ApduRequest(std::vector<uint8_t> { 0xFF, 0x82, 0x00, 0x61, 0x06, 0x41, 0x43, 0x53, 0x2D, 0x49, 0x4E }, false));
		DBG_INFO_MSG("Mifare - Authenticate");
		listApdu.push_back(ApduRequest(std::vector<uint8_t> { 0xFF, 0x86, 0x00, 0x00, 0x05, 0x01, 0x00, 0x04, 0x61, 0x00 }, false));
		DBG_INFO_MSG("Mifare - Read block");
		listApdu.push_back(ApduRequest(std::vector<uint8_t> { 0xFF, 0xB0, 0x00, 0x04, 0x10 }, false));

		DBG_INFO_MSG("ST25 - Read block");
		listApdu.push_back(ApduRequest(std::vector<uint8_t> { 0xFF, 0xB0, 0x00, 0x0A, 0x04 }, false));
		*/

        SeRequest *se_request = new SeRequest(AID, listApdu, false);

        try
        {
            SeResponse se_response = reader->transmit(se_request);

            std::vector<uint8_t> atr = se_response.getAtr();

            DBG_DUMP_HEX_VECTOR("ATR: ", atr);

            std::vector<uint8_t> fci = se_response.getFci().getBytes();

            DBG_DUMP_HEX_VECTOR("FCI: ", fci);
        } catch (const std::system_error &ex)
        {
            DBG_ERROR_MSG(ex.code().value());
            DBG_ERROR_MSG(ex.code().message());
        }
    }
    return status;
}

int main()
{
    // Load the plugin DLL
    handle_t plugin_dll_handle = ::OsOpenLibrary(PcscPlugin);
    if (!plugin_dll_handle)
    {
        DBG_ERROR_MSG("Load library error: " << OsGetLastError());
        exit(EXIT_FAILURE);
    }

    // Get the function from the DLL
    ReadersPluginFactory readers_plugin_factory_func =
        reinterpret_cast<ReadersPluginFactory>(::OsGetSymbol(plugin_dll_handle, "CreateClass"));
    if (!readers_plugin_factory_func)
    {
        DBG_ERROR_MSG("Unable to load CreateClass from library!");
        ::OsCloseLibrary(plugin_dll_handle);
        exit(EXIT_FAILURE);
    }

    // Ask the factory for a new object implementing the ReadersPlugin
    // interface
    ReadersPlugin *readers_plugin_instance = readers_plugin_factory_func();

    // Play with the plugin object
    DBG_INFO_MSG("plugin name = " << readers_plugin_instance->getName());

    // Load the SeProxyService DLL
    handle_t seproxy_dll_handle = ::OsOpenLibrary(SeProxyService);
    if (!seproxy_dll_handle)
    {
        DBG_ERROR_MSG("Load library error: " << OsGetLastError());
        exit(EXIT_FAILURE);
    }

    // Get the CreateClass function from the DLL
    SeProxyServiceFactory se_proxy_service_factory_func =
        reinterpret_cast<SeProxyServiceFactory>(::OsGetSymbol(seproxy_dll_handle, "CreateClass"));
    if (!se_proxy_service_factory_func)
    {
        DBG_ERROR_MSG("Unable to load CreateClass from library!");
        ::OsCloseLibrary(seproxy_dll_handle);
        exit(EXIT_FAILURE);
    }

    // Ask the factory for a new object implementing the SeProxyService
    // interface
    SeProxyService *se_proxy_service_instance = se_proxy_service_factory_func();

    // Play with the seproxyservice object
    list<ReadersPlugin *> readers_plugin_list_in;

    readers_plugin_list_in.push_back(readers_plugin_instance);

    se_proxy_service_instance->setPlugins(readers_plugin_list_in);

    list<ReadersPlugin *> readers_plugin_list_out;

    readers_plugin_list_out = se_proxy_service_instance->getPlugins();

    list<ReadersPlugin *>::iterator iterator_plugin = readers_plugin_list_out.begin();

    ReadersPlugin *plugin_instance_2 = *iterator_plugin;

    // play with retrieved plugin
    DBG_INFO_MSG("plugin_instance_2->getName() = " << plugin_instance_2->getName());

    list<ProxyReader *> readers_list;
    readers_list = plugin_instance_2->getReaders();

    list<ProxyReader *>::iterator iterator_reader = readers_list.begin();

    Observer observer;

    for (uint32_t ii = 0; ii < readers_list.size(); ii++)
    {
        ProxyReader *reader = *iterator_reader;
        DBG_INFO_MSG("[" << ii << "] reader->getName() = " << reader->getName());

        ConfigurableReader *configurable_reader = dynamic_cast<ConfigurableReader *>(reader);

        configurable_reader->setAParameter(PARAM_KEY_SHARE_MODE, PARAM_VALUE_SHARE_SHARED);

        configurable_reader->getParameters();

        ObservableReader *observable_reader = dynamic_cast<ObservableReader *>(reader);

        observable_reader->attachObserver(&observer);

        iterator_reader++;
    }

    //std::vector<uint8_t> AIDback = se_request->getAidToSelect();

    DBG_INFO_MSG("Waiting for events, press a key to exit...");

    cin.get();

    /// Explicitly destroys created objects
    //delete se_proxy_service_instance;
    //readers_plugin_instance->destroy();

    /// Unload libraries
    ::OsCloseLibrary(plugin_dll_handle);
    ::OsCloseLibrary(seproxy_dll_handle);

    exit(EXIT_SUCCESS);
}