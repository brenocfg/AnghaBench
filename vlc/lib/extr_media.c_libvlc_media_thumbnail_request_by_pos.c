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
typedef  scalar_t__ libvlc_time_t ;
typedef  scalar_t__ libvlc_thumbnailer_seek_speed_t ;
struct TYPE_15__ {int /*<<< orphan*/ * p_thumbnailer; } ;
typedef  TYPE_2__ libvlc_priv_t ;
typedef  int /*<<< orphan*/  libvlc_picture_type_t ;
struct TYPE_16__ {unsigned int width; unsigned int height; int crop; int /*<<< orphan*/ * req; int /*<<< orphan*/  type; TYPE_4__* md; } ;
typedef  TYPE_3__ libvlc_media_thumbnail_request_t ;
struct TYPE_17__ {int /*<<< orphan*/  p_input_item; TYPE_1__* p_libvlc_instance; } ;
typedef  TYPE_4__ libvlc_media_t ;
struct TYPE_14__ {int /*<<< orphan*/  p_libvlc_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_THUMBNAILER_SEEK_FAST ; 
 int /*<<< orphan*/  VLC_THUMBNAILER_SEEK_PRECISE ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (scalar_t__) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  libvlc_media_release (TYPE_4__*) ; 
 int /*<<< orphan*/  libvlc_media_retain (TYPE_4__*) ; 
 scalar_t__ libvlc_media_thumbnail_seek_fast ; 
 TYPE_2__* libvlc_priv (int /*<<< orphan*/ ) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  media_on_thumbnail_ready ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_thumbnailer_RequestByPos (int /*<<< orphan*/ *,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

libvlc_media_thumbnail_request_t*
libvlc_media_thumbnail_request_by_pos( libvlc_media_t *md, float pos,
                                       libvlc_thumbnailer_seek_speed_t speed,
                                       unsigned int width, unsigned int height,
                                       bool crop, libvlc_picture_type_t picture_type,
                                       libvlc_time_t timeout )
{
    assert( md );
    libvlc_priv_t *priv = libvlc_priv(md->p_libvlc_instance->p_libvlc_int);
    if( unlikely( priv->p_thumbnailer == NULL ) )
        return NULL;
    libvlc_media_thumbnail_request_t *req = malloc( sizeof( *req ) );
    if ( unlikely( req == NULL ) )
        return NULL;

    req->md = md;
    req->width = width;
    req->height = height;
    req->crop = crop;
    req->type = picture_type;
    libvlc_media_retain( md );
    req->req = vlc_thumbnailer_RequestByPos( priv->p_thumbnailer, pos,
        speed == libvlc_media_thumbnail_seek_fast ?
            VLC_THUMBNAILER_SEEK_FAST : VLC_THUMBNAILER_SEEK_PRECISE,
        md->p_input_item,
        timeout > 0 ? VLC_TICK_FROM_MS( timeout ) : VLC_TICK_INVALID,
        media_on_thumbnail_ready, req );
    if ( req->req == NULL )
    {
        free( req );
        libvlc_media_release( md );
        return NULL;
    }
    return req;
}