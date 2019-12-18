#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_get_property_cookie_t ;
struct TYPE_5__ {scalar_t__ strings_len; int /*<<< orphan*/  strings; } ;
typedef  TYPE_1__ xcb_ewmh_get_utf8_strings_reply_t ;
struct TYPE_6__ {int /*<<< orphan*/  ewmh; } ;

/* Variables and functions */
 int WM_DO_NOT_CHANGE_CURRENT_DESKTOP ; 
 int WM_PANGO_WORKSPACE_NAMES ; 
 int current_window_manager ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_strcmp0 (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* xcb ; 
 scalar_t__ xcb_ewmh_get_supporting_wm_check_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_ewmh_get_supporting_wm_check_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_ewmh_get_utf8_strings_reply_wipe (TYPE_1__*) ; 
 scalar_t__ xcb_ewmh_get_wm_name_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,void*) ; 
 int /*<<< orphan*/  xcb_ewmh_get_wm_name_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_stuff_get_root_window () ; 

__attribute__((used)) static void x11_helper_discover_window_manager ( void )
{
    xcb_window_t              wm_win = 0;
    xcb_get_property_cookie_t cc     = xcb_ewmh_get_supporting_wm_check_unchecked ( &xcb->ewmh,
                                                                                    xcb_stuff_get_root_window () );

    if ( xcb_ewmh_get_supporting_wm_check_reply ( &xcb->ewmh, cc, &wm_win, NULL ) ) {
        xcb_ewmh_get_utf8_strings_reply_t wtitle;
        xcb_get_property_cookie_t         cookie = xcb_ewmh_get_wm_name_unchecked ( &( xcb->ewmh ), wm_win );
        if (  xcb_ewmh_get_wm_name_reply ( &( xcb->ewmh ), cookie, &wtitle, (void *) 0 ) ) {
            if ( wtitle.strings_len > 0 ) {
                g_debug ( "Found window manager: %s", wtitle.strings );
                if ( g_strcmp0 ( wtitle.strings, "i3" ) == 0 ) {
                    current_window_manager = WM_DO_NOT_CHANGE_CURRENT_DESKTOP | WM_PANGO_WORKSPACE_NAMES;
                }
            }
            xcb_ewmh_get_utf8_strings_reply_wipe ( &wtitle );
        }
    }
}