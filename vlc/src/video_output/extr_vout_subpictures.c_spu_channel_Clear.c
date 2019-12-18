#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; TYPE_1__* data; } ;
struct spu_channel {TYPE_2__ entries; } ;
typedef  int /*<<< orphan*/  spu_private_t ;
struct TYPE_3__ {int /*<<< orphan*/  subpic; } ;

/* Variables and functions */
 int /*<<< orphan*/  spu_PrerenderCancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_channel_DeleteAt (struct spu_channel*,size_t) ; 

__attribute__((used)) static void spu_channel_Clear(spu_private_t *sys,
                              struct spu_channel *channel)
{
    for (size_t i = 0; i < channel->entries.size; i++)
    {
        spu_PrerenderCancel(sys, channel->entries.data[i].subpic);
        spu_channel_DeleteAt(channel, i);
    }
}