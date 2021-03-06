#define OTHER_LIBS \
     p3dtoolutil:c p3dtoolbase:c p3dtool:m p3prc
#define BUILD_DIRECTORY $[HAVE_AUDIO]

#begin lib_target
  #define TARGET p3audio
  #define LOCAL_LIBS p3putil p3event p3movies p3linmath

  #define BUILDING_DLL BUILDING_PANDA_AUDIO

  #define SOURCES \
    config_audio.h \
    filterProperties.h filterProperties.I\
    audioLoadRequest.h audioLoadRequest.I \
    audioManager.h audioManager.I\
    audioSound.h audioSound.I\
    nullAudioManager.h \
    nullAudioSound.h

  #define COMPOSITE_SOURCES \
    config_audio.cxx \
    filterProperties.cxx \
    audioLoadRequest.cxx \
    audioManager.cxx \
    audioSound.cxx \
    nullAudioManager.cxx \
    nullAudioSound.cxx

  #define INSTALL_HEADERS \
    config_audio.h \
    filterProperties.h filterProperties.I\
    audioLoadRequest.h audioLoadRequest.I \
    audioManager.h audioManager.I\
    audioSound.h audioSound.I\
    nullAudioManager.h \
    nullAudioSound.h

  #define IGATESCAN all
#end lib_target

#begin test_bin_target
  #define TARGET test_audio
  #define LOCAL_LIBS \
    p3audio

  #define SOURCES \
    test_audio.cxx

#end test_bin_target
