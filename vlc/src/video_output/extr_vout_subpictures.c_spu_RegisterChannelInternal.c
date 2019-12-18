#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_clock_t ;
struct spu_channel {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {TYPE_2__* p; } ;
typedef  TYPE_1__ spu_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  channels; } ;
typedef  TYPE_2__ spu_private_t ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;

/* Variables and functions */
 int VLC_VOUT_ORDER_PRIMARY ; 
 scalar_t__ VOUT_SPU_CHANNEL_INVALID ; 
 scalar_t__ spu_GetFreeChannelId (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  spu_channel_Init (struct spu_channel*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_vector_push (int /*<<< orphan*/ *,struct spu_channel) ; 

ssize_t spu_RegisterChannelInternal(spu_t *spu, vlc_clock_t *clock,
                                    enum vlc_vout_order *order)
{
    spu_private_t *sys = spu->p;

    vlc_mutex_lock(&sys->lock);

    ssize_t channel_id = spu_GetFreeChannelId(spu, order);

    if (channel_id != VOUT_SPU_CHANNEL_INVALID)
    {
        struct spu_channel channel;
        spu_channel_Init(&channel, channel_id,
                         order ? *order : VLC_VOUT_ORDER_PRIMARY, clock);
        if (vlc_vector_push(&sys->channels, channel))
        {
            vlc_mutex_unlock(&sys->lock);
            return channel_id;
        }
    }

    vlc_mutex_unlock(&sys->lock);

    return VOUT_SPU_CHANNEL_INVALID;
}