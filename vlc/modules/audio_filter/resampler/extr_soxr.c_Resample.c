#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/ * soxr_t ;
struct TYPE_22__ {scalar_t__ i_rate; } ;
struct TYPE_23__ {TYPE_3__ audio; } ;
struct TYPE_20__ {double i_rate; } ;
struct TYPE_21__ {TYPE_1__ audio; } ;
struct TYPE_24__ {TYPE_4__ fmt_in; TYPE_2__ fmt_out; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_25__ {double const f_fixed_ratio; size_t const i_last_olen; int /*<<< orphan*/ * soxr; int /*<<< orphan*/ * last_soxr; int /*<<< orphan*/ * vr_soxr; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_26__ {unsigned int i_nb_samples; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_7__ block_t ;

/* Variables and functions */
 size_t SoXR_GetOutLen (unsigned int,double const) ; 
 TYPE_7__* SoXR_Resample (TYPE_5__*,int /*<<< orphan*/ *,TYPE_7__*,size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_ChainAppend (TYPE_7__**,TYPE_7__*) ; 
 TYPE_7__* block_ChainGather (TYPE_7__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_7__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soxr_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soxr_set_io_ratio (int /*<<< orphan*/ *,int,size_t const) ; 

__attribute__((used)) static block_t *
Resample( filter_t *p_filter, block_t *p_in )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    const vlc_tick_t i_pts = p_in->i_pts;

    if( p_sys->vr_soxr )
    {
        /* "audio resampler" with variable ratio: use the fixed resampler when
         * the ratio is the same than the fixed one, otherwise use the variable
         * resampler. */

        soxr_t soxr;
        block_t *p_flushed_out = NULL, *p_out = NULL;
        const double f_ratio = p_filter->fmt_out.audio.i_rate
                             / (double) p_filter->fmt_in.audio.i_rate;
        const size_t i_olen = SoXR_GetOutLen( p_in->i_nb_samples, f_ratio );

        if( f_ratio != p_sys->f_fixed_ratio )
        {
            /* using variable resampler */
            soxr_set_io_ratio( p_sys->vr_soxr, 1 / f_ratio, i_olen );
            soxr = p_sys->vr_soxr;
        }
        else if( f_ratio == 1.0f )
        {
            /* not using any resampler */
            soxr = NULL;
            p_out = p_in;
        }
        else
        {
            /* using fixed resampler */
            soxr = p_sys->soxr;
        }

        /* If the new soxr is different than the last one, flush it */
        if( p_sys->last_soxr && soxr != p_sys->last_soxr && p_sys->i_last_olen )
        {
            p_flushed_out = SoXR_Resample( p_filter, p_sys->last_soxr,
                                           NULL, p_sys->i_last_olen );
            if( soxr )
                msg_Dbg( p_filter, "Using '%s' engine", soxr_engine( soxr ) );
        }

        if( soxr )
        {
            assert( !p_out );
            p_out = SoXR_Resample( p_filter, soxr, p_in, i_olen );
            if( !p_out )
                goto error;
        }

        if( p_flushed_out )
        {
            /* Prepend the flushed output data to p_out */
            const unsigned i_nb_samples = p_flushed_out->i_nb_samples
                                        + p_out->i_nb_samples;

            block_ChainAppend( &p_flushed_out, p_out );
            p_out = block_ChainGather( p_flushed_out );
            if( !p_out )
                goto error;
            p_out->i_nb_samples = i_nb_samples;
        }
        p_out->i_pts = i_pts;
        return p_out;
    }
    else
    {
        /* "audio converter" with fixed ratio */

        const size_t i_olen = SoXR_GetOutLen( p_in->i_nb_samples,
                                              p_sys->f_fixed_ratio );
        block_t *p_out = SoXR_Resample( p_filter, p_sys->soxr, p_in, i_olen );
        if( p_out )
            p_out->i_pts = i_pts;
        return p_out;
    }
error:
    block_Release( p_in );
    return NULL;
}