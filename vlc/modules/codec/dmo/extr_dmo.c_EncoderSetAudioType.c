#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_28__ {int i_bitspersample; scalar_t__ i_rate; scalar_t__ i_channels; } ;
struct TYPE_29__ {TYPE_1__ audio; int /*<<< orphan*/  i_codec; } ;
struct TYPE_30__ {scalar_t__ i_rate; scalar_t__ i_channels; scalar_t__ i_bitspersample; scalar_t__ i_blockalign; } ;
struct TYPE_31__ {int i_bitrate; int i_extra; int /*<<< orphan*/ * p_extra; TYPE_3__ audio; int /*<<< orphan*/  i_codec; } ;
struct TYPE_33__ {TYPE_2__ fmt_in; TYPE_4__ fmt_out; } ;
typedef  TYPE_6__ encoder_t ;
struct TYPE_34__ {scalar_t__ wFormatTag; scalar_t__ nSamplesPerSec; scalar_t__ nChannels; scalar_t__ wBitsPerSample; int nAvgBytesPerSec; int cbSize; scalar_t__ nBlockAlign; } ;
typedef  TYPE_7__ WAVEFORMATEX ;
struct TYPE_36__ {scalar_t__ pbFormat; } ;
struct TYPE_35__ {TYPE_5__* vt; } ;
struct TYPE_32__ {int (* SetOutputType ) (TYPE_8__*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ;int (* SetInputType ) (TYPE_8__*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetInputType ) (TYPE_8__*,int /*<<< orphan*/ ,int,TYPE_9__*) ;int /*<<< orphan*/  (* GetOutputType ) (TYPE_8__*,int /*<<< orphan*/ ,int,TYPE_9__*) ;} ;
typedef  TYPE_8__ IMediaObject ;
typedef  TYPE_9__ DMO_MEDIA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DMOFreeMediaType (TYPE_9__*) ; 
 int /*<<< orphan*/  VLC_CODEC_S16N ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  fourcc_to_wf_tag (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,int /*<<< orphan*/ ,int,TYPE_9__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*,int /*<<< orphan*/ ,int,TYPE_9__*) ; 
 int stub3 (TYPE_8__*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_8__*,int /*<<< orphan*/ ,int,TYPE_9__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_8__*,int /*<<< orphan*/ ,int,TYPE_9__*) ; 
 int stub6 (TYPE_8__*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int EncoderSetAudioType( encoder_t *p_enc, IMediaObject *p_dmo )
{
    int i, i_selected, i_err;
    unsigned int i_last_byterate;
    uint16_t i_tag;
    DMO_MEDIA_TYPE dmo_type;
    WAVEFORMATEX *p_wf;

    /* Setup the format structure */
    fourcc_to_wf_tag( p_enc->fmt_out.i_codec, &i_tag );
    if( i_tag == 0 ) return VLC_EGENERIC;

    p_enc->fmt_in.i_codec = VLC_CODEC_S16N;
    p_enc->fmt_in.audio.i_bitspersample = 16;

    /* We first need to choose an output type from the predefined
     * list of choices (we cycle through the list to select the best match) */
    i = 0; i_selected = -1; i_last_byterate = 0;
    while( !p_dmo->vt->GetOutputType( p_dmo, 0, i++, &dmo_type ) )
    {
        p_wf = (WAVEFORMATEX *)dmo_type.pbFormat;
        msg_Dbg( p_enc, "available format :%i, sample rate: %i, channels: %i, "
                 "bits per sample: %i, bitrate: %i, blockalign: %i",
                 (int) p_wf->wFormatTag, (int)p_wf->nSamplesPerSec,
                 (int)p_wf->nChannels, (int)p_wf->wBitsPerSample,
                 (int)p_wf->nAvgBytesPerSec * 8, (int)p_wf->nBlockAlign );

        if( p_wf->wFormatTag == i_tag &&
            p_wf->nSamplesPerSec == p_enc->fmt_in.audio.i_rate &&
            p_wf->nChannels == p_enc->fmt_in.audio.i_channels &&
            p_wf->wBitsPerSample == p_enc->fmt_in.audio.i_bitspersample )
        {
            if( p_wf->nAvgBytesPerSec <
                p_enc->fmt_out.i_bitrate * 110 / 800 /* + 10% */ &&
                p_wf->nAvgBytesPerSec > i_last_byterate )
            {
                i_selected = i - 1;
                i_last_byterate = p_wf->nAvgBytesPerSec;
                msg_Dbg( p_enc, "selected entry %i (bitrate: %i)",
                         i_selected, p_wf->nAvgBytesPerSec * 8 );
            }
        }

        DMOFreeMediaType( &dmo_type );
    }

    if( i_selected < 0 )
    {
        msg_Err( p_enc, "couldn't find a matching output" );
        return VLC_EGENERIC;
    }

    p_dmo->vt->GetOutputType( p_dmo, 0, i_selected, &dmo_type );
    p_wf = (WAVEFORMATEX *)dmo_type.pbFormat;

    msg_Dbg( p_enc, "selected format: %i, sample rate:%i, "
             "channels: %i, bits per sample: %i, bitrate: %i, blockalign: %i",
             (int)p_wf->wFormatTag, (int)p_wf->nSamplesPerSec,
             (int)p_wf->nChannels, (int)p_wf->wBitsPerSample,
             (int)p_wf->nAvgBytesPerSec * 8, (int)p_wf->nBlockAlign );

    p_enc->fmt_out.audio.i_rate = p_wf->nSamplesPerSec;
    p_enc->fmt_out.audio.i_channels = p_wf->nChannels;
    p_enc->fmt_out.audio.i_bitspersample = p_wf->wBitsPerSample;
    p_enc->fmt_out.audio.i_blockalign = p_wf->nBlockAlign;
    p_enc->fmt_out.i_bitrate = p_wf->nAvgBytesPerSec * 8;

    if( p_wf->cbSize )
    {
        msg_Dbg( p_enc, "found cbSize: %i", p_wf->cbSize );
        p_enc->fmt_out.i_extra = p_wf->cbSize;
        p_enc->fmt_out.p_extra = malloc( p_enc->fmt_out.i_extra );
        if( p_enc->fmt_out.p_extra == NULL)
            return VLC_EGENERIC;

        memcpy( p_enc->fmt_out.p_extra, &p_wf[1], p_enc->fmt_out.i_extra );
    }

    i_err = p_dmo->vt->SetOutputType( p_dmo, 0, &dmo_type, 0 );
    DMOFreeMediaType( &dmo_type );

    if( i_err )
    {
        msg_Err( p_enc, "can't set DMO output type: %i", i_err );
        return VLC_EGENERIC;
    }

    msg_Dbg( p_enc, "successfully set output type" );

    /* Setup the input type */
    i = 0; i_selected = -1;
    while( !p_dmo->vt->GetInputType( p_dmo, 0, i++, &dmo_type ) )
    {
        p_wf = (WAVEFORMATEX *)dmo_type.pbFormat;
        msg_Dbg( p_enc, "available format :%i, sample rate: %i, channels: %i, "
                 "bits per sample: %i, bitrate: %i, blockalign: %i",
                 (int) p_wf->wFormatTag, (int)p_wf->nSamplesPerSec,
                 (int)p_wf->nChannels, (int)p_wf->wBitsPerSample,
                 (int)p_wf->nAvgBytesPerSec * 8, (int)p_wf->nBlockAlign );

        if( p_wf->wFormatTag == WAVE_FORMAT_PCM &&
            p_wf->nSamplesPerSec == p_enc->fmt_in.audio.i_rate &&
            p_wf->nChannels == p_enc->fmt_in.audio.i_channels &&
            p_wf->wBitsPerSample == p_enc->fmt_in.audio.i_bitspersample )
        {
            i_selected = i - 1;
        }

        DMOFreeMediaType( &dmo_type );
    }

    if( i_selected < 0 )
    {
        msg_Err( p_enc, "couldn't find a matching input" );
        return VLC_EGENERIC;
    }

    p_dmo->vt->GetInputType( p_dmo, 0, i_selected, &dmo_type );
    i_err = p_dmo->vt->SetInputType( p_dmo, 0, &dmo_type, 0 );
    DMOFreeMediaType( &dmo_type );
    if( i_err )
    {
        msg_Err( p_enc, "can't set DMO input type: 0x%x", i_err );
        return VLC_EGENERIC;
    }
    msg_Dbg( p_enc, "successfully set input type" );

    return VLC_SUCCESS;
}