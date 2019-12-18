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
struct TYPE_3__ {int box_lines_total; int box_y; int box_idx; int box_start; } ;
typedef  TYPE_1__ intf_sys_t ;

/* Variables and functions */
 int LINES ; 

__attribute__((used)) static void CheckIdx(intf_sys_t *sys)
{
    int lines = sys->box_lines_total;
    int height = LINES - sys->box_y - 2;
    if (height > lines - 1)
        height = lines - 1;

    /* make sure the new index is within the box */
    if (sys->box_idx <= 0) {
        sys->box_idx = 0;
        sys->box_start = 0;
    } else if (sys->box_idx >= lines - 1 && lines > 0) {
        sys->box_idx = lines - 1;
        sys->box_start = sys->box_idx - height;
    }

    /* Fix box start (1st line of the box displayed) */
    if (sys->box_idx < sys->box_start ||
        sys->box_idx > height + sys->box_start + 1) {
        sys->box_start = sys->box_idx - height/2;
        if (sys->box_start < 0)
            sys->box_start = 0;
    } else if (sys->box_idx == sys->box_start - 1) {
        sys->box_start--;
    } else if (sys->box_idx == height + sys->box_start + 1) {
        sys->box_start++;
    }
}