#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;
struct TYPE_7__ {scalar_t__ p_head; scalar_t__ p_tail; } ;
typedef  TYPE_1__ hxxx_iterator_ctx_t ;
struct TYPE_8__ {size_t i_buffer; scalar_t__ i_pts; scalar_t__ i_dts; size_t i_length; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 scalar_t__ hxxx_annexb_iterate_next (TYPE_1__*,int /*<<< orphan*/  const**,size_t*) ; 
 int /*<<< orphan*/  hxxx_iterator_init (TYPE_1__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_packetize_h265_nal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,scalar_t__,scalar_t__,int,size_t) ; 

__attribute__((used)) static int rtp_packetize_h265( sout_stream_id_sys_t *id, block_t *in )
{
    hxxx_iterator_ctx_t it;
    hxxx_iterator_init( &it, in->p_buffer, in->i_buffer, 0 );

    const uint8_t *p_nal;
    size_t i_nal;
    while( hxxx_annexb_iterate_next( &it, &p_nal, &i_nal ) )
    {
        rtp_packetize_h265_nal( id, p_nal, i_nal,
                (in->i_pts != VLC_TICK_INVALID ? in->i_pts : in->i_dts), in->i_dts,
                it.p_head + 3 >= it.p_tail, in->i_length * i_nal / in->i_buffer );
    }

    block_Release(in);
    return VLC_SUCCESS;
}