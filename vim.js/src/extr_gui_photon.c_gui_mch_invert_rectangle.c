#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int char_width; int char_height; } ;
struct TYPE_6__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_7__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {TYPE_1__ lr; TYPE_2__ ul; } ;
typedef  TYPE_3__ PhRect_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRAW_END ; 
 int /*<<< orphan*/  DRAW_START ; 
 scalar_t__ FILL_X (int) ; 
 scalar_t__ FILL_Y (int) ; 
 int /*<<< orphan*/  PgDrawRect (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgSetDrawMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pg_DRAW_FILL ; 
 int /*<<< orphan*/  Pg_DrawModeDSTINVERT ; 
 int /*<<< orphan*/  Pg_DrawModeSRCCOPY ; 
 TYPE_4__ gui ; 

void
gui_mch_invert_rectangle(int row, int col, int nr, int nc)
{
    PhRect_t rect;

    rect.ul.x = FILL_X(col);
    rect.ul.y = FILL_Y(row);

    /* FIXME: This has an off by one pixel problem */
    rect.lr.x = rect.ul.x + nc * gui.char_width;
    rect.lr.y = rect.ul.y + nr * gui.char_height;
    if (nc > 0)
	rect.lr.x -= 1;
    if (nr > 0)
	rect.lr.y -= 1;

    DRAW_START;
    PgSetDrawMode(Pg_DrawModeDSTINVERT);
    PgDrawRect(&rect, Pg_DRAW_FILL);
    PgSetDrawMode(Pg_DrawModeSRCCOPY);
    DRAW_END;
}