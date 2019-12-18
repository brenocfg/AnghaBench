#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct spu_channel {size_t id; } ;
struct TYPE_6__ {TYPE_3__* p; } ;
typedef  TYPE_2__ spu_t ;
struct TYPE_5__ {size_t size; struct spu_channel* data; } ;
struct TYPE_7__ {TYPE_1__ channels; } ;
typedef  TYPE_3__ spu_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static struct spu_channel *spu_GetChannel(spu_t *spu, size_t channel_id)
{
    spu_private_t *sys = spu->p;

    for (size_t i = 0; i < sys->channels.size; ++i)
        if (sys->channels.data[i].id == channel_id)
            return &sys->channels.data[i];

    vlc_assert_unreachable();
}