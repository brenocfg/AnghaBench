#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_8__ {int /*<<< orphan*/  date; } ;
typedef  TYPE_1__ picture_t ;
typedef  int libvlc_picture_type_t ;
struct TYPE_9__ {int type; int /*<<< orphan*/  fmt; int /*<<< orphan*/  converted; int /*<<< orphan*/  time; int /*<<< orphan*/  rc; } ;
typedef  TYPE_2__ libvlc_picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  MS_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_CODEC_ARGB ; 
 int /*<<< orphan*/  VLC_CODEC_JPEG ; 
 int /*<<< orphan*/  VLC_CODEC_PNG ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
#define  libvlc_picture_Argb 130 
#define  libvlc_picture_Jpg 129 
#define  libvlc_picture_Png 128 
 TYPE_2__* malloc (int) ; 
 scalar_t__ picture_Export (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 

libvlc_picture_t* libvlc_picture_new( vlc_object_t* p_obj, picture_t* input,
                                      libvlc_picture_type_t type,
                                      unsigned int width, unsigned int height,
                                      bool crop )
{
    libvlc_picture_t *pic = malloc( sizeof( *pic ) );
    if ( unlikely( pic == NULL ) )
        return NULL;
    vlc_atomic_rc_init( &pic->rc );
    pic->type = type;
    pic->time = MS_FROM_VLC_TICK( input->date );
    vlc_fourcc_t format;
    switch ( type )
    {
        case libvlc_picture_Argb:
            format = VLC_CODEC_ARGB;
            break;
        case libvlc_picture_Jpg:
            format = VLC_CODEC_JPEG;
            break;
        case libvlc_picture_Png:
            format = VLC_CODEC_PNG;
            break;
        default:
            vlc_assert_unreachable();
    }
    if ( picture_Export( p_obj, &pic->converted, &pic->fmt,
                         input, format, width, height, crop ) != VLC_SUCCESS )
    {
        free( pic );
        return NULL;
    }

    return pic;
}