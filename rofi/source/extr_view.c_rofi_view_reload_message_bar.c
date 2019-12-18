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
struct TYPE_3__ {int /*<<< orphan*/ * mesg_box; int /*<<< orphan*/  mesg_tb; int /*<<< orphan*/  sw; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* mode_get_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbox_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  widget_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rofi_view_reload_message_bar ( RofiViewState *state )
{
    if ( state->mesg_box == NULL ) {
        return;
    }
    char *msg = mode_get_message ( state->sw );
    if ( msg ) {
        textbox_text ( state->mesg_tb, msg );
        widget_enable ( WIDGET ( state->mesg_box ) );
        g_free ( msg );
    }
    else {
        widget_disable ( WIDGET ( state->mesg_box ) );
    }
}