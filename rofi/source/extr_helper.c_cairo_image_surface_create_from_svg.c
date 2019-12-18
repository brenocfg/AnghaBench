#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_10__ {int /*<<< orphan*/  dpi; } ;
struct TYPE_9__ {int /*<<< orphan*/  message; } ;
struct TYPE_8__ {double height; scalar_t__ width; } ;
typedef  int /*<<< orphan*/  RsvgHandle ;
typedef  TYPE_1__ RsvgDimensionData ;
typedef  TYPE_2__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 scalar_t__ CAIRO_STATUS_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ G_LIKELY (int) ; 
 scalar_t__ G_UNLIKELY (scalar_t__) ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_create (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  cairo_scale (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ cairo_surface_status (int /*<<< orphan*/ *) ; 
 TYPE_7__ config ; 
 int /*<<< orphan*/  g_error_free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/  const*,...) ; 
 int /*<<< orphan*/  rsvg_handle_close (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  rsvg_handle_get_dimensions (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * rsvg_handle_new_from_file (int /*<<< orphan*/  const*,TYPE_2__**) ; 
 scalar_t__ rsvg_handle_render_cairo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsvg_handle_set_dpi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

cairo_surface_t* cairo_image_surface_create_from_svg ( const gchar* file, int height )
{
    GError          *error   = NULL;
    cairo_surface_t *surface = NULL;
    RsvgHandle      * handle;

    handle = rsvg_handle_new_from_file ( file, &error );
    if ( G_LIKELY ( handle != NULL ) ) {
        RsvgDimensionData dimensions;
        // Update DPI.
        rsvg_handle_set_dpi ( handle, config.dpi );
        // Get size.
        rsvg_handle_get_dimensions ( handle, &dimensions );
        // Create cairo surface in the right size.
        double scale = (double) height / dimensions.height;
        surface = cairo_image_surface_create ( CAIRO_FORMAT_ARGB32,
                                               (double) dimensions.width * scale,
                                               (double) dimensions.height * scale );
        gboolean failed = cairo_surface_status ( surface ) != CAIRO_STATUS_SUCCESS;
        if ( G_LIKELY ( failed == FALSE ) ) {
            cairo_t *cr = cairo_create ( surface );
            cairo_scale ( cr, scale, scale );
            failed = rsvg_handle_render_cairo ( handle, cr ) == FALSE;
            cairo_destroy ( cr );
        }

        rsvg_handle_close ( handle, &error );
        g_object_unref ( handle );

        /** Rendering fails */
        if ( G_UNLIKELY ( failed ) ) {
            g_warning ( "Failed to render file: '%s'", file );
            cairo_surface_destroy ( surface );
            surface = NULL;
        }
    }
    if ( G_UNLIKELY ( error != NULL ) ) {
        g_warning ( "Failed to render SVG file: '%s': %s", file, error->message );
        g_error_free ( error );
    }

    return surface;
}