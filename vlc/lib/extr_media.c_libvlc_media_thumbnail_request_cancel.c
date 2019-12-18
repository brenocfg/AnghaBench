#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * p_thumbnailer; } ;
typedef  TYPE_3__ libvlc_priv_t ;
struct TYPE_10__ {int /*<<< orphan*/  req; TYPE_2__* md; } ;
typedef  TYPE_4__ libvlc_media_thumbnail_request_t ;
struct TYPE_8__ {TYPE_1__* p_libvlc_instance; } ;
struct TYPE_7__ {int /*<<< orphan*/  p_libvlc_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* libvlc_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_thumbnailer_Cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void libvlc_media_thumbnail_request_cancel( libvlc_media_thumbnail_request_t *req )
{
    libvlc_priv_t *p_priv = libvlc_priv(req->md->p_libvlc_instance->p_libvlc_int);
    assert( p_priv->p_thumbnailer != NULL );
    vlc_thumbnailer_Cancel( p_priv->p_thumbnailer, req->req );
}