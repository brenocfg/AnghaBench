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
typedef  int /*<<< orphan*/  CPValue ;
typedef  int /*<<< orphan*/  CPState ;

/* Variables and functions */
 int /*<<< orphan*/  cp_expr_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_opt (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void cp_expr_comma(CPState *cp, CPValue *k)
{
  do { cp_expr_sub(cp, k, 0); } while (cp_opt(cp, ','));
}