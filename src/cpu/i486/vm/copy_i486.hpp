#ifdef USE_PRAGMA_IDENT_HDR
#pragma ident "%W% %E% %U% JVM"
#endif
/*
 * Copyright 2003-2004 Sun Microsystems, Inc.  All Rights Reserved.
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

// Inline functions for memory copy and fill.

// Contains inline asm implementations
#include "incls/_copy_pd.inline.hpp.incl"

static void pd_fill_to_words(HeapWord* tohw, size_t count, juint value) {
  juint* to = (juint*)tohw;
  count *= HeapWordSize / BytesPerInt;
  while (count-- > 0) {
    *to++ = value;
  }
}

static void pd_fill_to_aligned_words(HeapWord* tohw, size_t count, juint value) {
  pd_fill_to_words(tohw, count, value);
}

static void pd_fill_to_bytes(void* to, size_t count, jubyte value) {
  (void)memset(to, value, count);
}

static void pd_zero_to_words(HeapWord* tohw, size_t count) {
  pd_fill_to_words(tohw, count, 0);
}

static void pd_zero_to_bytes(void* to, size_t count) {
  (void)memset(to, 0, count);
}
