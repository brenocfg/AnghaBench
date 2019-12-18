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
struct TYPE_3__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ xcb_screen_t ;
typedef  int /*<<< orphan*/  xcb_pixmap_t ;
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_property_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  xcb_atom_t ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_ATOM_PIXMAP ; 
 int /*<<< orphan*/  XCB_NONE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xcb_get_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xcb_get_property_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_property_value (int /*<<< orphan*/ *) ; 
 int xcb_get_property_value_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xcb_pixmap_t get_root_pixmap ( xcb_connection_t *c,
                                      xcb_screen_t *screen,
                                      xcb_atom_t atom )
{
    xcb_get_property_cookie_t cookie;
    xcb_get_property_reply_t  *reply;
    xcb_pixmap_t              rootpixmap = XCB_NONE;

    cookie = xcb_get_property ( c,
                                0,
                                screen->root,
                                atom,
                                XCB_ATOM_PIXMAP,
                                0,
                                1 );

    reply = xcb_get_property_reply ( c, cookie, NULL );

    if ( reply ) {
        if ( xcb_get_property_value_length ( reply ) == sizeof ( xcb_pixmap_t ) ) {
            memcpy ( &rootpixmap, xcb_get_property_value ( reply ), sizeof ( xcb_pixmap_t ) );
        }
        free ( reply );
    }

    return rootpixmap;
}