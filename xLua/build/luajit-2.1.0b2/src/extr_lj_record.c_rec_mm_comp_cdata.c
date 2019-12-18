#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_11__ {int /*<<< orphan*/  keyv; int /*<<< orphan*/  tabv; int /*<<< orphan*/  key; int /*<<< orphan*/  tab; int /*<<< orphan*/  valv; int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ RecordIndex ;
typedef  int /*<<< orphan*/  MMS ;

/* Variables and functions */
 int /*<<< orphan*/  copyTV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_record_mm_lookup (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_snap_add (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (scalar_t__) ; 
 int /*<<< orphan*/  rec_mm_callcomp (TYPE_1__*,TYPE_2__*,int) ; 
 scalar_t__ tref_iscdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rec_mm_comp_cdata(jit_State *J, RecordIndex *ix, int op, MMS mm)
{
  lj_snap_add(J);
  if (tref_iscdata(ix->val)) {
    ix->tab = ix->val;
    copyTV(J->L, &ix->tabv, &ix->valv);
  } else {
    lua_assert(tref_iscdata(ix->key));
    ix->tab = ix->key;
    copyTV(J->L, &ix->tabv, &ix->keyv);
  }
  lj_record_mm_lookup(J, ix, mm);
  rec_mm_callcomp(J, ix, op);
}