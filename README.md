# Beremiz-Project-Manager
Beremiz Project Manager is the evolution of my previous Beremiz runtimes (like Beremiz4Pico). Rather than having one tool per target, the Project Manager uses plugins in order to support as many targets as wanted. The current version supports four different targets :
- Raspberry Pi Pico (replaces Beremiz4Pico project which is not anymore supported)
- Sferalabs IONO RP
- MERG CBUS
- Pixtend V2L

The plugin SDK is public, so it is possible to expand the Project Manager with new PLC targets without needing to modify the Project Manager.

### IMPORTANT : Beremiz Project Manager is still in its early development stage. The following features are not yet implemented :
- online debugging and visualization
- force/unforce variables
- generic fieldbus support

Beremiz Project Manager needs the following libraries to be compiled :
- Cross-platform BEB SDK : https://github.com/bbouchez/BEBSDK
- wxWidgets 3.2 : https://www.wxwidgets.org/downloads/  (current release has been compiled with wxWidgets 3.2.4)

IMPORTANT : project shall define in preprocessor
- `#define __TARGET_LINUX__`    to compile under Linux
- `#define __TARGET_WIN__`      to compile under Windows
- `#define __TARGET_MAC__`      to compile under MacOS (not tested for now)

