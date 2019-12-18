#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {TYPE_1__* ir; } ;
struct TYPE_10__ {TYPE_2__ cur; } ;
struct TYPE_9__ {TYPE_5__* J; } ;
struct TYPE_7__ {int /*<<< orphan*/  s; scalar_t__ r; } ;
typedef  int /*<<< orphan*/  SnapNo ;
typedef  scalar_t__ Reg ;
typedef  size_t IRRef ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_NIL ; 
 int /*<<< orphan*/  IR_RENAME ; 
 int /*<<< orphan*/  SPS_NONE ; 
 int /*<<< orphan*/  lj_ir_emit (TYPE_5__*) ; 
 int /*<<< orphan*/  lj_ir_set (TYPE_5__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t tref_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ra_addrename(ASMState *as, Reg down, IRRef ref, SnapNo snapno)
{
  IRRef ren;
  lj_ir_set(as->J, IRT(IR_RENAME, IRT_NIL), ref, snapno);
  ren = tref_ref(lj_ir_emit(as->J));
  as->J->cur.ir[ren].r = (uint8_t)down;
  as->J->cur.ir[ren].s = SPS_NONE;
}