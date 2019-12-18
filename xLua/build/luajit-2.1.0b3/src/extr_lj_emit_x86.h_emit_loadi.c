#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_8__ {scalar_t__ o; } ;
struct TYPE_7__ {scalar_t__ curins; scalar_t__* mcp; TYPE_1__* T; } ;
struct TYPE_6__ {scalar_t__ nins; } ;
typedef  int Reg ;
typedef  scalar_t__ MCode ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 TYPE_5__* IR (scalar_t__) ; 
 scalar_t__ IR_HIOP ; 
 scalar_t__ LJ_32 ; 
 int /*<<< orphan*/  REXRB (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ XI_MOVri ; 
 int /*<<< orphan*/  XO_ARITH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOg_XOR ; 
 int /*<<< orphan*/  emit_rr (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void emit_loadi(ASMState *as, Reg r, int32_t i)
{
  /* XOR r,r is shorter, but modifies the flags. This is bad for HIOP. */
  if (i == 0 && !(LJ_32 && (IR(as->curins)->o == IR_HIOP ||
			    (as->curins+1 < as->T->nins &&
			     IR(as->curins+1)->o == IR_HIOP)))) {
    emit_rr(as, XO_ARITH(XOg_XOR), r, r);
  } else {
    MCode *p = as->mcp;
    *(int32_t *)(p-4) = i;
    p[-5] = (MCode)(XI_MOVri+(r&7));
    p -= 5;
    REXRB(p, 0, r);
    as->mcp = p;
  }
}