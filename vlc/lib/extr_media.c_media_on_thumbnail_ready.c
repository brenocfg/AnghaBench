#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  libvlc_picture_t ;
struct TYPE_11__ {int /*<<< orphan*/  crop; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  type; TYPE_5__* md; } ;
typedef  TYPE_4__ libvlc_media_thumbnail_request_t ;
struct TYPE_12__ {int /*<<< orphan*/  event_manager; TYPE_1__* p_libvlc_instance; } ;
typedef  TYPE_5__ libvlc_media_t ;
struct TYPE_9__ {int /*<<< orphan*/ * p_thumbnail; } ;
struct TYPE_10__ {TYPE_2__ media_thumbnail_generated; } ;
struct TYPE_13__ {TYPE_3__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_6__ libvlc_event_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_libvlc_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_MediaThumbnailGenerated ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/ * libvlc_picture_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_picture_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void media_on_thumbnail_ready( void* data, picture_t* thumbnail )
{
    libvlc_media_thumbnail_request_t *req = data;
    libvlc_media_t *p_media = req->md;
    libvlc_event_t event;
    event.type = libvlc_MediaThumbnailGenerated;
    libvlc_picture_t* pic = NULL;
    if ( thumbnail != NULL )
        pic = libvlc_picture_new( VLC_OBJECT(p_media->p_libvlc_instance->p_libvlc_int),
                                    thumbnail, req->type, req->width, req->height,
                                    req->crop );
    event.u.media_thumbnail_generated.p_thumbnail = pic;
    libvlc_event_send( &p_media->event_manager, &event );
    if ( pic != NULL )
        libvlc_picture_release( pic );
}