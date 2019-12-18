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
struct TYPE_3__ {int /*<<< orphan*/  list_view; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  listview_set_selected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void rofi_view_nav_first ( RofiViewState * state )
{
//    state->selected = 0;
    listview_set_selected ( state->list_view, 0 );
}