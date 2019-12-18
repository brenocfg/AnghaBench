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
struct TYPE_3__ {scalar_t__ prompt; int /*<<< orphan*/  sw; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 char* mode_get_display_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbox_text (scalar_t__,char const*) ; 

__attribute__((used)) static void rofi_view_update_prompt ( RofiViewState *state )
{
    if ( state->prompt ) {
        const char *str = mode_get_display_name ( state->sw );
        textbox_text ( state->prompt, str );
    }
}