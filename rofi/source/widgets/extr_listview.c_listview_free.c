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
typedef  int /*<<< orphan*/  widget ;
struct TYPE_3__ {unsigned int cur_elements; int /*<<< orphan*/  scrollbar; struct TYPE_3__* listview_name; struct TYPE_3__* boxes; int /*<<< orphan*/  box; } ;
typedef  TYPE_1__ listview ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  widget_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listview_free ( widget *wid )
{
    listview *lv = (listview *) wid;
    for ( unsigned int i = 0; i < lv->cur_elements; i++ ) {
        widget_free ( WIDGET ( lv->boxes [i].box ) );
    }
    g_free ( lv->boxes );

    g_free ( lv->listview_name );
    widget_free ( WIDGET ( lv->scrollbar ) );
    g_free ( lv );
}