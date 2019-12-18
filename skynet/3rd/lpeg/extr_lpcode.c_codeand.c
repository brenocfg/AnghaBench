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

/* Variables and functions */
 int /*<<< orphan*/  IBackCommit ; 
 int /*<<< orphan*/  IBehind ; 
 int /*<<< orphan*/  IChoice ; 
 int /*<<< orphan*/  IFail ; 
 int MAXBEHIND ; 
 int /*<<< orphan*/  addinstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int addoffsetinst (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int fixedlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fullset ; 
 int /*<<< orphan*/  hascaptures (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jumptohere (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void codeand (CompileState *compst, TTree *tree, int tt) {
  int n = fixedlen(tree);
  if (n >= 0 && n <= MAXBEHIND && !hascaptures(tree)) {
    codegen(compst, tree, 0, tt, fullset);
    if (n > 0)
      addinstruction(compst, IBehind, n);
  }
  else {  /* default: Choice L1; p1; BackCommit L2; L1: Fail; L2: */
    int pcommit;
    int pchoice = addoffsetinst(compst, IChoice);
    codegen(compst, tree, 0, tt, fullset);
    pcommit = addoffsetinst(compst, IBackCommit);
    jumptohere(compst, pchoice);
    addinstruction(compst, IFail, 0);
    jumptohere(compst, pcommit);
  }
}