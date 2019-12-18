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
struct TYPE_3__ {int /*<<< orphan*/ * overlay; int /*<<< orphan*/ * list_view; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_queue_redraw () ; 
 int /*<<< orphan*/  textbox_text (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  widget_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_enable (int /*<<< orphan*/ ) ; 

void rofi_view_set_overlay ( RofiViewState *state, const char *text )
{
    if ( state->overlay == NULL || state->list_view == NULL ) {
        return;
    }
    if ( text == NULL ) {
        widget_disable ( WIDGET ( state->overlay ) );
        return;
    }
    widget_enable ( WIDGET ( state->overlay ) );
    textbox_text ( state->overlay, text );
    // We want to queue a repaint.
    rofi_view_queue_redraw ( );
}