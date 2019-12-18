#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TTree ;
typedef  int /*<<< orphan*/  CompileState ;
typedef  int /*<<< orphan*/  Charset ;

/* Variables and functions */
 int /*<<< orphan*/  IChoice ; 
 int /*<<< orphan*/  IFail ; 
 int /*<<< orphan*/  IFailTwice ; 
 int /*<<< orphan*/  NOINST ; 
 int /*<<< orphan*/  addinstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int addoffsetinst (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int codetestset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fullset ; 
 int getfirst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ headfail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jumptohere (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void codenot (CompileState *compst, TTree *tree) {
  Charset st;
  int e = getfirst(tree, fullset, &st);
  int test = codetestset(compst, &st, e);
  if (headfail(tree))  /* test (fail(p1)) -> L1; fail; L1:  */
    addinstruction(compst, IFail, 0);
  else {
    /* test(fail(p))-> L1; choice L1; <p>; failtwice; L1:  */
    int pchoice = addoffsetinst(compst, IChoice);
    codegen(compst, tree, 0, NOINST, fullset);
    addinstruction(compst, IFailTwice, 0);
    jumptohere(compst, pchoice);
  }
  jumptohere(compst, test);
}