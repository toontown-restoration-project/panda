// Filename: config_char.cxx
// Created by:  drose (28Feb00)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://www.panda3d.org/license.txt .
//
// To contact the maintainers of this program write to
// panda3d@yahoogroups.com .
//
////////////////////////////////////////////////////////////////////

#if defined(WIN32_VC) && !defined(NO_PCH)
#include "char_headers.h"
#endif

#pragma hdrstop

#if !defined(WIN32_VC) || defined(NO_PCH)
#include "config_char.h"
#include "character.h"
#include "characterJoint.h"
#include "characterJointBundle.h"
#include "characterSlider.h"
#include "computedVertices.h"
#include "dynamicVertices.h"
#endif

#include <dconfig.h>
#include <lmatrix4.h>

Configure(config_char);
NotifyCategoryDef(char, "");

ConfigureFn(config_char) {
  Character::init_type();
  CharacterJoint::init_type();
  CharacterJointBundle::init_type();
  CharacterSlider::init_type();
  ComputedVertices::init_type();
  DynamicVertices::init_type();

  // This isn't defined in this package, but it *is* essential that it
  // be initialized.  We have to do it explicitly here since template
  // statics don't necessarily resolve very well across dynamic
  // libraries.
  LMatrix4f::init_type();

  //Registration of writeable object's creation
  //functions with BamReader's factory
  Character::register_with_read_factory();
  CharacterJoint::register_with_read_factory();
  CharacterJointBundle::register_with_read_factory();
  CharacterSlider::register_with_read_factory();
  ComputedVertices::register_with_read_factory();
}

