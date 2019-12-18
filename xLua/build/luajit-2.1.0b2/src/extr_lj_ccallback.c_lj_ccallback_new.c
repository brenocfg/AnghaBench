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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  L; int /*<<< orphan*/ * miscmap; } ;
typedef  scalar_t__ MSize ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  int /*<<< orphan*/  GCfunc ;
typedef  int /*<<< orphan*/  CType ;
typedef  TYPE_1__ CTState ;

/* Variables and functions */
 int /*<<< orphan*/ * callback_checkfunc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* callback_slot2ptr (TYPE_1__*,scalar_t__) ; 
 scalar_t__ callback_slot_new (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_gc_anybarriert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_tab_setint (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setfuncV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void *lj_ccallback_new(CTState *cts, CType *ct, GCfunc *fn)
{
  ct = callback_checkfunc(cts, ct);
  if (ct) {
    MSize slot = callback_slot_new(cts, ct);
    GCtab *t = cts->miscmap;
    setfuncV(cts->L, lj_tab_setint(cts->L, t, (int32_t)slot), fn);
    lj_gc_anybarriert(cts->L, t);
    return callback_slot2ptr(cts, slot);
  }
  return NULL;  /* Bad conversion. */
}