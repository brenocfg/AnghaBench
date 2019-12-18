#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  info; } ;
struct TYPE_15__ {TYPE_1__ s; } ;
struct TYPE_16__ {scalar_t__ k; TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
struct TYPE_17__ {int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  GETARG_B (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_OPCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_REG ; 
 scalar_t__ OP_NOT ; 
 int /*<<< orphan*/  OP_TEST ; 
 int /*<<< orphan*/  OP_TESTSET ; 
 scalar_t__ VRELOCABLE ; 
 int condjump (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  discharge2anyreg (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  freeexp (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  getcode (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static int jumponcond (FuncState *fs, expdesc *e, int cond) {
  if (e->k == VRELOCABLE) {
    Instruction ie = getcode(fs, e);
    if (GET_OPCODE(ie) == OP_NOT) {
      fs->pc--;  /* remove previous OP_NOT */
      return condjump(fs, OP_TEST, GETARG_B(ie), 0, !cond);
    }
    /* else go through */
  }
  discharge2anyreg(fs, e);
  freeexp(fs, e);
  return condjump(fs, OP_TESTSET, NO_REG, e->u.s.info, cond);
}