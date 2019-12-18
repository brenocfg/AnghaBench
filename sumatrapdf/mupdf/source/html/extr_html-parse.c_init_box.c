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
struct TYPE_3__ {int /*<<< orphan*/ * style; int /*<<< orphan*/  markup_dir; int /*<<< orphan*/ * flow_head; int /*<<< orphan*/ ** flow_tail; int /*<<< orphan*/ * next; int /*<<< orphan*/ * down; int /*<<< orphan*/ * up; scalar_t__ b; scalar_t__ w; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_bidi_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BOX_BLOCK ; 

__attribute__((used)) static void init_box(fz_context *ctx, fz_html_box *box, fz_bidi_direction markup_dir)
{
	box->type = BOX_BLOCK;
	box->x = box->y = 0;
	box->w = box->b = 0;

	box->up = NULL;
	box->down = NULL;
	box->next = NULL;

	box->flow_head = NULL;
	box->flow_tail = &box->flow_head;
	box->markup_dir = markup_dir;
	box->style = NULL;
}