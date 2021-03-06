#define OTHER_LIBS p3interrogatedb \
                   p3dtoolutil:c p3dtoolbase:c p3dtool:m p3prc

#begin lib_target
  #define TARGET p3parametrics
  #define LOCAL_LIBS \
    p3pgraph p3linmath p3express p3putil p3pandabase

  #define BUILDING_DLL BUILDING_PANDA_PARAMETRICS

  #define SOURCES \
    config_parametrics.h  \
    cubicCurveseg.h curveFitter.I curveFitter.h  \
    hermiteCurve.h \
    nurbsCurve.I nurbsCurve.h \
    nurbsCurveEvaluator.I nurbsCurveEvaluator.h \
    nurbsCurveInterface.I nurbsCurveInterface.h \
    nurbsCurveResult.I nurbsCurveResult.h \
    nurbsBasisVector.I nurbsBasisVector.h \
    nurbsSurfaceEvaluator.I nurbsSurfaceEvaluator.h \
    nurbsSurfaceResult.I nurbsSurfaceResult.h \
    nurbsVertex.h nurbsVertex.I \
    parametricCurve.h  \
    parametricCurveCollection.I parametricCurveCollection.h  \
    piecewiseCurve.h \
    ropeNode.I ropeNode.h \
    sheetNode.I sheetNode.h

  #define COMPOSITE_SOURCES \
    config_parametrics.cxx cubicCurveseg.cxx  \
    curveFitter.cxx hermiteCurve.cxx  \
    nurbsCurve.cxx \
    nurbsCurveEvaluator.cxx \
    nurbsCurveInterface.cxx  \
    nurbsCurveResult.cxx \
    nurbsBasisVector.cxx \
    nurbsSurfaceEvaluator.cxx \
    nurbsSurfaceResult.cxx \
    nurbsVertex.cxx \
    parametricCurve.cxx parametricCurveCollection.cxx  \
    piecewiseCurve.cxx \
    ropeNode.cxx \
    sheetNode.cxx

  #define INSTALL_HEADERS \
    config_parametrics.h \
    cubicCurveseg.h \
    curveFitter.I curveFitter.h \
    hermiteCurve.h \
    nurbsCurve.I nurbsCurve.h \
    nurbsCurveEvaluator.I nurbsCurveEvaluator.h \
    nurbsCurveInterface.I nurbsCurveInterface.h \
    nurbsCurveResult.I nurbsCurveResult.h \
    nurbsBasisVector.I nurbsBasisVector.h \
    nurbsSurfaceEvaluator.I nurbsSurfaceEvaluator.h \
    nurbsSurfaceResult.I nurbsSurfaceResult.h \
    nurbsVertex.h nurbsVertex.I \
    parametricCurve.h \
    parametricCurveCollection.I parametricCurveCollection.h \
    piecewiseCurve.h \
    ropeNode.I ropeNode.h \
    sheetNode.I sheetNode.h

  #define IGATESCAN all

#end lib_target

#begin test_bin_target
  #define TARGET test_parametrics
  #define LOCAL_LIBS \
    p3parametrics

  #define SOURCES \
    test_parametrics.cxx

#end test_bin_target
