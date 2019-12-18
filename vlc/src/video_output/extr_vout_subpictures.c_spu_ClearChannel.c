#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spu_channel {int /*<<< orphan*/  delay; scalar_t__ clock; } ;
struct TYPE_6__ {TYPE_2__* p; } ;
typedef  TYPE_1__ spu_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ spu_private_t ;

/* Variables and functions */
 struct spu_channel* spu_GetChannel (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  spu_channel_Clear (TYPE_2__*,struct spu_channel*) ; 
 int /*<<< orphan*/  vlc_clock_Reset (scalar_t__) ; 
 int /*<<< orphan*/  vlc_clock_SetDelay (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void spu_ClearChannel(spu_t *spu, size_t channel_id)
{
    spu_private_t *sys = spu->p;
    vlc_mutex_lock(&sys->lock);
    struct spu_channel *channel = spu_GetChannel(spu, channel_id);
    spu_channel_Clear(sys, channel);
    if (channel->clock)
    {
        vlc_clock_Reset(channel->clock);
        vlc_clock_SetDelay(channel->clock, channel->delay);
    }
    vlc_mutex_unlock(&sys->lock);
}