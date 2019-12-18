#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ type; int /*<<< orphan*/  opaque; } ;
typedef  TYPE_2__ vlc_decoder_device ;
struct TYPE_11__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_13__ {scalar_t__ p_sys; TYPE_1__ format; } ;
typedef  TYPE_3__ picture_t ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  VADisplay ;
struct TYPE_14__ {int /*<<< orphan*/  lock; TYPE_2__* dec_device; int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 scalar_t__ VLC_DECODER_DEVICE_VAAPI ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* filter_NewPicture (int /*<<< orphan*/ *) ; 
 TYPE_9__ holder ; 
 int /*<<< orphan*/  picture_Release (TYPE_3__*) ; 
 TYPE_2__* vlc_decoder_device_Hold (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vaapi_IsChromaOpaque (int /*<<< orphan*/ ) ; 
 TYPE_2__* vlc_vaapi_PicSysHoldInstance (scalar_t__,int /*<<< orphan*/ *) ; 

vlc_decoder_device *
vlc_vaapi_FilterHoldInstance(filter_t *filter, VADisplay *dpy)
{

    picture_t *pic = filter_NewPicture(filter);
    if (!pic)
        return NULL;

    if (!vlc_vaapi_IsChromaOpaque(pic->format.i_chroma))
    {
        picture_Release(pic);
        return NULL;
    }

    vlc_decoder_device *dec_device = NULL;

    vlc_mutex_lock(&holder.lock);
    if (holder.dec_device != NULL)
    {
        dec_device = vlc_decoder_device_Hold(holder.dec_device);
        *dpy = dec_device->opaque;
    }
    else
    {
        holder.owner = filter;
        holder.dec_device = dec_device = pic->p_sys ?
            vlc_vaapi_PicSysHoldInstance(pic->p_sys, dpy) : NULL;
        assert(dec_device == NULL || dec_device->type == VLC_DECODER_DEVICE_VAAPI);
    }
    vlc_mutex_unlock(&holder.lock);
    picture_Release(pic);

    return dec_device;
}