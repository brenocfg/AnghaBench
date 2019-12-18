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
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  ExpDesc ;
typedef  scalar_t__ BinOpr ;

/* Variables and functions */
 scalar_t__ OPR_AND ; 
 scalar_t__ OPR_CONCAT ; 
 scalar_t__ OPR_EQ ; 
 scalar_t__ OPR_NE ; 
 scalar_t__ OPR_OR ; 
 int /*<<< orphan*/  bcemit_branch_f (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcemit_branch_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_isk_nojump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_isnumk_nojump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_toanyreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_tonextreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcemit_binop_left(FuncState *fs, BinOpr op, ExpDesc *e)
{
  if (op == OPR_AND) {
    bcemit_branch_t(fs, e);
  } else if (op == OPR_OR) {
    bcemit_branch_f(fs, e);
  } else if (op == OPR_CONCAT) {
    expr_tonextreg(fs, e);
  } else if (op == OPR_EQ || op == OPR_NE) {
    if (!expr_isk_nojump(e)) expr_toanyreg(fs, e);
  } else {
    if (!expr_isnumk_nojump(e)) expr_toanyreg(fs, e);
  }
}