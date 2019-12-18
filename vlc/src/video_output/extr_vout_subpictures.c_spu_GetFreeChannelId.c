#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_8__ {TYPE_4__* p; } ;
typedef  TYPE_3__ spu_t ;
struct TYPE_7__ {size_t size; TYPE_1__* data; } ;
struct TYPE_9__ {TYPE_2__ channels; } ;
typedef  TYPE_4__ spu_private_t ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;
struct TYPE_6__ {size_t id; } ;

/* Variables and functions */
 size_t SSIZE_MAX ; 
 int VLC_VOUT_ORDER_PRIMARY ; 
 int VLC_VOUT_ORDER_SECONDARY ; 
 size_t VOUT_SPU_CHANNEL_INVALID ; 
 size_t VOUT_SPU_CHANNEL_OSD_COUNT ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t spu_GetFreeChannelId(spu_t *spu, enum vlc_vout_order *order)
{
    spu_private_t *sys = spu->p;

    if (unlikely(sys->channels.size > SSIZE_MAX))
        return VOUT_SPU_CHANNEL_INVALID;

    size_t id;
    if (order)
        *order = VLC_VOUT_ORDER_PRIMARY;
    for (id = VOUT_SPU_CHANNEL_OSD_COUNT; id < sys->channels.size + 1; ++id)
    {
        bool used = false;
        for (size_t i = VOUT_SPU_CHANNEL_OSD_COUNT; i < sys->channels.size; ++i)
        {
            if (sys->channels.data[i].id == id)
            {
                used = true;
                if (order)
                    *order = VLC_VOUT_ORDER_SECONDARY;
                break;
            }
        }
        if (!used)
            return id;
    }
    return VOUT_SPU_CHANNEL_INVALID;
}