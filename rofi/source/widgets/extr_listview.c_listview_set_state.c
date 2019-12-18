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
struct TYPE_3__ {scalar_t__ box; scalar_t__ icon; scalar_t__ textbox; } ;
typedef  TYPE_1__ _listview_row ;
typedef  int /*<<< orphan*/  TextBoxFontType ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (scalar_t__) ; 
 int /*<<< orphan*/  listview_set_style (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listview_set_state ( _listview_row r, TextBoxFontType type )
{
    listview_set_style ( WIDGET(r.box), type);
    listview_set_style ( WIDGET(r.textbox), type);
    if ( r.icon ) {
        listview_set_style ( WIDGET(r.icon), type);
    }
    widget_queue_redraw ( WIDGET( r.box  ) );
}