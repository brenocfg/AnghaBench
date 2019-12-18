#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  L; } ;
typedef  int /*<<< orphan*/  GCcdata ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_1__ CTState ;
typedef  int /*<<< orphan*/  CTSize ;
typedef  int CTInfo ;

/* Variables and functions */
 int CTF_VLA ; 
 scalar_t__ CT_MEMALIGN ; 
 scalar_t__ ctype_align (int) ; 
 int /*<<< orphan*/ * lj_cdata_new (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_cdata_newv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

GCcdata *lj_cdata_newx(CTState *cts, CTypeID id, CTSize sz, CTInfo info)
{
  if (!(info & CTF_VLA) && ctype_align(info) <= CT_MEMALIGN)
    return lj_cdata_new(cts, id, sz);
  else
    return lj_cdata_newv(cts->L, id, sz, ctype_align(info));
}