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
struct TYPE_3__ {int /*<<< orphan*/  refilter; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ textbox_append_text (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void rofi_view_handle_text ( RofiViewState *state, char *text )
{
    if ( textbox_append_text ( state->text, text, strlen ( text ) ) ) {
        state->refilter = TRUE;
    }
}