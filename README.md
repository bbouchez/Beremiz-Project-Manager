# Beremiz-Project-Manager
Plugin based manager for Beremiz IDE

Beremiz Project Manager needs the following libraries to be compiled :
- Cross-platform BEB SDK : https://github.com/bbouchez/BEBSDK
- wxWidgets 3.2 : https://www.wxwidgets.org/downloads/  (current release has been compiled with wxWidgets 3.2.4)

IMPORTANT : project shall define in preprocessor
- `#define __TARGET_LINUX__`    to compile under Linux
- `#define __TARGET_WIN__`      to compile under Windows
- `#define __TARGET_MAC__`      to compile under MacOS (not tested for now)

