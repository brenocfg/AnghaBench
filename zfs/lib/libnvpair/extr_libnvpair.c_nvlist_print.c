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
struct nvlist_prtctl {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_print_with_indent (int /*<<< orphan*/ *,struct nvlist_prtctl*) ; 
 int /*<<< orphan*/  prtctl_defaults (int /*<<< orphan*/ *,struct nvlist_prtctl*,int /*<<< orphan*/ *) ; 

void
nvlist_print(FILE *fp, nvlist_t *nvl)
{
	struct nvlist_prtctl pc;

	prtctl_defaults(fp, &pc, NULL);
	nvlist_print_with_indent(nvl, &pc);
}