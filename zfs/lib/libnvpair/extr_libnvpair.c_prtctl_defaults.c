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
struct nvlist_prtctl {int nvprt_indentinc; char* nvprt_nmfmt; char* nvprt_eomfmt; char* nvprt_btwnarrfmt; struct nvlist_printops* nvprt_custops; struct nvlist_printops* nvprt_dfltops; scalar_t__ nvprt_btwnarrfmt_nl; scalar_t__ nvprt_indent; int /*<<< orphan*/  nvprt_indent_mode; int /*<<< orphan*/ * nvprt_fp; } ;
struct nvlist_printops {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_INDENT_TABBED ; 
 int /*<<< orphan*/  defprtops ; 

__attribute__((used)) static void
prtctl_defaults(FILE *fp, struct nvlist_prtctl *pctl,
    struct nvlist_printops *ops)
{
	pctl->nvprt_fp = fp;
	pctl->nvprt_indent_mode = NVLIST_INDENT_TABBED;
	pctl->nvprt_indent = 0;
	pctl->nvprt_indentinc = 1;
	pctl->nvprt_nmfmt = "%s = ";
	pctl->nvprt_eomfmt = "\n";
	pctl->nvprt_btwnarrfmt = " ";
	pctl->nvprt_btwnarrfmt_nl = 0;

	pctl->nvprt_dfltops = (struct nvlist_printops *)&defprtops;
	pctl->nvprt_custops = ops;
}