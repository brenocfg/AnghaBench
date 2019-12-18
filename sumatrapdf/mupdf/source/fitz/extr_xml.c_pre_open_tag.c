#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct parser {int /*<<< orphan*/  for_html; TYPE_1__* head; } ;
struct TYPE_4__ {struct TYPE_4__* up; } ;
typedef  TYPE_1__ fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int CONTAINER ; 
 int find_html_tag (char*,int) ; 
 int fz_xml_html_tag__NONE ; 
 char* fz_xml_tag (TYPE_1__*) ; 
 TYPE_2__* html_tags ; 
 int /*<<< orphan*/  open_implied (int /*<<< orphan*/ *,struct parser*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xml_emit_close_tag (int /*<<< orphan*/ *,struct parser*) ; 

__attribute__((used)) static void
pre_open_tag(fz_context *ctx, struct parser *parser, char *mark, char *p)
{
	fz_xml *head = parser->head;
	int tag_num;

	if (!parser->for_html)
		return;

	tag_num = find_html_tag(mark, p-mark);

	if (tag_num == fz_xml_html_tag__NONE)
		return;

	if ((html_tags[tag_num].flags & CONTAINER) == 0)
	{
		/* We aren't a container flag. This means that we should autoclose up to
		 * any matching tags in the same container. */
		fz_xml *which;
		for (which = head; which; which = which->up)
		{
			char *tag = fz_xml_tag(which);
			int tag_num2 = tag ? find_html_tag(tag, strlen(tag)) : fz_xml_html_tag__NONE;
			if (tag_num == tag_num2)
			{
				/* Autoclose everything from head to which inclusive */
				while (1)
				{
					int done = (head == which);
					xml_emit_close_tag(ctx, parser);
					head = head->up;
					if (done)
						break;
				}
				break;
			}
			if (html_tags[tag_num2].flags & CONTAINER)
			{
				/* Stop searching */
				break;
			}
		}
	}

	/* Now, autoopen any tags implied by this one. */
	open_implied(ctx, parser, tag_num);
}