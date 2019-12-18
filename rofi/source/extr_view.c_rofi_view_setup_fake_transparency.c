#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_4__ {TYPE_1__ mon; scalar_t__ fake_bgrel; int /*<<< orphan*/ * fake_bg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 scalar_t__ CAIRO_STATUS_SUCCESS ; 
 TYPE_2__ CacheState ; 
 int /*<<< orphan*/  TICK_N (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cairo_image_surface_create_from_png (char*) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* cairo_status_to_string (scalar_t__) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ cairo_surface_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*,char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_strcmp0 (char const* const,char*) ; 
 char* rofi_expand_path (char const* const) ; 
 int /*<<< orphan*/ * x11_helper_get_bg_surface () ; 
 int /*<<< orphan*/ * x11_helper_get_screenshot_surface () ; 

__attribute__((used)) static void rofi_view_setup_fake_transparency ( const char* const fake_background )
{
    if ( CacheState.fake_bg == NULL ) {
        cairo_surface_t *s = NULL;
        /**
         * Select Background to use for fake transparency.
         * Current options: 'real', 'screenshot','background'
         */
        TICK_N ( "Fake start" );
        if ( g_strcmp0 ( fake_background, "real" ) == 0 ) {
            return;
        }
        else if ( g_strcmp0 ( fake_background, "screenshot" ) == 0 ) {
            s = x11_helper_get_screenshot_surface ();
        }
        else if ( g_strcmp0 ( fake_background, "background" ) == 0 ) {
            s = x11_helper_get_bg_surface ();
        }
        else {
            char *fpath = rofi_expand_path ( fake_background );
            g_debug ( "Opening %s to use as background.", fpath );
            s                     = cairo_image_surface_create_from_png ( fpath );
            CacheState.fake_bgrel = TRUE;
            g_free ( fpath );
        }
        TICK_N ( "Get surface." );
        if ( s != NULL ) {
            if ( cairo_surface_status ( s ) != CAIRO_STATUS_SUCCESS ) {
                g_debug ( "Failed to open surface fake background: %s",
                          cairo_status_to_string ( cairo_surface_status ( s ) ) );
                cairo_surface_destroy ( s );
                s = NULL;
            }
            else {
                CacheState.fake_bg = cairo_image_surface_create ( CAIRO_FORMAT_ARGB32, CacheState.mon.w, CacheState.mon.h );
                cairo_t *dr = cairo_create ( CacheState.fake_bg );
                if ( CacheState.fake_bgrel ) {
                    cairo_set_source_surface ( dr, s, 0, 0 );
                }
                else {
                    cairo_set_source_surface ( dr, s, -CacheState.mon.x, -CacheState.mon.y );
                }
                cairo_paint ( dr );
                cairo_destroy ( dr );
                cairo_surface_destroy ( s );
            }
        }
        TICK_N ( "Fake transparency" );
    }
}