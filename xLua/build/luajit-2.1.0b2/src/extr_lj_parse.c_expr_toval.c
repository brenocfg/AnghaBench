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

/* Variables and functions */
 int /*<<< orphan*/  expr_discharge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ expr_hasjump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_toanyreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void expr_toval(FuncState *fs, ExpDesc *e)
{
  if (expr_hasjump(e))
    expr_toanyreg(fs, e);
  else
    expr_discharge(fs, e);
}