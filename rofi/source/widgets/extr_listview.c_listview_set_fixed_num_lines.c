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
struct TYPE_3__ {int /*<<< orphan*/  fixed_num_lines; } ;
typedef  TYPE_1__ listview ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

void listview_set_fixed_num_lines ( listview *lv )
{
    if ( lv  ) {
        lv->fixed_num_lines = TRUE;
    }
}