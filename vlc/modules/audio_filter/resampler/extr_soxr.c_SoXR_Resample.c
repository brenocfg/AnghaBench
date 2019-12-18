#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * soxr_t ;
typedef  scalar_t__ soxr_error_t ;
struct TYPE_12__ {size_t i_bytes_per_frame; int /*<<< orphan*/  i_rate; } ;
struct TYPE_13__ {TYPE_1__ audio; } ;
struct TYPE_14__ {TYPE_2__ fmt_out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_15__ {size_t i_last_olen; int /*<<< orphan*/ * last_soxr; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_16__ {size_t i_nb_samples; size_t i_buffer; int /*<<< orphan*/  i_length; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 TYPE_5__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  block_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,size_t const,...) ; 
 int /*<<< orphan*/  soxr_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ soxr_process (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const,size_t*,int /*<<< orphan*/ *,size_t,size_t*) ; 
 int /*<<< orphan*/  soxr_strerror (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_tick_from_samples (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *
SoXR_Resample( filter_t *p_filter, soxr_t soxr, block_t *p_in, size_t i_olen )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    size_t i_idone, i_odone;
    const size_t i_oframesize = p_filter->fmt_out.audio.i_bytes_per_frame;
    const size_t i_ilen = p_in ? p_in->i_nb_samples : 0;

    block_t *p_out;
    if( i_ilen >= i_olen )
    {
        i_olen = i_ilen;
        p_out = p_in;
    }
    else
        p_out = block_Alloc( i_olen * i_oframesize );

    soxr_error_t error = soxr_process( soxr, p_in ? p_in->p_buffer : NULL,
                                       i_ilen, &i_idone, p_out->p_buffer,
                                       i_olen, &i_odone );
    if( error )
    {
        msg_Err( p_filter, "soxr_process failed: %s", soxr_strerror( error ) );
        block_Release( p_out );
        goto error;
    }
    if( unlikely( i_idone < i_ilen ) )
        msg_Err( p_filter, "lost %zd of %zd input frames",
                 i_ilen - i_idone, i_idone);

    p_out->i_buffer = i_odone * i_oframesize;
    p_out->i_nb_samples = i_odone;
    p_out->i_length = vlc_tick_from_samples(i_odone, p_filter->fmt_out.audio.i_rate);

    if( p_in )
    {
        p_sys->i_last_olen = i_olen;
        p_sys->last_soxr = soxr;
    }
    else
    {
        soxr_clear( soxr );
        p_sys->i_last_olen = 0;
        p_sys->last_soxr = NULL;
    }

error:
    if( p_in && p_out != p_in )
        block_Release( p_in );

    return p_out;
}