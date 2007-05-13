// Filename: simpleLru.cxx
// Created by:  drose (11May07)
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

#include "simpleLru.h"


////////////////////////////////////////////////////////////////////
//     Function: SimpleLru::Destructor
//       Access: Published, Virtual
//  Description: 
////////////////////////////////////////////////////////////////////
SimpleLru::
~SimpleLru() {
#ifndef NDEBUG
  // We're shutting down.  Force-remove everything remaining, but
  // don't explicitly evict it (that would force vertex buffers to
  // write themselves to disk unnecessarily).
  while (_next != (LinkedListNode *)this) {
    nassertv(_next != (LinkedListNode *)NULL);
    ((SimpleLruPage *)_next)->_lru = NULL;
    ((SimpleLruPage *)_next)->remove_from_list();
  }
#endif
}

////////////////////////////////////////////////////////////////////
//     Function: SimpleLru::do_evict
//       Access: Private
//  Description: Evicts pages until the LRU is within tolerance.
////////////////////////////////////////////////////////////////////
void SimpleLru::
do_evict() {
  // Store the current end of the list.  If pages re-enqueue
  // themselves during this traversal, we don't want to visit them
  // twice.
  SimpleLruPage *end = (SimpleLruPage *)_prev;

  // Now walk through the list.
  SimpleLruPage *node = (SimpleLruPage *)_next;
  while (_total_size > _max_size) {
    SimpleLruPage *next = (SimpleLruPage *)node->_next;
    
    node->evict_lru();
    if (node == end) {
      // If we reach the original tail of the list, stop.
      return;
    }
    node = next;
  }
}

////////////////////////////////////////////////////////////////////
//     Function: SimpleLruPage::Destructor
//       Access: Published, Virtual
//  Description: 
////////////////////////////////////////////////////////////////////
SimpleLruPage::
~SimpleLruPage() {
  if (_lru != NULL) {
    dequeue_lru();
  }
}

////////////////////////////////////////////////////////////////////
//     Function: SimpleLruPage::evict_lru
//       Access: Published, Virtual
//  Description: Evicts the page from the LRU.  Called internally when
//               the LRU determines that it is full.  May also be
//               called externally when necessary to explicitly evict
//               the page.
//
//               It is legal for this method to either evict the page
//               as requested, do nothing (in which case the eviction
//               will be requested again at the next epoch), or
//               requeue itself on the tail of the queue (in which
//               case the eviction will be requested again much
//               later).
////////////////////////////////////////////////////////////////////
void SimpleLruPage::
evict_lru() {
  dequeue_lru();
}
