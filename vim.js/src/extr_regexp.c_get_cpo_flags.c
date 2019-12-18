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

/* Variables and functions */
 int /*<<< orphan*/  CPO_BACKSL ; 
 int /*<<< orphan*/  CPO_LITERAL ; 
 int /*<<< orphan*/  p_cpo ; 
 int /*<<< orphan*/  reg_cpo_bsl ; 
 int /*<<< orphan*/  reg_cpo_lit ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_cpo_flags()
{
    reg_cpo_lit = vim_strchr(p_cpo, CPO_LITERAL) != NULL;
    reg_cpo_bsl = vim_strchr(p_cpo, CPO_BACKSL) != NULL;
}