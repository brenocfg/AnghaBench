#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ strmtyp; } ;
struct TYPE_18__ {TYPE_1__ eac3; } ;
struct TYPE_21__ {size_t const i_size; scalar_t__ i_blocks_per_sync_frame; TYPE_2__ bs; int /*<<< orphan*/  b_eac3; } ;
typedef  TYPE_5__ vlc_a52_header_t ;
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_22__ {TYPE_7__* p_sys; } ;
typedef  TYPE_6__ filter_t ;
struct TYPE_20__ {int i_nb_blocks; } ;
struct TYPE_23__ {scalar_t__ i_out_offset; TYPE_4__ eac3; TYPE_3__* p_out_buf; } ;
typedef  TYPE_7__ filter_sys_t ;
struct TYPE_24__ {size_t const i_buffer; int /*<<< orphan*/  const* p_buffer; } ;
typedef  TYPE_8__ block_t ;
struct TYPE_19__ {scalar_t__ i_buffer; } ;

/* Variables and functions */
 int AOUT_SPDIF_SIZE ; 
 scalar_t__ EAC3_STRMTYP_DEPENDENT ; 
 int /*<<< orphan*/  IEC61937_EAC3 ; 
 int SPDIF_ERROR ; 
 int SPDIF_MORE_DATA ; 
 int SPDIF_SUCCESS ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ vlc_a52_header_Parse (TYPE_5__*,int /*<<< orphan*/  const*,size_t const) ; 
 int /*<<< orphan*/  write_buffer (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  write_finalize (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ write_init (TYPE_6__*,TYPE_8__*,int,int) ; 

__attribute__((used)) static int write_buffer_eac3( filter_t *p_filter, block_t *p_in_buf )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    /* The input block can contain the following:
     * a/ One EAC3 independent stream (with 1, 2, 3 or 6 audio blocks per
     * syncframe)
     * b/ One AC3 stream followed by one EAC3 dependent stream (with 6 audio
     * blocks per syncframe)
     * c/ One EAC3 independent stream followed by one EAC3 dependent stream
     * (with 1, 2, 3 or 6 audio blocks per syncframe)
     *
     * One IEC61937_EAC3 frame must contain 6 audio blocks per syncframe. This
     * function will gather input blocks until it reaches this amount of audio
     * blocks.
     *
     * Example: for the c/ case with 1 audio blocks per syncframe, a
     * IEC61937_EAC3 frame will contain 12 a52 streams: 6 independent + 6
     * dependent EAC3 streams.
     */

    vlc_a52_header_t a52;
    if( vlc_a52_header_Parse( &a52, p_in_buf->p_buffer, p_in_buf->i_buffer )
        != VLC_SUCCESS || a52.i_size > p_in_buf->i_buffer )
        return SPDIF_ERROR;

    if( p_in_buf->i_buffer > a52.i_size )
    {
        /* Check if the next stream is an eac3 dependent one */
        vlc_a52_header_t a52_dep;
        const uint8_t *dep_buf = &p_in_buf->p_buffer[a52.i_size];
        const size_t dep_size = p_in_buf->i_buffer - a52.i_size;

        if( vlc_a52_header_Parse( &a52_dep, dep_buf, dep_size ) != VLC_SUCCESS
         || a52_dep.i_size > dep_size
         || !a52_dep.b_eac3 || a52_dep.bs.eac3.strmtyp != EAC3_STRMTYP_DEPENDENT
         || p_in_buf->i_buffer > a52.i_size + a52_dep.i_size )
            return SPDIF_ERROR;
    }

    if( !p_sys->p_out_buf
     && write_init( p_filter, p_in_buf, AOUT_SPDIF_SIZE * 4, AOUT_SPDIF_SIZE ) )
        return SPDIF_ERROR;
    if( p_in_buf->i_buffer > p_sys->p_out_buf->i_buffer - p_sys->i_out_offset )
        return SPDIF_ERROR;

    write_buffer( p_filter, p_in_buf );

    /* cf. Annex E 2.3 of AC3 spec */
    p_sys->eac3.i_nb_blocks += a52.i_blocks_per_sync_frame;

    if( p_sys->eac3.i_nb_blocks < 6 )
        return SPDIF_MORE_DATA;
    else if ( p_sys->eac3.i_nb_blocks > 6 )
        return SPDIF_ERROR;

    write_finalize( p_filter, IEC61937_EAC3, 1 /* in bytes */ );
    p_sys->eac3.i_nb_blocks = 0;
    return SPDIF_SUCCESS;
}