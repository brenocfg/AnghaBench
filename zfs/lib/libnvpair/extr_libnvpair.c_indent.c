#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* nvlist_prtctl_t ;
struct TYPE_3__ {int nvprt_indent_mode; int nvprt_indentinc; int /*<<< orphan*/  nvprt_fp; int /*<<< orphan*/  nvprt_indent; } ;

/* Variables and functions */
#define  NVLIST_INDENT_ABS 129 
#define  NVLIST_INDENT_TABBED 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
indent(nvlist_prtctl_t pctl, int onemore)
{
	int depth;

	switch (pctl->nvprt_indent_mode) {
	case NVLIST_INDENT_ABS:
		(void) fprintf(pctl->nvprt_fp, "%*s",
		    pctl->nvprt_indent + onemore * pctl->nvprt_indentinc, "");
		break;

	case NVLIST_INDENT_TABBED:
		depth = pctl->nvprt_indent + onemore;
		while (depth-- > 0)
			(void) fprintf(pctl->nvprt_fp, "\t");
	}
}