#define BUILD_DIRECTORY $[BUILD_IPHONE]

#define OTHER_LIBS p3interrogatedb  \
                   p3dtoolutil:c p3dtoolbase:c p3dtool:m p3prc

#define OSX_SYS_FRAMEWORKS Foundation QuartzCore UIKit OpenGLES

#begin bin_target
  #define TARGET iphone_pview

  #define LOCAL_LIBS \
    p3iphonedisplay \
    p3framework p3putil p3collide p3pgraph p3chan p3text \
    p3pnmimage p3pnmimagetypes p3event p3gobj p3display \
    p3mathutil p3putil p3express p3dgraph p3device p3tform \
    p3linmath p3pstatclient panda p3glstuff

  #define SOURCES \
    pview_delegate.h pview_delegate.mm \
    pview_main.mm

#end bin_target
