#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_12__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_13__ {TYPE_1__* p_root; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_14__ {int i_flags; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; scalar_t__ i_length; scalar_t__ i_pts; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_child; } ;

/* Variables and functions */
 int BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  ClearCuesByTime (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Flush (TYPE_2__*) ; 
 int /*<<< orphan*/  ProcessISOBMFF (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Render (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int VLCDEC_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 

__attribute__((used)) static int DecodeBlock( decoder_t *p_dec, block_t *p_block )
{
    if( p_block == NULL ) /* No Drain */
        return VLCDEC_SUCCESS;

    decoder_sys_t *p_sys = p_dec->p_sys;

    vlc_tick_t i_start = p_block->i_pts - VLC_TICK_0;
    vlc_tick_t i_stop = i_start + p_block->i_length;

    if( p_block->i_flags & BLOCK_FLAG_DISCONTINUITY )
        Flush( p_dec );
    else
        ClearCuesByTime( &p_sys->p_root->p_child, i_start );

    ProcessISOBMFF( p_dec, p_block->p_buffer, p_block->i_buffer,
                    i_start, i_stop );

    Render( p_dec, i_start, i_stop );

    block_Release( p_block );
    return VLCDEC_SUCCESS;
}