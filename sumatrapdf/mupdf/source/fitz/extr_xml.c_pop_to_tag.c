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
struct parser {TYPE_1__* head; scalar_t__ for_html; } ;
struct TYPE_3__ {struct TYPE_3__* up; } ;
typedef  TYPE_1__ fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_strncasecmp (char*,char*,int) ; 
 char* fz_xml_tag (TYPE_1__*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  xml_emit_close_tag (int /*<<< orphan*/ *,struct parser*) ; 

__attribute__((used)) static int
pop_to_tag(fz_context *ctx, struct parser *parser, char *mark, char *p)
{
	fz_xml *to, *head;

	/* Run up from the tag */
	if (parser->for_html)
	{
		for (to = parser->head; to; to = to->up)
		{
			char *tag = fz_xml_tag(to);
			if (tag && fz_strncasecmp(tag, mark, p-mark) == 0 && tag[p-mark] == 0)
				break; /* Found a matching tag */
		}
	}
	else
	{
		for (to = parser->head; to; to = to->up)
		{
			char *tag = fz_xml_tag(to);
			if (tag && strncmp(tag, mark, p-mark) == 0 && tag[p-mark] == 0)
				break; /* Found a matching tag */
		}
	}

	if (to == NULL)
	{
		/* We didn't find a matching enclosing tag. Don't close anything. */
		return 0;
	}

	/* Pop everything up to and including this tag. */
	for (head = parser->head; head != to; head = head->up)
		xml_emit_close_tag(ctx, parser);
	return 1;
}