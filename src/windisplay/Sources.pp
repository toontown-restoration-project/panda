#define BUILD_DIRECTORY $[WINDOWS_PLATFORM]

#define OTHER_LIBS p3interrogatedb \
                   p3dtoolutil:c p3dtoolbase:c p3dtool:m
#define WIN_SYS_LIBS imm32.lib user32.lib

#define BUILDING_DLL BUILDING_PANDAWIN

#define USE_PACKAGES dx9

#begin lib_target
  #define TARGET p3windisplay
  #define LOCAL_LIBS \
    p3display p3putil

  #define SOURCES \
     config_windisplay.h \
     winGraphicsPipe.I winGraphicsPipe.h \
     winGraphicsWindow.I winGraphicsWindow.h \
     winDetectDx.h

  #define INSTALL_HEADERS \
     config_windisplay.h \
     winGraphicsPipe.I winGraphicsPipe.h \
     winGraphicsWindow.I winGraphicsWindow.h
//     Win32Defs.h

  #define COMPOSITE_SOURCES \
     config_windisplay.cxx winGraphicsPipe.cxx \
     winGraphicsWindow.cxx \
     winDetectDx9.cxx

  #define WIN_SYS_LIBS Imm32.lib winmm.lib kernel32.lib oldnames.lib user32.lib gdi32.lib

#end lib_target
