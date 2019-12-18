#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_13__ {TYPE_1__* ir; int /*<<< orphan*/ * snapmap; TYPE_2__* snap; } ;
struct TYPE_12__ {scalar_t__ o; int op2; scalar_t__ op1; scalar_t__ prev; } ;
struct TYPE_11__ {size_t mapofs; size_t nent; } ;
struct TYPE_10__ {scalar_t__ prev; } ;
typedef  TYPE_2__ SnapShot ;
typedef  size_t SnapNo ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  size_t MSize ;
typedef  size_t IRRef ;
typedef  TYPE_3__ IRIns ;
typedef  TYPE_4__ GCtrace ;
typedef  int /*<<< orphan*/  BloomFilter ;

/* Variables and functions */
 int IRSLOAD_PARENT ; 
 scalar_t__ IR_HIOP ; 
 scalar_t__ IR_PVAL ; 
 scalar_t__ IR_SLOAD ; 
 scalar_t__ LJ_SOFTFP ; 
 size_t REF_BIAS ; 
 scalar_t__ bloomtest (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int regsp_used (scalar_t__) ; 
 size_t snap_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snap_renamefilter (TYPE_4__*,size_t) ; 
 scalar_t__ snap_renameref (TYPE_4__*,size_t,size_t,scalar_t__) ; 
 scalar_t__ snap_slot (int /*<<< orphan*/ ) ; 

IRIns *lj_snap_regspmap(GCtrace *T, SnapNo snapno, IRIns *ir)
{
  SnapShot *snap = &T->snap[snapno];
  SnapEntry *map = &T->snapmap[snap->mapofs];
  BloomFilter rfilt = snap_renamefilter(T, snapno);
  MSize n = 0;
  IRRef ref = 0;
  for ( ; ; ir++) {
    uint32_t rs;
    if (ir->o == IR_SLOAD) {
      if (!(ir->op2 & IRSLOAD_PARENT)) break;
      for ( ; ; n++) {
	lua_assert(n < snap->nent);
	if (snap_slot(map[n]) == ir->op1) {
	  ref = snap_ref(map[n++]);
	  break;
	}
      }
    } else if (LJ_SOFTFP && ir->o == IR_HIOP) {
      ref++;
    } else if (ir->o == IR_PVAL) {
      ref = ir->op1 + REF_BIAS;
    } else {
      break;
    }
    rs = T->ir[ref].prev;
    if (bloomtest(rfilt, ref))
      rs = snap_renameref(T, snapno, ref, rs);
    ir->prev = (uint16_t)rs;
    lua_assert(regsp_used(rs));
  }
  return ir;
}