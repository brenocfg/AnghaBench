#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int i_bits_per_pixel; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_2__ video_format_t ;
struct TYPE_16__ {TYPE_1__* p; } ;
typedef  TYPE_3__ picture_t ;
typedef  int /*<<< orphan*/  guint8 ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_18__ {int /*<<< orphan*/  message; } ;
struct TYPE_17__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {int i_pitch; int i_lines; int /*<<< orphan*/  p_pixels; } ;
typedef  int /*<<< orphan*/  RsvgHandle ;
typedef  TYPE_4__ RsvgDimensionData ;
typedef  TYPE_5__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_CODEC_BGRA ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_create_for_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_3__* picture_NewFromFormat (TYPE_2__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  rsvg_handle_get_dimensions (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * rsvg_handle_new_from_data (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  rsvg_handle_render_cairo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svg_RescaletoFit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  video_format_Clean (TYPE_2__*) ; 
 int /*<<< orphan*/  video_format_Init (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_t * svg_RenderPicture( filter_t *p_filter,
                                      const char *psz_svgdata )
{
    RsvgHandle *p_handle;
    GError *error = NULL;

    p_handle = rsvg_handle_new_from_data( (const guint8 *)psz_svgdata,
                                          strlen( psz_svgdata ), &error );
    if( !p_handle )
    {
        msg_Err( p_filter, "error while rendering SVG: %s", error->message );
        return NULL;
    }

    RsvgDimensionData dim;
    rsvg_handle_get_dimensions( p_handle, &dim );
    float scale;
    svg_RescaletoFit( p_filter, &dim.width, &dim.height, &scale );

    /* Create a new subpicture region */
    video_format_t fmt;
    video_format_Init( &fmt, VLC_CODEC_BGRA ); /* CAIRO_FORMAT_ARGB32 == VLC_CODEC_BGRA, go figure */
    fmt.i_bits_per_pixel = 32;
    fmt.i_chroma = VLC_CODEC_BGRA;
    fmt.i_width = fmt.i_visible_width = dim.width;
    fmt.i_height = fmt.i_visible_height = dim.height;

    picture_t *p_picture = picture_NewFromFormat( &fmt );
    if( !p_picture )
    {
        video_format_Clean( &fmt );
        g_object_unref( G_OBJECT( p_handle ) );
        return NULL;
    }
    memset( p_picture->p[0].p_pixels, 0x00, p_picture->p[0].i_pitch * p_picture->p[0].i_lines );

    cairo_surface_t* surface = cairo_image_surface_create_for_data( p_picture->p->p_pixels,
                                                                    CAIRO_FORMAT_ARGB32,
                                                                    fmt.i_width, fmt.i_height,
                                                                    p_picture->p[0].i_pitch );
    if( !surface )
    {
        g_object_unref( G_OBJECT( p_handle ) );
        picture_Release( p_picture );
        return NULL;
    }

    cairo_t *cr = cairo_create( surface );
    if( !cr )
    {
        msg_Err( p_filter, "error while creating cairo surface" );
        cairo_surface_destroy( surface );
        g_object_unref( G_OBJECT( p_handle ) );
        picture_Release( p_picture );
        return NULL;
    }

    if( ! rsvg_handle_render_cairo( p_handle, cr ) )
    {
        msg_Err( p_filter, "error while rendering SVG" );
        cairo_destroy( cr );
        cairo_surface_destroy( surface );
        g_object_unref( G_OBJECT( p_handle ) );
        picture_Release( p_picture );
        return NULL;
    }

    cairo_destroy( cr );
    cairo_surface_destroy( surface );
    g_object_unref( G_OBJECT( p_handle ) );

    return p_picture;
}