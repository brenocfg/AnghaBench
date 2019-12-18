#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ k; } ;
struct LHS_assign {int /*<<< orphan*/ * prev; TYPE_3__ v; } ;
struct TYPE_7__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  SETARG_C (int /*<<< orphan*/ ,int) ; 
 scalar_t__ VCALL ; 
 int /*<<< orphan*/  assignment (TYPE_1__*,struct LHS_assign*,int) ; 
 int /*<<< orphan*/  getcode (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  primaryexp (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static void exprstat (LexState *ls) {
  /* stat -> func | assignment */
  FuncState *fs = ls->fs;
  struct LHS_assign v;
  primaryexp(ls, &v.v);
  if (v.v.k == VCALL)  /* stat -> func */
    SETARG_C(getcode(fs, &v.v), 1);  /* call statement uses no results */
  else {  /* stat -> assignment */
    v.prev = NULL;
    assignment(ls, &v, 1);
  }
}