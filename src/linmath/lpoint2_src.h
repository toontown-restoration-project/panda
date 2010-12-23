// Filename: lpoint2_src.h
// Created by:  drose (08Mar00)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
//       Class : LPoint2
// Description : This is a two-component point in space.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA_LINMATH FLOATNAME(LPoint2) : public FLOATNAME(LVecBase2) {
PUBLISHED:
  INLINE_LINMATH FLOATNAME(LPoint2)();
  INLINE_LINMATH FLOATNAME(LPoint2)(const FLOATNAME(LVecBase2) &copy);
  INLINE_LINMATH FLOATNAME(LPoint2) &operator = (const FLOATNAME(LVecBase2) &copy);
  INLINE_LINMATH FLOATNAME(LPoint2) &operator = (FLOATTYPE fill_value);
  INLINE_LINMATH FLOATNAME(LPoint2)(FLOATTYPE fill_value);
  INLINE_LINMATH FLOATNAME(LPoint2)(FLOATTYPE x, FLOATTYPE y);

#ifdef HAVE_PYTHON
  PyObject *__getattr__(const string &attr_name) const;
  int __setattr__(PyObject *self, const string &attr_name, PyObject *assign);
#endif

  INLINE_LINMATH static const FLOATNAME(LPoint2) &zero();
  INLINE_LINMATH static const FLOATNAME(LPoint2) &unit_x();
  INLINE_LINMATH static const FLOATNAME(LPoint2) &unit_y();

  INLINE_LINMATH FLOATNAME(LPoint2) operator - () const;

  INLINE_LINMATH FLOATNAME(LVecBase2)
  operator + (const FLOATNAME(LVecBase2) &other) const;
  INLINE_LINMATH FLOATNAME(LPoint2)
  operator + (const FLOATNAME(LVector2) &other) const;

  INLINE_LINMATH FLOATNAME(LVecBase2)
  operator - (const FLOATNAME(LVecBase2) &other) const;
  INLINE_LINMATH FLOATNAME(LVector2)
  operator - (const FLOATNAME(LPoint2) &other) const;
  INLINE_LINMATH FLOATNAME(LPoint2)
  operator - (const FLOATNAME(LVector2) &other) const;

  INLINE_LINMATH FLOATNAME(LPoint2) operator * (FLOATTYPE scalar) const;
  INLINE_LINMATH FLOATNAME(LPoint2) operator / (FLOATTYPE scalar) const;
  INLINE_LINMATH FLOATNAME(LPoint2) project(const FLOATNAME(LVecBase2) &onto) const;

#ifdef HAVE_PYTHON
  INLINE_LINMATH void python_repr(ostream &out, const string &class_name) const;
#endif

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type();

private:
  static TypeHandle _type_handle;
};

#include "lpoint2_src.I"
