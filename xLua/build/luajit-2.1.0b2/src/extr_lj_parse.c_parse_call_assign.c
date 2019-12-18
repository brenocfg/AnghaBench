#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ k; } ;
struct TYPE_10__ {int /*<<< orphan*/ * prev; TYPE_7__ v; } ;
struct TYPE_9__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ LHSVarList ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ VCALL ; 
 int /*<<< orphan*/  bcptr (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  expr_primary (TYPE_1__*,TYPE_7__*) ; 
 int /*<<< orphan*/  parse_assignment (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  setbc_b (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void parse_call_assign(LexState *ls)
{
  FuncState *fs = ls->fs;
  LHSVarList vl;
  expr_primary(ls, &vl.v);
  if (vl.v.k == VCALL) {  /* Function call statement. */
    setbc_b(bcptr(fs, &vl.v), 1);  /* No results. */
  } else {  /* Start of an assignment. */
    vl.prev = NULL;
    parse_assignment(ls, &vl, 1);
  }
}