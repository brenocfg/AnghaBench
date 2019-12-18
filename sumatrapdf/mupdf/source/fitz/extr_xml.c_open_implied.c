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
struct parser {TYPE_1__* head; } ;
struct TYPE_4__ {struct TYPE_4__* up; } ;
typedef  TYPE_1__ fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int flags; char* tag; } ;

/* Variables and functions */
 int IMPLIES_MASK ; 
 int IMPLIES_SHIFT ; 
 int IMPLIES_SHIFT2 ; 
 int IMPLIES_SHIFT3 ; 
 int TABLE_MASK ; 
 int TABLE_SHIFT ; 
 int find_html_tag (char*,int) ; 
 int fz_xml_html_tag__NONE ; 
 int fz_xml_html_tag_table ; 
 char* fz_xml_tag (TYPE_1__*) ; 
 TYPE_2__* html_tags ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xml_emit_close_tag (int /*<<< orphan*/ *,struct parser*) ; 
 int /*<<< orphan*/  xml_emit_open_tag (int /*<<< orphan*/ *,struct parser*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
open_implied(fz_context *ctx, struct parser *parser, int tag)
{
	fz_xml *head;
	int implied, implied2, implied3, tag_num;
	int table_level;

	if (tag == fz_xml_html_tag__NONE)
		return;

	implied  = (html_tags[tag].flags >> IMPLIES_SHIFT) & IMPLIES_MASK;
	implied2 = (html_tags[tag].flags >> IMPLIES_SHIFT2) & IMPLIES_MASK;
	implied3 = (html_tags[tag].flags >> IMPLIES_SHIFT3) & IMPLIES_MASK;
	if (implied == fz_xml_html_tag__NONE)
		return;
	if (implied2 == fz_xml_html_tag__NONE)
		implied2 = implied;
	if (implied3 == fz_xml_html_tag__NONE)
		implied3 = implied;

	/* So, check to see whether implied{,2,3} is present. */
	table_level = (html_tags[tag].flags>>TABLE_SHIFT) & TABLE_MASK;
	if (table_level != 0)
	{
		/* Table tag. Autoclose anything within the current TABLE
		 * with >= table_level. */
		fz_xml *close_to = NULL;
		int implied_found = 0;
		for (head = parser->head; head; head = head->up)
		{
			char *tag = fz_xml_tag(head);
			int level;

			if (tag == NULL)
				continue;
			tag_num = find_html_tag(tag, strlen(tag));
			level = (html_tags[tag_num].flags>>TABLE_SHIFT) & TABLE_MASK;
			if (level >= table_level)
				close_to = head;
			if (tag_num == implied || tag_num == implied2 || tag_num == implied3)
				implied_found = 1;
			if (tag_num == fz_xml_html_tag_table)
				break;
		}
		if (close_to)
		{
			for (head = parser->head; head; head = head->up)
			{
				xml_emit_close_tag(ctx, parser);
				if (head == close_to)
					break;
			}
		}
		if (!implied_found)
		{
			char *tag = html_tags[implied].tag;
			open_implied(ctx, parser, implied);
			xml_emit_open_tag(ctx, parser, tag, tag + strlen(tag), 0);
		}
	}
	else
	{
		/* Non table tag. Open by implication. */
		for (head = parser->head; head; head = head->up)
		{
			char *tag = fz_xml_tag(head);

			if (tag == NULL)
				continue;
			tag_num = find_html_tag(tag, strlen(tag));
			if (tag_num == implied || tag_num == implied2 || tag_num == implied3)
				break;
		}
		if (head == NULL)
		{
			char *s = html_tags[implied].tag;
			open_implied(ctx, parser, implied);
			(void)xml_emit_open_tag(ctx, parser, s, s+strlen(s), 0);
		}
	}
}