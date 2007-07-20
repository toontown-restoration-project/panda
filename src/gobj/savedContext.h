// Filename: savedContext.h
// Created by:  drose (11Jun01)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://etc.cmu.edu/panda3d/docs/license/ .
//
// To contact the maintainers of this program write to
// panda3d-general@lists.sourceforge.net .
//
////////////////////////////////////////////////////////////////////

#ifndef SAVEDCONTEXT_H
#define SAVEDCONTEXT_H

#include "pandabase.h"

#include "typedObject.h"

////////////////////////////////////////////////////////////////////
//       Class : SavedContext
// Description : This is the base class for all GSG-specific context
//               objects, such as TextureContext and GeomContext.  It
//               exists mainly to provide some structural
//               organization.  At the moment, there are no methods
//               common to all of these objects, but there might be
//               one day.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA_GOBJ SavedContext : public TypedObject {
public:
  INLINE SavedContext();

PUBLISHED:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
public:
  static void init_type() {
    TypedObject::init_type();
    register_type(_type_handle, "SavedContext",
                  TypedObject::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;
};

#include "savedContext.I"

#endif

