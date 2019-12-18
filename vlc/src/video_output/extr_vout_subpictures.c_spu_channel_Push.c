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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_stop; int /*<<< orphan*/  i_start; } ;
typedef  TYPE_1__ subpicture_t ;
struct spu_channel {int /*<<< orphan*/  entries; } ;
struct TYPE_6__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  orgstop; int /*<<< orphan*/  orgstart; TYPE_1__* subpic; } ;
typedef  TYPE_2__ spu_render_entry_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ vlc_vector_push (int /*<<< orphan*/ *,TYPE_2__ const) ; 

__attribute__((used)) static int spu_channel_Push(struct spu_channel *channel, subpicture_t *subpic,
                            vlc_tick_t orgstart, vlc_tick_t orgstop)
{
    const spu_render_entry_t entry = {
        .subpic = subpic,
        .orgstart = orgstart,
        .orgstop = orgstop,
        .start = subpic->i_start,
        .stop = subpic->i_stop,
    };
    return vlc_vector_push(&channel->entries, entry) ? VLC_SUCCESS : VLC_EGENERIC;
}