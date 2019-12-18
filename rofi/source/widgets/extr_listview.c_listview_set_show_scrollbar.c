#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  scrollbar; } ;
typedef  TYPE_1__ listview ;
typedef  scalar_t__ gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_recompute_elements (TYPE_1__*) ; 
 int /*<<< orphan*/  widget_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_enable (int /*<<< orphan*/ ) ; 

void listview_set_show_scrollbar ( listview *lv, gboolean enabled )
{
    if ( lv ) {
        if ( enabled ) {
            widget_enable ( WIDGET ( lv->scrollbar ) );
        }
        else {
            widget_disable ( WIDGET ( lv->scrollbar ) );
        }
        listview_recompute_elements ( lv );
    }
}