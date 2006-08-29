// Filename: conditionVar.h
// Created by:  drose (09Aug02)
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

#ifndef CONDITIONVAR_H
#define CONDITIONVAR_H

#include "pandabase.h"
#include "conditionVarDebug.h"
#include "conditionVarDirect.h"

////////////////////////////////////////////////////////////////////
//       Class : ConditionVar
// Description : A condition variable, usually used to communicate
//               information about changing state to a thread that is
//               waiting for something to happen.  A condition
//               variable can be used to "wake up" a thread when some
//               arbitrary condition has changed.

//               The ConditionVar class does not support the full
//               semantics of POSIX condition variables.  In
//               particular, it does not support the broadcast or
//               signal_all function.  See ConditionVarFull for a more
//               complete (but possibly more expensive) API.
//
//               A condition variable is associated with a single
//               mutex, and several condition variables may share the
//               same mutex.
//
//               This class inherits its implementation either from
//               ConditionVarDebug or ConditionVarDirect, depending on
//               the definition of DEBUG_THREADS.
////////////////////////////////////////////////////////////////////
#ifdef DEBUG_THREADS
class EXPCL_PANDA ConditionVar : public ConditionVarDebug
#else
class EXPCL_PANDA ConditionVar : public ConditionVarDirect
#endif  // DEBUG_THREADS
{
public:
  INLINE ConditionVar(Mutex &mutex);
  INLINE ~ConditionVar();
private:
  INLINE ConditionVar(const ConditionVar &copy);
  INLINE void operator = (const ConditionVar &copy);

  // These methods are inherited from the base class.
  // INLINE void wait();
  // INLINE void signal();

private:
  // The signal_all() method is specifically *not* provided by
  // ConditionVar.  Use ConditionVarFull if you need to call this
  // method.
  INLINE void signal_all();

public:
  INLINE Mutex &get_mutex() const;
};

#include "conditionVar.I"

#endif
