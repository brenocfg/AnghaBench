#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  BOX_BLOCK 132 
#define  BOX_FLOW 131 
#define  BOX_TABLE 130 
#define  BOX_TABLE_CELL 129 
#define  BOX_TABLE_ROW 128 
 int /*<<< orphan*/  draw_block_box (int /*<<< orphan*/ *,TYPE_1__*,float,float,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  draw_flow_box (int /*<<< orphan*/ *,TYPE_1__*,float,float,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void draw_box(fz_context *ctx, fz_html_box *box, float page_top, float page_bot, fz_device *dev, fz_matrix ctm, hb_buffer_t *hb_buf)
{
	switch (box->type)
	{
	case BOX_TABLE:
	case BOX_TABLE_ROW:
	case BOX_TABLE_CELL:
	case BOX_BLOCK:
		draw_block_box(ctx, box, page_top, page_bot, dev, ctm, hb_buf);
		break;
	case BOX_FLOW:
		draw_flow_box(ctx, box, page_top, page_bot, dev, ctm, hb_buf);
		break;
	}
}