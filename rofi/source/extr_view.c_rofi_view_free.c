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
struct TYPE_4__ {scalar_t__ num_modi; struct TYPE_4__* modi; struct TYPE_4__* distance; struct TYPE_4__* line_map; int /*<<< orphan*/  main_window; int /*<<< orphan*/ * tokens; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  helper_tokenize_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_free (int /*<<< orphan*/ ) ; 

void rofi_view_free ( RofiViewState *state )
{
    if ( state->tokens ) {
        helper_tokenize_free ( state->tokens );
        state->tokens = NULL;
    }
    // Do this here?
    // Wait for final release?
    widget_free ( WIDGET ( state->main_window ) );

    g_free ( state->line_map );
    g_free ( state->distance );
    // Free the switcher boxes.
    // When state is free'ed we should no longer need these.
    g_free ( state->modi );
    state->num_modi = 0;
    g_free ( state );
}