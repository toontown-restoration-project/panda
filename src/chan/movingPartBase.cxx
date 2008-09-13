// Filename: movingPartBase.cxx
// Created by:  drose (22Feb99)
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

#include "movingPartBase.h"
#include "animControl.h"
#include "animChannelBase.h"
#include "bitArray.h"
#include "config_chan.h"
#include "dcast.h"
#include "indent.h"

TypeHandle MovingPartBase::_type_handle;


////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
MovingPartBase::
MovingPartBase(PartGroup *parent, const string &name)
  : PartGroup(parent, name) {
}

////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::Constructor
//       Access: Protected
//  Description:
////////////////////////////////////////////////////////////////////
MovingPartBase::
MovingPartBase() {
}

////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::clear_forced_channel
//       Access: Published, Virtual
//  Description: Undoes the effect of a previous call to
//               apply_freeze() or apply_control().  Returns true if
//               the joint was modified, false otherwise.
////////////////////////////////////////////////////////////////////
bool MovingPartBase::
clear_forced_channel() {
  if (_forced_channel != (AnimChannelBase *)NULL) {
    _forced_channel.clear();
    return true;
  }
  return false;
}

////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::get_forced_channel
//       Access: Published, Virtual
//  Description: Returns the AnimChannelBase that has been forced to
//               this joint by a previous call to apply_freeze() or
//               apply_control(), or NULL if no such channel has been
//               applied.
////////////////////////////////////////////////////////////////////
AnimChannelBase *MovingPartBase::
get_forced_channel() const {
  return _forced_channel;
}

////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::write
//       Access: Published, Virtual
//  Description: Writes a brief description of the channel and all of
//               its descendants.
////////////////////////////////////////////////////////////////////
void MovingPartBase::
write(ostream &out, int indent_level) const {
  indent(out, indent_level) << get_value_type() << " " << get_name();
  if (_children.empty()) {
    out << "\n";
  } else {
    out << " {\n";
    write_descendants(out, indent_level + 2);
    indent(out, indent_level) << "}\n";
  }
}

////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::write_with_value
//       Access: Published, Virtual
//  Description: Writes a brief description of the channel and all of
//               its descendants, along with their values.
////////////////////////////////////////////////////////////////////
void MovingPartBase::
write_with_value(ostream &out, int indent_level) const {
  indent(out, indent_level) << get_value_type() << " " << get_name() << "\n";
  indent(out, indent_level);
  output_value(out);

  if (_children.empty()) {
    out << "\n";
  } else {
    out << " {\n";
    write_descendants_with_value(out, indent_level + 2);
    indent(out, indent_level) << "}\n";
  }
}

////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::do_update
//       Access: Public, Virtual
//  Description: Recursively update this particular part and all of
//               its descendents for the current frame.  This is not
//               really public and is not intended to be called
//               directly; it is called from the top of the tree by
//               PartBundle::update().
//
//               The return value is true if any part has changed,
//               false otherwise.
////////////////////////////////////////////////////////////////////
bool MovingPartBase::
do_update(PartBundle *root, const CycleData *root_cdata, PartGroup *parent,
          bool parent_changed, bool anim_changed,
          Thread *current_thread) {
  bool any_changed = false;
  bool needs_update = anim_changed;

  // See if any of the channel values have changed since last time.

  if (_forced_channel != (AnimChannelBase *)NULL) {
    if (!needs_update) {
      needs_update = _forced_channel->has_changed(0, 0.0, 0, 0.0);
    }

  } else {
    const PartBundle::CData *cdata = (const PartBundle::CData *)root_cdata;
    PartBundle::ChannelBlend::const_iterator bci;
    for (bci = cdata->_blend.begin();
         !needs_update && bci != cdata->_blend.end();
         ++bci) {
      AnimControl *control = (*bci).first;

      AnimChannelBase *channel = NULL;
      int channel_index = control->get_channel_index();
      if (channel_index >= 0 && channel_index < (int)_channels.size()) {
        channel = _channels[channel_index];
      }
      if (channel != (AnimChannelBase*)NULL) {
        needs_update = control->channel_has_changed(channel, cdata->_frame_blend_flag);
      }
    }
  }

  if (needs_update) {
    // Ok, get the latest value.
    get_blend_value(root);
  }

  if (parent_changed || needs_update) {
    any_changed = update_internals(root, parent, needs_update, parent_changed,
                                   current_thread);
  }

  // Now recurse.
  Children::iterator ci;
  for (ci = _children.begin(); ci != _children.end(); ++ci) {
    if ((*ci)->do_update(root, root_cdata, this, 
                         parent_changed || needs_update,
                         anim_changed, current_thread)) {
      any_changed = true;
    }
  }

  return any_changed;
}


