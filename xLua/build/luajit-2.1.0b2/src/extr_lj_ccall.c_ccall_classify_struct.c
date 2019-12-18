#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int size; int /*<<< orphan*/  info; scalar_t__ sib; } ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int CTSize ;

/* Variables and functions */
 int CCALL_RCL_INT ; 
 int CCALL_RCL_MEM ; 
 int /*<<< orphan*/  CTA_SUBTYPE ; 
 int /*<<< orphan*/  ccall_classify_ct (int /*<<< orphan*/ *,TYPE_1__*,int*,int) ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ctype_isbitfield (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isfield (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isxattrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int ccall_classify_struct(CTState *cts, CType *ct, int *rcl, CTSize ofs)
{
  if (ct->size > 16) return CCALL_RCL_MEM;  /* Too big, gets memory class. */
  while (ct->sib) {
    CTSize fofs;
    ct = ctype_get(cts, ct->sib);
    fofs = ofs+ct->size;
    if (ctype_isfield(ct->info))
      ccall_classify_ct(cts, ctype_rawchild(cts, ct), rcl, fofs);
    else if (ctype_isbitfield(ct->info))
      rcl[(fofs >= 8)] |= CCALL_RCL_INT;  /* NYI: unaligned bitfields? */
    else if (ctype_isxattrib(ct->info, CTA_SUBTYPE))
      ccall_classify_struct(cts, ctype_rawchild(cts, ct), rcl, fofs);
  }
  return ((rcl[0]|rcl[1]) & CCALL_RCL_MEM);  /* Memory class? */
}