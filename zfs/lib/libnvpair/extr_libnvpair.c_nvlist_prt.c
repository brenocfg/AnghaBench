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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  nvlist_prtctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_print_with_indent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
nvlist_prt(nvlist_t *nvl, nvlist_prtctl_t pctl)
{
	nvlist_print_with_indent(nvl, pctl);
}