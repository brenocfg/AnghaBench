#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_visualtype_t ;
struct TYPE_7__ {scalar_t__ map_state; double width; double height; int /*<<< orphan*/  visual; } ;
typedef  TYPE_1__ xcb_get_window_attributes_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_window_attributes_cookie_t ;
typedef  TYPE_1__ xcb_get_geometry_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_geometry_cookie_t ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_8__ {int /*<<< orphan*/  connection; int /*<<< orphan*/  screen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 scalar_t__ CAIRO_STATUS_SUCCESS ; 
 int MAX (double,double) ; 
 scalar_t__ XCB_MAP_STATE_VIEWABLE ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_scale (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cairo_surface_create_similar_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ cairo_surface_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_xcb_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * lookup_visual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* xcb ; 
 int /*<<< orphan*/  xcb_get_geometry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_get_geometry_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_window_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_get_window_attributes_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

cairo_surface_t *x11_helper_get_screenshot_surface_window ( xcb_window_t window, int size )
{
    xcb_get_geometry_cookie_t cookie;
    xcb_get_geometry_reply_t *reply;

    cookie = xcb_get_geometry(xcb->connection, window);
    reply = xcb_get_geometry_reply(xcb->connection, cookie, NULL);
    if ( reply == NULL ) {
        return NULL;
    }

    xcb_get_window_attributes_cookie_t  attributesCookie = xcb_get_window_attributes (xcb->connection, window);
    xcb_get_window_attributes_reply_t  *attributes       = xcb_get_window_attributes_reply (xcb->connection,
            attributesCookie,
            NULL );
    if ( attributes == NULL ||  ( attributes->map_state != XCB_MAP_STATE_VIEWABLE ) ) {
        free(reply);
        if ( attributes ) free(attributes);
        return NULL;
    }
    // Create a cairo surface for the window.
    xcb_visualtype_t * vt = lookup_visual(xcb->screen, attributes->visual);
    free ( attributes );

    cairo_surface_t *t = cairo_xcb_surface_create ( xcb->connection, window, vt , reply->width, reply->height );

    if ( cairo_surface_status ( t ) != CAIRO_STATUS_SUCCESS ) {
        cairo_surface_destroy(t);
        free(reply);
        return NULL;
    }

    // Scale the image, as we don't want to keep large one around.
    int max = MAX(reply->width, reply->height);
    double scale = (double)size/ max;

    cairo_surface_t *s2 = cairo_surface_create_similar_image ( t, CAIRO_FORMAT_ARGB32, reply->width*scale,reply->height*scale );
    free ( reply );

    if ( cairo_surface_status ( s2 ) != CAIRO_STATUS_SUCCESS ) {
        cairo_surface_destroy ( t ) ;
        return NULL;
    }
    // Paint it in.
    cairo_t *d = cairo_create (s2);
    cairo_scale ( d, scale, scale );
    cairo_set_source_surface ( d, t, 0, 0 );
    cairo_paint ( d);
    cairo_destroy(d);

    cairo_surface_destroy(t);
    return s2;
}