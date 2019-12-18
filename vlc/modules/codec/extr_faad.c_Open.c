#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_15__ {scalar_t__ i_rate; int /*<<< orphan*/  i_chan_mode; int /*<<< orphan*/  channel_type; } ;
struct TYPE_16__ {scalar_t__ i_codec; scalar_t__ i_profile; int i_extra; TYPE_3__ audio; int /*<<< orphan*/  p_extra; } ;
struct TYPE_13__ {unsigned long i_rate; unsigned char i_channels; int /*<<< orphan*/  i_chan_mode; scalar_t__ i_physical_channels; int /*<<< orphan*/  channel_type; } ;
struct TYPE_14__ {TYPE_1__ audio; int /*<<< orphan*/  i_codec; } ;
struct TYPE_17__ {int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; TYPE_4__ fmt_in; TYPE_2__ fmt_out; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_18__ {int b_discontinuity; int b_sbr; int b_ps; int /*<<< orphan*/ * p_block; scalar_t__ i_last_length; int /*<<< orphan*/ * hfaad; int /*<<< orphan*/  date; } ;
typedef  TYPE_6__ decoder_sys_t ;
struct TYPE_19__ {int /*<<< orphan*/  outputFormat; scalar_t__ defSampleRate; } ;
typedef  TYPE_7__ NeAACDecConfiguration ;

/* Variables and functions */
 scalar_t__ AAC_PROFILE_ELD ; 
 int /*<<< orphan*/  DecodeBlock ; 
 int /*<<< orphan*/  FAAD_FMT_16BIT ; 
 int /*<<< orphan*/  FAAD_FMT_FLOAT ; 
 int /*<<< orphan*/  Flush ; 
 int GetWBE (int /*<<< orphan*/ ) ; 
 scalar_t__ HAVE_FPU ; 
 unsigned char MPEG4_ASC_MAX_INDEXEDPOS ; 
 int /*<<< orphan*/  NeAACDecClose (int /*<<< orphan*/ *) ; 
 TYPE_7__* NeAACDecGetCurrentConfiguration (int /*<<< orphan*/ *) ; 
 scalar_t__ NeAACDecInit2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned long*,unsigned char*) ; 
 int /*<<< orphan*/ * NeAACDecOpen () ; 
 int /*<<< orphan*/  NeAACDecSetConfiguration (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  VLC_CODEC_FL32 ; 
 scalar_t__ VLC_CODEC_MP4A ; 
 int /*<<< orphan*/  VLC_CODEC_S16N ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 TYPE_6__* malloc (int) ; 
 scalar_t__* mpeg4_asc_channelsbyindex ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;
    NeAACDecConfiguration *cfg;

    if( p_dec->fmt_in.i_codec != VLC_CODEC_MP4A ||
        p_dec->fmt_in.i_profile == AAC_PROFILE_ELD ||
        (p_dec->fmt_in.i_extra > 1 &&
         (GetWBE(p_dec->fmt_in.p_extra) & 0xffe0) == 0xf8e0)) /* ELD AOT */
    {
        return VLC_EGENERIC;
    }

    /* Allocate the memory needed to store the decoder's structure */
    if( ( p_dec->p_sys = p_sys = malloc( sizeof(*p_sys) ) ) == NULL )
        return VLC_ENOMEM;

    /* Open a faad context */
    if( ( p_sys->hfaad = NeAACDecOpen() ) == NULL )
    {
        msg_Err( p_dec, "cannot initialize faad" );
        free( p_sys );
        return VLC_EGENERIC;
    }

    /* Misc init */
    p_dec->fmt_out.audio.channel_type = p_dec->fmt_in.audio.channel_type;

    if( p_dec->fmt_in.i_extra > 0 )
    {
        /* We have a decoder config so init the handle */
        unsigned long i_rate;
        unsigned char i_channels;

        if( NeAACDecInit2( p_sys->hfaad, p_dec->fmt_in.p_extra,
                           p_dec->fmt_in.i_extra,
                           &i_rate, &i_channels ) < 0 ||
                i_channels >= MPEG4_ASC_MAX_INDEXEDPOS )
        {
            msg_Err( p_dec, "Failed to initialize faad using extra data" );
            NeAACDecClose( p_sys->hfaad );
            free( p_sys );
            return VLC_EGENERIC;
        }

        p_dec->fmt_out.audio.i_rate = i_rate;
        p_dec->fmt_out.audio.i_channels = i_channels;
        p_dec->fmt_out.audio.i_physical_channels
            = mpeg4_asc_channelsbyindex[i_channels];
        date_Init( &p_sys->date, i_rate, 1 );
    }
    else
    {
        p_dec->fmt_out.audio.i_physical_channels = 0;
        /* Will be initalised from first frame */
        p_dec->fmt_out.audio.i_rate = 0;
        p_dec->fmt_out.audio.i_channels = 0;
        date_Set( &p_sys->date, VLC_TICK_INVALID );
    }

    p_dec->fmt_out.i_codec = HAVE_FPU ? VLC_CODEC_FL32 : VLC_CODEC_S16N;
    p_dec->fmt_out.audio.i_chan_mode = p_dec->fmt_in.audio.i_chan_mode;

    /* Set the faad config */
    cfg = NeAACDecGetCurrentConfiguration( p_sys->hfaad );
    if( p_dec->fmt_in.audio.i_rate )
        cfg->defSampleRate = p_dec->fmt_in.audio.i_rate;
    cfg->outputFormat = HAVE_FPU ? FAAD_FMT_FLOAT : FAAD_FMT_16BIT;
    NeAACDecSetConfiguration( p_sys->hfaad, cfg );

    p_sys->i_last_length = 0;

    /* buffer */
    p_sys->p_block = NULL;

    p_sys->b_discontinuity =
    p_sys->b_sbr = p_sys->b_ps = false;

    p_dec->pf_decode = DecodeBlock;
    p_dec->pf_flush  = Flush;
    return VLC_SUCCESS;
}