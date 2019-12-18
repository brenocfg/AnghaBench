#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* base_uri; int /*<<< orphan*/  base_xml; struct TYPE_4__* next; } ;
typedef  TYPE_1__ xps_resource ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_xml (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
xps_drop_resource_dictionary(fz_context *ctx, xps_document *doc, xps_resource *dict)
{
	xps_resource *next;
	while (dict)
	{
		next = dict->next;
		fz_drop_xml(ctx, dict->base_xml);
		fz_free(ctx, dict->base_uri);
		fz_free(ctx, dict);
		dict = next;
	}
}