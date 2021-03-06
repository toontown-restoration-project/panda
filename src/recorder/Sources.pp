#define OTHER_LIBS p3interrogatedb \
                  p3dtoolutil:c p3dtoolbase:c p3dtool:m p3prc
#define LOCAL_LIBS p3dgraph p3putil p3express p3pandabase

#begin lib_target
  #define TARGET p3recorder

  #define BUILDING_DLL BUILDING_PANDA_RECORDER

  #define SOURCES \
    config_recorder.h \
    mouseRecorder.h \
    recorderBase.h recorderBase.I \
    recorderController.h recorderController.I \
    recorderFrame.h recorderFrame.I \
    recorderHeader.h recorderHeader.I \
    recorderTable.h recorderTable.I \
    socketStreamRecorder.h socketStreamRecorder.I

 #define COMPOSITE_SOURCES \
    config_recorder.cxx \
    mouseRecorder.cxx \
    recorderBase.cxx recorderController.cxx \
    recorderFrame.cxx recorderHeader.cxx recorderTable.cxx \
    socketStreamRecorder.cxx

  #define INSTALL_HEADERS \
    mouseRecorder.h \
    recorderBase.h recorderBase.I \
    recorderController.h recorderController.I \
    recorderFrame.h recorderFrame.I \
    recorderHeader.h recorderHeader.I \
    recorderTable.h recorderTable.I \
    socketStreamRecorder.h socketStreamRecorder.I

  #define IGATESCAN all

#end lib_target
