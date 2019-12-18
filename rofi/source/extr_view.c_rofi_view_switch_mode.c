#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int num_modi; void* refilter; void* reload; int /*<<< orphan*/  const* sw; int /*<<< orphan*/ * modi; scalar_t__ sidebar_bar; scalar_t__ prompt; } ;
typedef  TYPE_1__ RofiViewState ;
typedef  int /*<<< orphan*/  const Mode ;

/* Variables and functions */
 int /*<<< orphan*/  HIGHLIGHT ; 
 int /*<<< orphan*/  NORMAL ; 
 void* TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_get_display_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* rofi_get_mode (unsigned int) ; 
 int /*<<< orphan*/  rofi_view_refilter (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_restart (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_set_window_title (char*) ; 
 int /*<<< orphan*/  rofi_view_update (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  rofi_view_update_prompt (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_font (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rofi_view_switch_mode ( RofiViewState *state, Mode *mode )
{
    state->sw = mode;
    // Update prompt;
    if ( state->prompt ) {
        rofi_view_update_prompt ( state );
    }
    if ( state->sw ) {
        char * title = g_strdup_printf ( "rofi - %s", mode_get_display_name (state->sw ) );
        rofi_view_set_window_title ( title );
        g_free ( title );
    } else {
        rofi_view_set_window_title ( "rofi" );
    }
    if ( state->sidebar_bar ) {
        for ( unsigned int j = 0; j < state->num_modi; j++ ) {
            const Mode * mode = rofi_get_mode ( j );
            textbox_font ( state->modi[j], ( mode == state->sw ) ? HIGHLIGHT : NORMAL );
        }
    }
    rofi_view_restart ( state );
    state->reload   = TRUE;
    state->refilter = TRUE;
    rofi_view_refilter ( state );
    rofi_view_update ( state, TRUE );
}