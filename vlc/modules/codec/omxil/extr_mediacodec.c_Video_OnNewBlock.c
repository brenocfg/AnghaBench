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
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_7__ {int /*<<< orphan*/  timestamp_fifo; } ;
struct TYPE_9__ {TYPE_1__ video; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_dts; scalar_t__ i_pts; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  timestamp_FifoPut (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Video_OnNewBlock(decoder_t *p_dec, block_t **pp_block)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t *p_block = *pp_block;

    timestamp_FifoPut(p_sys->video.timestamp_fifo,
                      p_block->i_pts ? VLC_TICK_INVALID : p_block->i_dts);

    return 1;
}