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
typedef  int /*<<< orphan*/  fz_output ;
struct TYPE_3__ {struct TYPE_3__* next; struct TYPE_3__* down; int /*<<< orphan*/  uri; int /*<<< orphan*/  title; scalar_t__ is_open; } ;
typedef  TYPE_1__ fz_outline ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_print_outline(fz_context *ctx, fz_output *out, fz_outline *outline, int level)
{
	int i;
	while (outline)
	{
		if (outline->down)
			fz_write_byte(ctx, out, outline->is_open ? '-' : '+');
		else
			fz_write_byte(ctx, out, '|');

		for (i = 0; i < level; i++)
			fz_write_byte(ctx, out, '\t');
		fz_write_printf(ctx, out, "%q\t%s\n", outline->title, outline->uri);
		if (outline->down)
			fz_print_outline(ctx, out, outline->down, level + 1);
		outline = outline->next;
	}
}