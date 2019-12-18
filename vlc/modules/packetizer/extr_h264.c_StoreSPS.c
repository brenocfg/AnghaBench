#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  h264_sequence_parameter_set_t ;
struct TYPE_5__ {TYPE_1__* sps; int /*<<< orphan*/ * p_active_sps; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_sps; int /*<<< orphan*/ * p_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h264_release_sps (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void StoreSPS( decoder_sys_t *p_sys, uint8_t i_id,
                      block_t *p_block, h264_sequence_parameter_set_t *p_sps )
{
    if( p_sys->sps[i_id].p_block )
        block_Release( p_sys->sps[i_id].p_block );
    if( p_sys->sps[i_id].p_sps )
        h264_release_sps( p_sys->sps[i_id].p_sps );
    if( p_sys->sps[i_id].p_sps == p_sys->p_active_sps )
        p_sys->p_active_sps = NULL;
    p_sys->sps[i_id].p_block = p_block;
    p_sys->sps[i_id].p_sps = p_sps;
}