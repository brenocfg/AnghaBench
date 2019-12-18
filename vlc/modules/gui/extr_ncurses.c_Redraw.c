#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_7__ {int box_type; int box_height; int box_y; int box_lines_total; int box_start; int /*<<< orphan*/  color; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 int BOX_NONE ; 
 scalar_t__ COLS ; 
 int /*<<< orphan*/  DrawBox (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawEmptyLine (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int DrawStatus (TYPE_1__*) ; 
 int /*<<< orphan*/  FillBox (TYPE_1__*) ; 
 int LINES ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 scalar_t__ __MIN (int,int) ; 
 int /*<<< orphan*/ * box_title ; 
 int /*<<< orphan*/  refresh () ; 

__attribute__((used)) static void Redraw(intf_thread_t *intf)
{
    intf_sys_t *sys   = intf->p_sys;
    int         box   = sys->box_type;
    int         y     = DrawStatus(intf);

    sys->box_height = LINES - y - 2;
    DrawBox(y++, sys->box_height, sys->color, _(box_title[box]));

    sys->box_y = y;

    if (box != BOX_NONE) {
        FillBox(intf);

        if (sys->box_lines_total == 0)
            sys->box_start = 0;
        else if (sys->box_start > sys->box_lines_total - 1)
            sys->box_start = sys->box_lines_total - 1;
        y += __MIN(sys->box_lines_total - sys->box_start,
                   sys->box_height);
    }

    while (y < LINES - 1)
        DrawEmptyLine(y++, 1, COLS - 2);

    refresh();
}