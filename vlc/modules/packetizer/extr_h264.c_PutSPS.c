#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {size_t i_id; } ;
typedef  TYPE_2__ h264_sequence_parameter_set_t ;
struct TYPE_17__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_18__ {TYPE_1__* sps; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_19__ {size_t i_buffer; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_15__ {int /*<<< orphan*/  p_sps; } ;

/* Variables and functions */
 int /*<<< orphan*/  StoreSPS (TYPE_4__*,size_t,TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_5__*) ; 
 TYPE_2__* h264_decode_sps (int /*<<< orphan*/  const*,size_t,int) ; 
 int /*<<< orphan*/  hxxx_strip_AnnexB_startcode (int /*<<< orphan*/  const**,size_t*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,size_t) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 

__attribute__((used)) static void PutSPS( decoder_t *p_dec, block_t *p_frag )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    const uint8_t *p_buffer = p_frag->p_buffer;
    size_t i_buffer = p_frag->i_buffer;

    if( !hxxx_strip_AnnexB_startcode( &p_buffer, &i_buffer ) )
    {
        block_Release( p_frag );
        return;
    }

    h264_sequence_parameter_set_t *p_sps = h264_decode_sps( p_buffer, i_buffer, true );
    if( !p_sps )
    {
        msg_Warn( p_dec, "invalid SPS" );
        block_Release( p_frag );
        return;
    }

    /* We have a new SPS */
    if( !p_sys->sps[p_sps->i_id].p_sps )
        msg_Dbg( p_dec, "found NAL_SPS (sps_id=%d)", p_sps->i_id );

    StoreSPS( p_sys, p_sps->i_id, p_frag, p_sps );
}