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
struct TYPE_3__ {char* base_uri; int /*<<< orphan*/ * data; int /*<<< orphan*/  name; struct TYPE_3__* next; struct TYPE_3__* parent; } ;
typedef  TYPE_1__ xps_resource ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static fz_xml *
xps_lookup_resource(fz_context *ctx, xps_document *doc, xps_resource *dict, char *name, char **urip)
{
	xps_resource *head, *node;
	for (head = dict; head; head = head->parent)
	{
		for (node = head; node; node = node->next)
		{
			if (!strcmp(node->name, name))
			{
				if (urip && head->base_uri)
					*urip = head->base_uri;
				return node->data;
			}
		}
	}
	return NULL;
}