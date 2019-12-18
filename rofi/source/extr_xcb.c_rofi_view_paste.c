#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ property; int /*<<< orphan*/  requestor; } ;
typedef  TYPE_2__ xcb_selection_notify_event_t ;
typedef  char gchar ;
struct TYPE_5__ {scalar_t__ UTF8_STRING; } ;
struct TYPE_7__ {TYPE_1__ ewmh; } ;
typedef  int /*<<< orphan*/  RofiViewState ;

/* Variables and functions */
 scalar_t__ XCB_ATOM_NONE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_warning (char*) ; 
 int /*<<< orphan*/  rofi_view_handle_text (int /*<<< orphan*/ *,char*) ; 
 unsigned int strlen (char*) ; 
 char* window_get_text_prop (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* xcb ; 

__attribute__((used)) static void rofi_view_paste ( RofiViewState *state, xcb_selection_notify_event_t *xse )
{
    if ( xse->property == XCB_ATOM_NONE ) {
        g_warning ( "Failed to convert selection" );
    }
    else if ( xse->property == xcb->ewmh.UTF8_STRING ) {
        gchar *text = window_get_text_prop ( xse->requestor, xcb->ewmh.UTF8_STRING );
        if ( text != NULL && text[0] != '\0' ) {
            unsigned int dl = strlen ( text );
            // Strip new line
            for ( unsigned int i = 0; i < dl; i++ ) {
                if ( text[i] == '\n' ) {
                    text[i] = '\0';
                }
            }
            rofi_view_handle_text ( state, text );
        }
        g_free ( text );
    }
    else {
        g_warning ( "Failed" );
    }
}