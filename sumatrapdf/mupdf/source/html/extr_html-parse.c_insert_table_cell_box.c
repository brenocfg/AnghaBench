#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; struct TYPE_9__* up; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  BOX_TABLE_CELL ; 
 scalar_t__ BOX_TABLE_ROW ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  insert_block_box (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  insert_box (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static fz_html_box *insert_table_cell_box(fz_context *ctx, fz_html_box *box, fz_html_box *top)
{
	fz_html_box *tr = top;
	while (tr && tr->type != BOX_TABLE_ROW)
		tr = tr->up;
	if (tr)
	{
		insert_box(ctx, box, BOX_TABLE_CELL, tr);
		return tr;
	}
	fz_warn(ctx, "table-cell not inside table-row element");
	insert_block_box(ctx, box, top);
	return top;
}