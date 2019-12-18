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
struct TYPE_3__ {int type; double em; double x; double y; double w; double b; double* margin; int list_item; char* id; char* href; struct TYPE_3__* next; scalar_t__ flow_head; struct TYPE_3__* down; scalar_t__ is_first_flow; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  BOX_BLOCK 134 
#define  BOX_BREAK 133 
#define  BOX_FLOW 132 
#define  BOX_INLINE 131 
#define  BOX_TABLE 130 
#define  BOX_TABLE_CELL 129 
#define  BOX_TABLE_ROW 128 
 int /*<<< orphan*/  fz_debug_html_flow (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  indent (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
fz_debug_html_box(fz_context *ctx, fz_html_box *box, int level)
{
	while (box)
	{
		indent(level);
		switch (box->type) {
		case BOX_BLOCK: printf("block"); break;
		case BOX_BREAK: printf("break"); break;
		case BOX_FLOW: printf("flow"); break;
		case BOX_INLINE: printf("inline"); break;
		case BOX_TABLE: printf("table"); break;
		case BOX_TABLE_ROW: printf("table-row"); break;
		case BOX_TABLE_CELL: printf("table-cell"); break;
		}

		printf(" em=%g x=%g y=%g w=%g b=%g\n", box->em, box->x, box->y, box->w, box->b);

		indent(level);
		printf("{\n");
		if (box->type == BOX_BLOCK) {
			indent(level+1);
			printf("margin=%g %g %g %g\n", box->margin[0], box->margin[1], box->margin[2], box->margin[3]);
		}
		if (box->is_first_flow) {
			indent(level+1);
			printf("is-first-flow\n");
		}
		if (box->list_item) {
			indent(level+1);
			printf("list=%d\n", box->list_item);
		}
		if (box->id) {
			indent(level+1);
			printf("id=%s\n", box->id);
		}
		if (box->href) {
			indent(level+1);
			printf("href=%s\n", box->href);
		}

		if (box->down)
			fz_debug_html_box(ctx, box->down, level + 1);
		if (box->flow_head)
			fz_debug_html_flow(ctx, box->flow_head, level + 1);

		indent(level);
		printf("}\n");

		box = box->next;
	}
}