/* Example */
#include "ObservableReaderNotificationEngine.h"

/* Core */
#include "SeProxyService.h"
#include "ReaderPlugin.h"
#include "ObservablePlugin.h"

/* Plugin PC/SC */
#include "PcscPlugin.h"

using ObservableReaderNotificationEngine = org::eclipse::keyple::example::generic::common::ObservableReaderNotificationEngine;
using PcscPlugin = org::eclipse::keyple::plugin::pcsc::PcscPlugin;
using SeProxyService = org::eclipse::keyple::seproxy::SeProxyService;
using ReaderPlugin = org::eclipse::keyple::seproxy::ReaderPlugin;
using ObservablePlugin = org::eclipse::keyple::seproxy::event::ObservablePlugin;

int main(int argc, char **argv)
throw(std::runtime_error)
{
    ObservableReaderNotificationEngine *demoEngine = new ObservableReaderNotificationEngine();

    /* Instantiate SeProxyService and add PC/SC plugin */
    SeProxyService seProxyService = SeProxyService::getInstance();

    /*
    * Alex: diamond issue, casting PcscPlugin into ReaderPlugin can take two
    * routes:
    * - PcscPlugin -> AbstractThreadedObservablePlugin ->
    *   AbstractObservablePlugin -> ReaderPlugin
    * or
    * - PcscPlugin -> AbstractThreadedObservablePlugin -> ObservablePlugin ->
    *   ReaderPlugin
    *
    * Forcing conversion to ObservablePlugin for now but should be fixed or at
    * least validated.
    */
    std::shared_ptr<PcscPlugin> pcscplugin = PcscPlugin::getInstance();
    pcscplugin->initReaders();
    std::shared_ptr<ObservablePlugin> plugin = std::dynamic_pointer_cast<ObservablePlugin>(pcscplugin);
    seProxyService.addPlugin(std::dynamic_pointer_cast<ReaderPlugin>(plugin));

    /* Set observers */
    demoEngine->setPluginObserver();

    std::cout << "[Demo_ObservableReaderNotification_Pcsc:main] Wait for reader or SE insertion/removal" << std::endl;

    /* Wait indefinitely. CTRL-C to exit. */
//JAVA TO C++ CONVERTER TODO TASK: Multithread locking is not converted to native C++ unless you choose one of the options on the 'Modern C++ Options' dialog:
//    synchronized(waitBeforeEnd) {
//        waitBeforeEnd->wait();
//    }
    while (1);
}
