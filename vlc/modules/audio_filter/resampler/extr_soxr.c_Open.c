#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  soxr_quality_spec_t ;
typedef  int /*<<< orphan*/  soxr_io_spec_t ;
typedef  scalar_t__ soxr_error_t ;
typedef  int /*<<< orphan*/  soxr_datatype_t ;
typedef  size_t int64_t ;
struct TYPE_13__ {unsigned int i_channels; double i_rate; int /*<<< orphan*/  i_format; } ;
struct TYPE_14__ {TYPE_3__ audio; } ;
struct TYPE_11__ {unsigned int i_channels; scalar_t__ i_rate; int /*<<< orphan*/  i_format; } ;
struct TYPE_12__ {TYPE_1__ audio; } ;
struct TYPE_15__ {int /*<<< orphan*/  pf_audio_drain; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_audio_filter; TYPE_6__* p_sys; TYPE_4__ fmt_out; TYPE_2__ fmt_in; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_16__ {double f_fixed_ratio; void* soxr; void* vr_soxr; } ;
typedef  TYPE_6__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Drain ; 
 int /*<<< orphan*/  Flush ; 
 size_t MAX_SOXR_QUALITY ; 
 int /*<<< orphan*/  Resample ; 
 unsigned long const SOXR_LQ ; 
 int /*<<< orphan*/  SOXR_VR ; 
 int /*<<< orphan*/  SoXR_GetFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_6__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__,char const*,double) ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 void* soxr_create (int,double const,unsigned int const,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soxr_delete (void*) ; 
 int /*<<< orphan*/  soxr_engine (void*) ; 
 int /*<<< orphan*/  soxr_io_spec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soxr_quality_spec (unsigned long const,int /*<<< orphan*/ ) ; 
 unsigned long* soxr_resampler_quality_list ; 
 int /*<<< orphan*/ * soxr_resampler_quality_vlctext ; 
 int /*<<< orphan*/  soxr_set_io_ratio (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soxr_strerror (scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 size_t var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
Open( vlc_object_t *p_obj, bool b_change_ratio )
{
    filter_t *p_filter = (filter_t *)p_obj;

    /* Cannot remix */
    if( p_filter->fmt_in.audio.i_channels != p_filter->fmt_out.audio.i_channels )
        return VLC_EGENERIC;

    /* Get SoXR input/output format */
    soxr_datatype_t i_itype, i_otype;
    if( !SoXR_GetFormat( p_filter->fmt_in.audio.i_format, &i_itype )
     || !SoXR_GetFormat( p_filter->fmt_out.audio.i_format, &i_otype ) )
        return VLC_EGENERIC;

    filter_sys_t *p_sys = calloc( 1, sizeof( filter_sys_t ) );
    if( unlikely( p_sys == NULL ) )
        return VLC_ENOMEM;

    /* Setup SoXR */
    int64_t i_vlc_q = var_InheritInteger( p_obj, "soxr-resampler-quality" );
    if( i_vlc_q < 0 )
        i_vlc_q = 0;
    else if( i_vlc_q > MAX_SOXR_QUALITY )
        i_vlc_q = MAX_SOXR_QUALITY;
    const unsigned long i_recipe = soxr_resampler_quality_list[i_vlc_q];
    const unsigned i_channels = p_filter->fmt_in.audio.i_channels;
    const double f_ratio = p_filter->fmt_out.audio.i_rate
                           / (double) p_filter->fmt_in.audio.i_rate;

    p_sys->f_fixed_ratio = f_ratio;
    soxr_error_t error;
    /* IO spec */
    soxr_io_spec_t io_spec = soxr_io_spec( i_itype, i_otype );
    /* Quality spec */
    soxr_quality_spec_t q_spec = soxr_quality_spec( i_recipe, 0 );
    /* Create SoXR */
    p_sys->soxr = soxr_create( 1, f_ratio, i_channels,
                               &error, &io_spec, &q_spec, NULL );
    if( error )
    {
        msg_Err( p_filter, "soxr_create failed: %s", soxr_strerror( error ) );
        free( p_sys );
        return VLC_EGENERIC;
    }

    /* Create a 'variable-rate' SoXR if needed: it is slower than the fixed
     * one, but it will be only used when the input rate is changing (to catch
     * up a delay).  */
    if( b_change_ratio )
    {
        q_spec = soxr_quality_spec( SOXR_LQ, SOXR_VR );
        p_sys->vr_soxr = soxr_create( 1, f_ratio, i_channels,
                                      &error, &io_spec, &q_spec, NULL );
        if( error )
        {
            msg_Err( p_filter, "soxr_create failed: %s", soxr_strerror( error ) );
            soxr_delete( p_sys->soxr );
            free( p_sys );
            return VLC_EGENERIC;
        }
        soxr_set_io_ratio( p_sys->vr_soxr, 1 / f_ratio, 0 );
    }

    msg_Dbg( p_filter, "Using SoX Resampler with '%s' engine and '%s' quality "
             "to convert %4.4s/%dHz to %4.4s/%dHz.",
             soxr_engine( p_sys->soxr ), soxr_resampler_quality_vlctext[i_vlc_q],
             (const char *)&p_filter->fmt_in.audio.i_format,
             p_filter->fmt_in.audio.i_rate,
             (const char *)&p_filter->fmt_out.audio.i_format,
             p_filter->fmt_out.audio.i_rate );

    p_filter->p_sys = p_sys;
    p_filter->pf_audio_filter = Resample;
    p_filter->pf_flush = Flush;
    p_filter->pf_audio_drain = Drain;
    return VLC_SUCCESS;
}