#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_14__ {scalar_t__ i_sar_den; scalar_t__ i_sar_num; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_15__ {TYPE_4__* p_region; int /*<<< orphan*/  i_original_picture_height; int /*<<< orphan*/  i_original_picture_width; } ;
typedef  TYPE_2__ subpicture_t ;
struct TYPE_16__ {TYPE_1__ format; } ;
typedef  TYPE_3__ picture_t ;
typedef  int /*<<< orphan*/  image_handler_t ;
struct TYPE_17__ {TYPE_3__* p_picture; } ;

/* Variables and functions */
 TYPE_3__* image_Convert (int /*<<< orphan*/ *,TYPE_3__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * image_HandlerCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  image_HandlerDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (TYPE_3__*) ; 
 TYPE_2__* subpicture_New (int /*<<< orphan*/ *) ; 
 TYPE_4__* subpicture_region_New (TYPE_1__*) ; 

subpicture_t *subpicture_NewFromPicture( vlc_object_t *p_obj,
                                         picture_t *p_picture, vlc_fourcc_t i_chroma )
{
    /* */
    video_format_t fmt_in = p_picture->format;

    /* */
    video_format_t fmt_out;
    fmt_out = fmt_in;
    fmt_out.i_chroma = i_chroma;

    /* */
    image_handler_t *p_image = image_HandlerCreate( p_obj );
    if( !p_image )
        return NULL;

    picture_t *p_pip = image_Convert( p_image, p_picture, &fmt_in, &fmt_out );

    image_HandlerDelete( p_image );

    if( !p_pip )
        return NULL;

    subpicture_t *p_subpic = subpicture_New( NULL );
    if( !p_subpic )
    {
         picture_Release( p_pip );
         return NULL;
    }

    p_subpic->i_original_picture_width  = fmt_out.i_visible_width;
    p_subpic->i_original_picture_height = fmt_out.i_visible_height;

    fmt_out.i_sar_num =
    fmt_out.i_sar_den = 0;

    p_subpic->p_region = subpicture_region_New( &fmt_out );
    if( p_subpic->p_region )
    {
        picture_Release( p_subpic->p_region->p_picture );
        p_subpic->p_region->p_picture = p_pip;
    }
    else
    {
        picture_Release( p_pip );
    }
    return p_subpic;
}