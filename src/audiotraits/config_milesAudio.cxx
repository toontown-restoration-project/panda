// Filename: config_milesAudio.cxx
// Created by:  skyler
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

#include "config_milesAudio.h"
#include "milesAudioManager.h"
#include "milesAudioSound.h"
#include "dconfig.h"

ConfigureDef(config_milesAudio);
NotifyCategoryDef(milesAudio, "");

ConfigureFn(config_milesAudio) {
  init_libMilesAudio();
}
/*
const float LinearIntegrator::_max_linear_dt =
  config_milesAudio.GetFloat("default_max_linear_dt", 1.0f / 30.0f);

const float AngularIntegrator::_max_angular_dt =
  config_milesAudio.GetFloat("default_max_angular_dt", 1.0f / 30.0f);

int LinearNoiseForce::_random_seed =
  config_milesAudio.GetInt("default_noise_force_seed", 665);

const float milesAudioObject::_default_terminal_velocity =
  config_milesAudio.GetFloat("default_terminal_velocity", 400.0f);*/

////////////////////////////////////////////////////////////////////
//     Function: init_libMilesAudio
//  Description: Initializes the library.  This must be called at
//               least once before any of the functions or classes in
//               this library can be used.  Normally it will be
//               called by the static initializers and need not be
//               called explicitly, but special cases exist.
////////////////////////////////////////////////////////////////////
void
init_libMilesAudio() {
  static bool initialized = false;
  if (initialized) {
    return;
  }
  initialized = true;
  
  AudioManager::register_AudioManager_creator(Create_AudioManager);
}
