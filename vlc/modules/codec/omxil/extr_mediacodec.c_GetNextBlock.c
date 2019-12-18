#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ i_csd_send; scalar_t__ i_csd_count; int /*<<< orphan*/ ** pp_csd; } ;
typedef  TYPE_1__ decoder_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */

__attribute__((used)) static block_t *GetNextBlock(decoder_sys_t *p_sys, block_t *p_block)
{
    if (p_sys->i_csd_send < p_sys->i_csd_count)
        return p_sys->pp_csd[p_sys->i_csd_send++];
    else
        return p_block;
}