#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct parser {TYPE_2__* head; } ;
struct TYPE_3__ {char* text; } ;
struct TYPE_4__ {TYPE_1__ u; } ;
typedef  TYPE_2__ fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  xml_emit_close_tag (int /*<<< orphan*/ *,struct parser*) ; 
 int /*<<< orphan*/  xml_emit_open_tag (int /*<<< orphan*/ *,struct parser*,char*,char*,int) ; 

__attribute__((used)) static void xml_emit_cdata(fz_context *ctx, struct parser *parser, char *a, char *b)
{
	fz_xml *head;
	char *s;

	(void)xml_emit_open_tag(ctx, parser, a, b, 1);
	head = parser->head;

	s = head->u.text;
	while (a < b)
		*s++ = *a++;
	*s = 0;

	xml_emit_close_tag(ctx, parser);
}