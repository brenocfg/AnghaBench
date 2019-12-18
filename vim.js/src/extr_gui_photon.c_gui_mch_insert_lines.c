#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int scroll_region_bot; int char_height; scalar_t__ scroll_region_right; scalar_t__ scroll_region_left; int /*<<< orphan*/  vimTextArea; } ;
struct TYPE_12__ {int y; scalar_t__ x; } ;
struct TYPE_10__ {void* y; void* x; } ;
struct TYPE_9__ {void* y; void* x; } ;
struct TYPE_11__ {TYPE_2__ lr; TYPE_1__ ul; } ;
typedef  TYPE_3__ PhRect_t ;
typedef  TYPE_4__ PhPoint_t ;

/* Variables and functions */
 void* FILL_X (scalar_t__) ; 
 void* FILL_Y (int) ; 
 int /*<<< orphan*/  PgFlush () ; 
 int /*<<< orphan*/  PhBlit (int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  PhTranslatePoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PhTranslateRect (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtFindDisjoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtWidgetOffset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtWidgetPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtWidgetRid (int /*<<< orphan*/ ) ; 
 TYPE_5__ gui ; 
 int /*<<< orphan*/  gui_clear_block (int,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  gui_ph_raw_offset ; 

void
gui_mch_insert_lines(int row, int num_lines)
{
    PhRect_t    rect;
    PhPoint_t   delta;

    rect.ul.x = FILL_X(gui.scroll_region_left);
    rect.ul.y = FILL_Y(row);

    rect.lr.x = FILL_X(gui.scroll_region_right + 1) - 1;
    rect.lr.y = FILL_Y(gui.scroll_region_bot - num_lines + 1) - 1;

    PtWidgetOffset(gui.vimTextArea, &gui_ph_raw_offset);
    PhTranslatePoint(&gui_ph_raw_offset, PtWidgetPos(gui.vimTextArea, NULL));
    PhTranslateRect(&rect, &gui_ph_raw_offset);

    delta.x = 0;
    delta.y = num_lines * gui.char_height;

    PgFlush();

    PhBlit(PtWidgetRid(PtFindDisjoint(gui.vimTextArea)) , &rect, &delta);

    gui_clear_block(row, gui.scroll_region_left,
	    row + num_lines - 1, gui.scroll_region_right);
}