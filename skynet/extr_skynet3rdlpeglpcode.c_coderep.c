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
struct TYPE_8__ {int /*<<< orphan*/  cs; } ;
typedef  int /*<<< orphan*/  TTree ;
typedef  int /*<<< orphan*/  CompileState ;
typedef  TYPE_1__ Charset ;

/* Variables and functions */
 int /*<<< orphan*/  IChoice ; 
 int /*<<< orphan*/  IJmp ; 
 int /*<<< orphan*/  IPartialCommit ; 
 int /*<<< orphan*/  ISpan ; 
 int NOINST ; 
 int /*<<< orphan*/  addcharset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addinstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int addoffsetinst (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int codetestset (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ cs_disjoint (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  fullset ; 
 int getfirst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int gethere (int /*<<< orphan*/ *) ; 
 scalar_t__ headfail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jumptohere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jumptothere (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ tocharset (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void coderep (CompileState *compst, TTree *tree, int opt,
                     const Charset *fl) {
  Charset st;
  if (tocharset(tree, &st)) {
    addinstruction(compst, ISpan, 0);
    addcharset(compst, st.cs);
  }
  else {
    int e1 = getfirst(tree, fullset, &st);
    if (headfail(tree) || (!e1 && cs_disjoint(&st, fl))) {
      /* L1: test (fail(p1)) -> L2; <p>; jmp L1; L2: */
      int jmp;
      int test = codetestset(compst, &st, 0);
      codegen(compst, tree, 0, test, fullset);
      jmp = addoffsetinst(compst, IJmp);
      jumptohere(compst, test);
      jumptothere(compst, jmp, test);
    }
    else {
      /* test(fail(p1)) -> L2; choice L2; L1: <p>; partialcommit L1; L2: */
      /* or (if 'opt'): partialcommit L1; L1: <p>; partialcommit L1; */
      int commit, l2;
      int test = codetestset(compst, &st, e1);
      int pchoice = NOINST;
      if (opt)
        jumptohere(compst, addoffsetinst(compst, IPartialCommit));
      else
        pchoice = addoffsetinst(compst, IChoice);
      l2 = gethere(compst);
      codegen(compst, tree, 0, NOINST, fullset);
      commit = addoffsetinst(compst, IPartialCommit);
      jumptothere(compst, commit, l2);
      jumptohere(compst, pchoice);
      jumptohere(compst, test);
    }
  }
}