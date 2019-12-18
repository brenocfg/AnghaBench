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
typedef  int /*<<< orphan*/  xps_resource ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * xps_parse_resource_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**) ; 

void
xps_resolve_resource_reference(fz_context *ctx, xps_document *doc, xps_resource *dict,
		char **attp, fz_xml **tagp, char **urip)
{
	if (*attp)
	{
		fz_xml *rsrc = xps_parse_resource_reference(ctx, doc, dict, *attp, urip);
		if (rsrc)
		{
			*attp = NULL;
			*tagp = rsrc;
		}
	}
}