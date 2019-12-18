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
struct parser {scalar_t__ depth; int /*<<< orphan*/ * head; int /*<<< orphan*/  preserve_white; } ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_runetochar (char*,int) ; 
 char* fz_xml_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iswhite (char) ; 
 int /*<<< orphan*/  xml_emit_close_tag (int /*<<< orphan*/ *,struct parser*) ; 
 int /*<<< orphan*/  xml_emit_open_tag (int /*<<< orphan*/ *,struct parser*,char*,char*,int) ; 
 int /*<<< orphan*/  xml_parse_entity (int*,char*) ; 

__attribute__((used)) static void xml_emit_text(fz_context *ctx, struct parser *parser, char *a, char *b)
{
	fz_xml *head;
	char *s;
	int c;

	/* Skip text outside the root tag */
	if (parser->depth == 0)
		return;

	/* Skip all-whitespace text nodes */
	if (!parser->preserve_white)
	{
		for (s = a; s < b; s++)
			if (!iswhite(*s))
				break;
		if (s == b)
			return;
	}

	(void)xml_emit_open_tag(ctx, parser, a, b, 1);
	head = parser->head;

	/* entities are all longer than UTFmax so runetochar is safe */
	s = fz_xml_text(head);
	while (a < b) {
		if (*a == '&') {
			a += xml_parse_entity(&c, a);
			s += fz_runetochar(s, c);
		}
		else {
			*s++ = *a++;
		}
	}
	*s = 0;

	xml_emit_close_tag(ctx, parser);
}