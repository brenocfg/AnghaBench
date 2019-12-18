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
struct TYPE_4__ {scalar_t__ text; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  rofi_view_set_selected_line (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbox_text (scalar_t__,char*) ; 

void rofi_view_clear_input ( RofiViewState *state )
{
    if ( state->text ) {
        textbox_text ( state->text, "" );
        rofi_view_set_selected_line ( state, 0 );
    }
}