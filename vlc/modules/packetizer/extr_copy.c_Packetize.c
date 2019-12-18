#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ i_codec; } ;
struct TYPE_13__ {TYPE_1__ fmt_in; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* pf_parse ) (TYPE_2__*,TYPE_4__*) ;TYPE_4__* p_block; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_15__ {int i_flags; scalar_t__ i_dts; scalar_t__ i_pts; scalar_t__ i_length; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 scalar_t__ VLC_CODEC_OPUS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_4__*) ; 

__attribute__((used)) static block_t *Packetize ( decoder_t *p_dec, block_t **pp_block )
{
    block_t *p_block;
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t *p_ret = p_sys->p_block;

    if( pp_block == NULL || *pp_block == NULL )
        return NULL;
    if( (*pp_block)->i_flags&(BLOCK_FLAG_CORRUPTED) )
    {
        block_Release( *pp_block );
        return NULL;
    }

    p_block = *pp_block;
    *pp_block = NULL;

    if( p_block->i_dts == VLC_TICK_INVALID )
    {
        p_block->i_dts = p_block->i_pts;
    }

    if( p_block->i_dts == VLC_TICK_INVALID )
    {
        msg_Dbg( p_dec, "need valid dts" );
        block_Release( p_block );
        return NULL;
    }

    if( p_ret != NULL && p_block->i_pts > p_ret->i_pts )
    {
        if (p_dec->fmt_in.i_codec != VLC_CODEC_OPUS)
            p_ret->i_length = p_block->i_pts - p_ret->i_pts;
    }
    p_sys->p_block = p_block;

    if( p_ret && p_sys->pf_parse )
        p_sys->pf_parse( p_dec, p_ret );
    return p_ret;
}