// Filename: qpgeomLinestrips.h
// Created by:  drose (22Mar05)
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

#ifndef qpGEOMLINESTRIPS_H
#define qpGEOMLINESTRIPS_H

#include "pandabase.h"
#include "qpgeomPrimitive.h"

////////////////////////////////////////////////////////////////////
//       Class : qpGeomLinestrips
// Description : Defines a series of line strips.
//
//               This is part of the experimental Geom rewrite.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA qpGeomLinestrips : public qpGeomPrimitive {
PUBLISHED:
  qpGeomLinestrips(qpGeomUsageHint::UsageHint usage_hint);
  qpGeomLinestrips(const qpGeomLinestrips &copy);
  virtual ~qpGeomLinestrips();

  virtual PT(qpGeomPrimitive) make_copy() const;
  virtual PrimitiveType get_primitive_type() const;

public:
  virtual void draw(GraphicsStateGuardianBase *gsg) const;

protected:
  virtual CPT(qpGeomPrimitive) decompose_impl() const;
  virtual CPTA_ushort rotate_impl() const;

public:
  static void register_with_read_factory();

protected:
  static TypedWritable *make_from_bam(const FactoryParams &params);

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    qpGeomPrimitive::init_type();
    register_type(_type_handle, "qpGeomLinestrips",
                  qpGeomPrimitive::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;

  friend class qpGeom;
};

#endif
