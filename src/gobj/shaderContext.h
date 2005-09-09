// Filename: shaderContext.h
// Created by: jyelon (01Sep05)
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

#ifndef SHADERCONTEXT_H
#define SHADERCONTEXT_H

#include "pandabase.h"
#include "internalName.h"
#include "savedContext.h"
#include "shader.h"

////////////////////////////////////////////////////////////////////
//       Class : ShaderContext
// Description : The ShaderContext is meant to contain the compiled
//               version of a shader string.  ShaderContext is an
//               abstract base class, there will be a subclass of it
//               for each shader language and graphics API.
//               Since the languages are so different and the
//               graphics APIs have so little in common, the base
//               class contains almost nothing.  All the implementation
//               details are in the subclasses.
////////////////////////////////////////////////////////////////////

class EXPCL_PANDA ShaderContext: public SavedContext {
public:
  INLINE ShaderContext(Shader *shader);
  
  Shader *_shader;

  enum {
    VERT_SHADER=0,
    FRAG_SHADER=1,
    BOTH_SHADER=2,
  };
  
public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    TypedObject::init_type();
    register_type(_type_handle, "ShaderContext",
                  TypedObject::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;
};

#include "shaderContext.I"

#endif
