#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vlc_block_callbacks {int dummy; } ;
struct TYPE_4__ {size_t i_buffer; size_t i_size; struct vlc_block_callbacks const* cbs; scalar_t__ i_length; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; scalar_t__ i_nb_samples; scalar_t__ i_flags; void* p_start; void* p_buffer; int /*<<< orphan*/ * p_next; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_INVALID ; 

block_t *block_Init(block_t *restrict b, const struct vlc_block_callbacks *cbs,
                    void *buf, size_t size)
{
    /* Fill all fields to their default */
    b->p_next = NULL;
    b->p_buffer = buf;
    b->i_buffer = size;
    b->p_start = buf;
    b->i_size = size;
    b->i_flags = 0;
    b->i_nb_samples = 0;
    b->i_pts =
    b->i_dts = VLC_TICK_INVALID;
    b->i_length = 0;
    b->cbs = cbs;
    return b;
}