#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_clock_t ;
struct spu_channel {size_t id; float rate; int order; int /*<<< orphan*/  entries; scalar_t__ delay; int /*<<< orphan*/ * clock; } ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_vector_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spu_channel_Init(struct spu_channel *channel, size_t id,
                             enum vlc_vout_order order, vlc_clock_t *clock)
{
    channel->id = id;
    channel->clock = clock;
    channel->delay = 0;
    channel->rate = 1.f;
    channel->order = order;

    vlc_vector_init(&channel->entries);
}