////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::update_internals
//       Access: Public, Virtual
//  Description: This is called by do_update() whenever the part or
//               some ancestor has changed values.  It is a hook for
//               derived classes to update whatever cache they may
//               have that depends on these.
//
//               The return value is true if the part has changed as a
//               result of the update, or false otherwise.
////////////////////////////////////////////////////////////////////
bool MovingPartBase::
update_internals(PartBundle *, PartGroup *, bool, bool, Thread *) {
  return true;
}

////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::pick_channel_index
//       Access: Protected
//  Description: Walks the part hierarchy, looking for a suitable
//               channel index number to use.  Available index numbers
//               are the elements of the holes set, as well as next to
//               infinity.
////////////////////////////////////////////////////////////////////
void MovingPartBase::
pick_channel_index(plist<int> &holes, int &next) const {
  // Verify each of the holes.

  plist<int>::iterator ii, ii_next;
  ii = holes.begin();
  while (ii != holes.end()) {
    ii_next = ii;
    ++ii_next;

    int hole = (*ii);
    nassertv(hole >= 0 && hole < next);
    if (hole < (int)_channels.size() ||
        _channels[hole] != (AnimChannelBase *)NULL) {
      // We can't accept this hole; we're using it!
      holes.erase(ii);
    }
    ii = ii_next;
  }

  // Now do we have any more to restrict?
  if (next < (int)_channels.size()) {
    int i;
    for (i = next; i < (int)_channels.size(); i++) {
      if (_channels[i] == (AnimChannelBase*)NULL) {
        // Here's a hole we do have.
        holes.push_back(i);
      }
    }
    next = _channels.size();
  }

  PartGroup::pick_channel_index(holes, next);
}



////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::bind_hierarchy
//       Access: Protected, Virtual
//  Description: Binds the indicated anim hierarchy to the part
//               hierarchy, at the given channel index number.
////////////////////////////////////////////////////////////////////
void MovingPartBase::
bind_hierarchy(AnimGroup *anim, int channel_index, int &joint_index, 
               bool is_included, BitArray &bound_joints,
               const PartSubset &subset) {
  if (subset.matches_include(get_name())) {
    is_included = true;
  } else if (subset.matches_exclude(get_name())) {
    is_included = false;
  }

  if (chan_cat.is_debug()) {
    chan_cat.debug()
      << "binding " << *this << " to " << *anim << ", is_included = "
      << is_included << "\n";
  }
  while ((int)_channels.size() <= channel_index) {
    _channels.push_back((AnimChannelBase*)NULL);
  }

  nassertv(_channels[channel_index] == (AnimChannelBase*)NULL);

  if (is_included) {
    if (anim == (AnimGroup*)NULL) {
      // If we're binding to the NULL anim, it means actually to create
      // a default AnimChannel that just returns the part's initial
      // value.
      _channels[channel_index] = make_initial_channel();
    } else {
      _channels[channel_index] = DCAST(AnimChannelBase, anim);
    }

    // Record that we have bound this joint in the bound_joints
    // BitArray.
    bound_joints.set_bit(joint_index);
  } else {
    // Record that we have *not* bound this particular joint.
    bound_joints.clear_bit(joint_index);
  }
  ++joint_index;

  PartGroup::bind_hierarchy(anim, channel_index, joint_index, 
                            is_included, bound_joints, subset);
}

////////////////////////////////////////////////////////////////////
//     Function: MovingPartBase::find_bound_joints
//       Access: Protected, Virtual
//  Description: Similar to bind_hierarchy, but does not actually
//               perform any binding.  All it does is compute the
//               BitArray bount_joints according to the specified
//               subset.  This is useful in preparation for
//               asynchronous binding--in this case, we may need to
//               know bound_joints immediately, without having to wait
//               for the animation itself to load and bind.
////////////////////////////////////////////////////////////////////
void MovingPartBase::
find_bound_joints(int &joint_index, bool is_included, BitArray &bound_joints,
                  const PartSubset &subset) {
  if (subset.matches_include(get_name())) {
    is_included = true;
  } else if (subset.matches_exclude(get_name())) {
    is_included = false;
  }

  bound_joints.set_bit_to(joint_index, is_included);
  ++joint_index;

  PartGroup::find_bound_joints(joint_index, is_included, bound_joints, subset);
}
