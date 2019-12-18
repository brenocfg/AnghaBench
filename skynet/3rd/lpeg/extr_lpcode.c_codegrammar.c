#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ tag; } ;
typedef  TYPE_1__ TTree ;
typedef  int /*<<< orphan*/  CompileState ;

/* Variables and functions */
 int /*<<< orphan*/  ICall ; 
 int /*<<< orphan*/  IJmp ; 
 int /*<<< orphan*/  IRet ; 
 int MAXRULES ; 
 int /*<<< orphan*/  NOINST ; 
 scalar_t__ TRule ; 
 scalar_t__ TTrue ; 
 int /*<<< orphan*/  addinstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int addoffsetinst (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  correctcalls (int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  fullset ; 
 int gethere (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jumptohere (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 

__attribute__((used)) static void codegrammar (CompileState *compst, TTree *grammar) {
  int positions[MAXRULES];
  int rulenumber = 0;
  TTree *rule;
  int firstcall = addoffsetinst(compst, ICall);  /* call initial rule */
  int jumptoend = addoffsetinst(compst, IJmp);  /* jump to the end */
  int start = gethere(compst);  /* here starts the initial rule */
  jumptohere(compst, firstcall);
  for (rule = sib1(grammar); rule->tag == TRule; rule = sib2(rule)) {
    positions[rulenumber++] = gethere(compst);  /* save rule position */
    codegen(compst, sib1(rule), 0, NOINST, fullset);  /* code rule */
    addinstruction(compst, IRet, 0);
  }
  assert(rule->tag == TTrue);
  jumptohere(compst, jumptoend);
  correctcalls(compst, positions, start, gethere(compst));
}