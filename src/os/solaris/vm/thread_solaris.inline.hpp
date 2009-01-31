#ifdef USE_PRAGMA_IDENT_HDR
#pragma ident "%W% %E% %U% JVM"
#endif
/*
 * Copyright 2002-2003 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 *  
 */

// Thread::current is "hot" it's called > 128K times in the 1st 500 msecs of
// startup.
// ThreadLocalStorage::thread is warm -- it's called > 16K times in the same
// period.   Thread::current() now calls ThreadLocalStorage::thread() directly.
// For SPARC, to avoid excessive register window spill-fill faults,
// we aggressively inline these routines.  

inline Thread* ThreadLocalStorage::thread()  {
  // don't use specialized code if +UseMallocOnly -- may confuse Purify et al.
  debug_only(if (UseMallocOnly) return get_thread_slow(););

  uintptr_t raw = pd_raw_thread_id();
  int ix = pd_cache_index(raw);
  Thread *Candidate = ThreadLocalStorage::_get_thread_cache[ix];
  if (Candidate->_self_raw_id == raw) {
    // hit
    return Candidate;
  } else {
    return ThreadLocalStorage::get_thread_via_cache_slowly(raw, ix);
  }
}
