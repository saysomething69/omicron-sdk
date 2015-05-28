# New Features #
## Other New Features ##
  * add simple one-line command to start servicemanager + netservice and connect to a specific host:port. fix tutorials. test build
    * ServiceManager::runLocal(config, [datapath](datapath.md))
    * ServiceManager::runRemote(host, port)
  * add omsg with template arg list
    * remove need for explicit PortholeTabletService update calls.
  * oinputserver working on linux
  * omicronConnectorServer
  * oinputserver uses the connectorServer

# CHanges #
## Other Changes ##
  * ServiceManager: poll >> update (VERY LOW PRIORITY CHANGE)
> > default implementation calls poll for compatibility with legacy code