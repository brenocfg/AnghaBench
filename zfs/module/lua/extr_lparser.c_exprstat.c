#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ k; } ;
struct LHS_assign {TYPE_4__ v; int /*<<< orphan*/ * prev; } ;
struct TYPE_9__ {char token; } ;
struct TYPE_10__ {TYPE_1__ t; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  SETARG_C (int /*<<< orphan*/ ,int) ; 
 scalar_t__ VCALL ; 
 int /*<<< orphan*/  assignment (TYPE_2__*,struct LHS_assign*,int) ; 
 int /*<<< orphan*/  check_condition (TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  getcode (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  suffixedexp (TYPE_2__*,TYPE_4__*) ; 

__attribute__((used)) static void exprstat (LexState *ls) {
  /* stat -> func | assignment */
  FuncState *fs = ls->fs;
  struct LHS_assign v;
  suffixedexp(ls, &v.v);
  if (ls->t.token == '=' || ls->t.token == ',') { /* stat -> assignment ? */
    v.prev = NULL;
    assignment(ls, &v, 1);
  }
  else {  /* stat -> func */
    check_condition(ls, v.v.k == VCALL, "syntax error");
    SETARG_C(getcode(fs, &v.v), 1);  /* call statement uses no results */
  }
}