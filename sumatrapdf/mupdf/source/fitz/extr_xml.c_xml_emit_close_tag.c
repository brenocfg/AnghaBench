#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parser {TYPE_1__* head; int /*<<< orphan*/  depth; } ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {struct TYPE_2__* up; int /*<<< orphan*/ * next; } ;

/* Variables and functions */

__attribute__((used)) static void xml_emit_close_tag(fz_context *ctx, struct parser *parser)
{
	parser->depth--;
	parser->head->next = NULL;
	if (parser->head->up)
		parser->head = parser->head->up;
}