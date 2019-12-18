#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
struct TYPE_7__ {struct TYPE_7__* next; struct TYPE_7__* down; int /*<<< orphan*/  page; void* uri; void* title; } ;
typedef  TYPE_1__ fz_outline ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 void* Memento_label (int /*<<< orphan*/ ,char*) ; 
 int atoi (char*) ; 
 TYPE_1__* fz_new_outline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_strdup (int /*<<< orphan*/ *,char*) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 TYPE_1__* xps_lookup_last_outline_at_level (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 TYPE_3__ xps_lookup_link_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fz_outline *
xps_parse_document_outline(fz_context *ctx, xps_document *doc, fz_xml *root)
{
	fz_xml *node;
	fz_outline *head = NULL, *entry, *tail;
	int last_level = 1, this_level;
	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
	{
		if (fz_xml_is_tag(node, "OutlineEntry"))
		{
			char *level = fz_xml_att(node, "OutlineLevel");
			char *target = fz_xml_att(node, "OutlineTarget");
			char *description = fz_xml_att(node, "Description");
			if (!target || !description)
				continue;

			entry = fz_new_outline(ctx);
			entry->title = Memento_label(fz_strdup(ctx, description), "outline_title");
			entry->uri = Memento_label(fz_strdup(ctx, target), "outline_uri");
			entry->page = xps_lookup_link_target(ctx, (fz_document*)doc, target, NULL, NULL).page;
			entry->down = NULL;
			entry->next = NULL;

			this_level = level ? atoi(level) : 1;

			if (!head)
			{
				head = entry;
			}
			else
			{
				tail = xps_lookup_last_outline_at_level(ctx, doc, head, 1, this_level);
				if (this_level > last_level)
					tail->down = entry;
				else
					tail->next = entry;
			}

			last_level = this_level;
		}
	}
	return head;
}