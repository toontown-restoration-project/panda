// Filename: zSpinParticle.cxx
// Created by:  charles (16Aug00)
//
////////////////////////////////////////////////////////////////////

#include "zSpinParticle.h"

////////////////////////////////////////////////////////////////////
//    Function : ZSpinParticle
//      Access : public
// Description : constructor
////////////////////////////////////////////////////////////////////
ZSpinParticle::
ZSpinParticle(void) :
  BaseParticle() {
  _initial_angle = 0.0f;
  _final_angle = 0.0f;
  _cur_angle = 0.0f;
}

////////////////////////////////////////////////////////////////////
//    Function : ZSpinParticle
//      Access : public
// Description : copy constructor
////////////////////////////////////////////////////////////////////
ZSpinParticle::
ZSpinParticle(const ZSpinParticle &copy) :
  BaseParticle(copy) {
  _initial_angle = copy._initial_angle;
  _final_angle = copy._final_angle;
  _cur_angle = copy._cur_angle;
}

////////////////////////////////////////////////////////////////////
//    Function : ~ZSpinParticle
//      Access : public, virtual
// Description : destructor
////////////////////////////////////////////////////////////////////
ZSpinParticle::
~ZSpinParticle(void) {
}

////////////////////////////////////////////////////////////////////
//    Function : make_copy
//      Access : public, virtual
// Description : dynamic copier
////////////////////////////////////////////////////////////////////
PhysicsObject *ZSpinParticle::
make_copy(void) const {
  return new ZSpinParticle(*this);
}

////////////////////////////////////////////////////////////////////
//    Function : init
//      Access : public, virtual
// Description :
////////////////////////////////////////////////////////////////////
void ZSpinParticle::
init(void) {
}

////////////////////////////////////////////////////////////////////
//    Function : update
//      Access : public, virtual
// Description :
////////////////////////////////////////////////////////////////////
void ZSpinParticle::
update(void) {
  float t = get_parameterized_age();

  // interpolate the current orientation
  _cur_angle = _initial_angle + (t * (_final_angle - _initial_angle));

  // normalize the result to [0..360)
  _cur_angle = fmod(_cur_angle, 360.0f);

  // if _cur_angle was negative, it is still negative after fmod,
  // but greater than -360.
  // wrap it around by adding 360
  if(_cur_angle < 0.0f)
    _cur_angle += 360.0f;
}

////////////////////////////////////////////////////////////////////
//    Function : die
//      Access : public, virtual
// Description :
////////////////////////////////////////////////////////////////////
void ZSpinParticle::
die(void) {
}

////////////////////////////////////////////////////////////////////
//    Function : get_angle
//      Access : public, virtual
// Description :
////////////////////////////////////////////////////////////////////
float ZSpinParticle::
get_angle(void) const {
  return _cur_angle;
}
