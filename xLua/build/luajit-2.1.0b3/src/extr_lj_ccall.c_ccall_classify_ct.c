#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  scalar_t__ CTSize ;

/* Variables and functions */
 int CCALL_RCL_INT ; 
 int CCALL_RCL_MEM ; 
 int CCALL_RCL_SSE ; 
 int /*<<< orphan*/  ccall_classify_struct (int /*<<< orphan*/ *,TYPE_1__*,int*,scalar_t__) ; 
 int /*<<< orphan*/  ctype_hassize (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isarray (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isfp (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isstruct (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccall_classify_ct(CTState *cts, CType *ct, int *rcl, CTSize ofs)
{
  if (ctype_isarray(ct->info)) {
    CType *cct = ctype_rawchild(cts, ct);
    CTSize eofs, esz = cct->size, asz = ct->size;
    for (eofs = 0; eofs < asz; eofs += esz)
      ccall_classify_ct(cts, cct, rcl, ofs+eofs);
  } else if (ctype_isstruct(ct->info)) {
    ccall_classify_struct(cts, ct, rcl, ofs);
  } else {
    int cl = ctype_isfp(ct->info) ? CCALL_RCL_SSE : CCALL_RCL_INT;
    lua_assert(ctype_hassize(ct->info));
    if ((ofs & (ct->size-1))) cl = CCALL_RCL_MEM;  /* Unaligned. */
    rcl[(ofs >= 8)] |= cl;
  }
}