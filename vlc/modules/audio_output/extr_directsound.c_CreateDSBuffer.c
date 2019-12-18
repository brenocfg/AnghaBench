#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_12__ {int i_bytes_per_sample; int format; int i_rate; int i_channel_mask; int /*<<< orphan*/ * p_notify; int /*<<< orphan*/ * p_dsbuffer; int /*<<< orphan*/  chans_to_reorder; int /*<<< orphan*/  chan_table; int /*<<< orphan*/  p_dsobject; } ;
typedef  TYPE_3__ aout_stream_sys_t ;
struct TYPE_11__ {int wBitsPerSample; int nChannels; int nSamplesPerSec; int nBlockAlign; int nAvgBytesPerSec; int cbSize; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_10__ {int wValidBitsPerSample; } ;
struct TYPE_13__ {int dwChannelMask; TYPE_2__ Format; int /*<<< orphan*/  SubFormat; TYPE_1__ Samples; } ;
typedef  TYPE_4__ WAVEFORMATEXTENSIBLE ;
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
struct TYPE_14__ {int dwSize; int dwFlags; int /*<<< orphan*/ * lpwfxFormat; int /*<<< orphan*/  dwBufferBytes; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_5__ DSBUFFERDESC ;

/* Variables and functions */
 int DSBCAPS_CTRLPOSITIONNOTIFY ; 
 int DSBCAPS_CTRLVOLUME ; 
 int DSBCAPS_GETCURRENTPOSITION2 ; 
 int DSBCAPS_GLOBALFOCUS ; 
 int DSBCAPS_LOCHARDWARE ; 
 int /*<<< orphan*/  DS_BUF_SIZE ; 
 scalar_t__ DS_OK ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FillBuffer (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSoundBuffer_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound_CreateSoundBuffer (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirectSoundNotify ; 
 int SPEAKER_FRONT_LEFT ; 
 int SPEAKER_FRONT_RIGHT ; 
#define  VLC_CODEC_FL32 130 
#define  VLC_CODEC_S16N 129 
#define  VLC_CODEC_SPDIFL 128 
 int /*<<< orphan*/  WAVE_FORMAT_DOLBY_AC3_SPDIF ; 
 int /*<<< orphan*/  WAVE_FORMAT_EXTENSIBLE ; 
 int /*<<< orphan*/  WAVE_FORMAT_IEEE_FLOAT ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  _KSDATAFORMAT_SUBTYPE_DOLBY_AC3_SPDIF ; 
 int /*<<< orphan*/  _KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 int /*<<< orphan*/  _KSDATAFORMAT_SUBTYPE_PCM ; 
 int /*<<< orphan*/  aout_CheckChannelReorder (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int* pi_channels_in ; 
 int /*<<< orphan*/  pi_channels_out ; 
 int* pi_vlc_chan_order_wg4 ; 

__attribute__((used)) static HRESULT CreateDSBuffer( vlc_object_t *obj, aout_stream_sys_t *sys,
                               int i_format, int i_channels, int i_nb_channels,
                               int i_rate, bool b_probe )
{
    WAVEFORMATEXTENSIBLE waveformat;
    DSBUFFERDESC         dsbdesc;
    HRESULT              hr;

    /* First set the sound buffer format */
    waveformat.dwChannelMask = 0;
    for( unsigned i = 0; pi_vlc_chan_order_wg4[i]; i++ )
        if( i_channels & pi_vlc_chan_order_wg4[i] )
            waveformat.dwChannelMask |= pi_channels_in[i];

    switch( i_format )
    {
    case VLC_CODEC_SPDIFL:
        i_nb_channels = 2;
        /* To prevent channel re-ordering */
        waveformat.dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;
        waveformat.Format.wBitsPerSample = 16;
        waveformat.Samples.wValidBitsPerSample =
            waveformat.Format.wBitsPerSample;
        waveformat.Format.wFormatTag = WAVE_FORMAT_DOLBY_AC3_SPDIF;
        waveformat.SubFormat = _KSDATAFORMAT_SUBTYPE_DOLBY_AC3_SPDIF;
        break;

    case VLC_CODEC_FL32:
        waveformat.Format.wBitsPerSample = sizeof(float) * 8;
        waveformat.Samples.wValidBitsPerSample =
            waveformat.Format.wBitsPerSample;
        waveformat.Format.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
        waveformat.SubFormat = _KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
        break;

    case VLC_CODEC_S16N:
        waveformat.Format.wBitsPerSample = 16;
        waveformat.Samples.wValidBitsPerSample =
            waveformat.Format.wBitsPerSample;
        waveformat.Format.wFormatTag = WAVE_FORMAT_PCM;
        waveformat.SubFormat = _KSDATAFORMAT_SUBTYPE_PCM;
        break;
    }

    waveformat.Format.nChannels = i_nb_channels;
    waveformat.Format.nSamplesPerSec = i_rate;
    waveformat.Format.nBlockAlign =
        waveformat.Format.wBitsPerSample / 8 * i_nb_channels;
    waveformat.Format.nAvgBytesPerSec =
        waveformat.Format.nSamplesPerSec * waveformat.Format.nBlockAlign;

    sys->i_bytes_per_sample = waveformat.Format.nBlockAlign;
    sys->format = i_format;

    /* Then fill in the direct sound descriptor */
    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 /* Better position accuracy */
                    | DSBCAPS_GLOBALFOCUS         /* Allows background playing */
                    | DSBCAPS_CTRLVOLUME          /* Allows volume control */
                    | DSBCAPS_CTRLPOSITIONNOTIFY; /* Allow position notifications */

    /* Only use the new WAVE_FORMAT_EXTENSIBLE format for multichannel audio */
    if( i_nb_channels <= 2 )
    {
        waveformat.Format.cbSize = 0;
    }
    else
    {
        waveformat.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
        waveformat.Format.cbSize =
            sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);

        /* Needed for 5.1 on emu101k */
        dsbdesc.dwFlags |= DSBCAPS_LOCHARDWARE;
    }

    dsbdesc.dwBufferBytes = DS_BUF_SIZE; /* buffer size */
    dsbdesc.lpwfxFormat = (WAVEFORMATEX *)&waveformat;

    /* CreateSoundBuffer doesn't allow volume control for non-PCM buffers */
    if ( i_format == VLC_CODEC_SPDIFL )
        dsbdesc.dwFlags &= ~DSBCAPS_CTRLVOLUME;

    hr = IDirectSound_CreateSoundBuffer( sys->p_dsobject, &dsbdesc,
                                         &sys->p_dsbuffer, NULL );
    if( FAILED(hr) )
    {
        if( !(dsbdesc.dwFlags & DSBCAPS_LOCHARDWARE) )
            return hr;

        /* Try without DSBCAPS_LOCHARDWARE */
        dsbdesc.dwFlags &= ~DSBCAPS_LOCHARDWARE;
        hr = IDirectSound_CreateSoundBuffer( sys->p_dsobject, &dsbdesc,
                                             &sys->p_dsbuffer, NULL );
        if( FAILED(hr) )
            return hr;
        if( !b_probe )
            msg_Dbg( obj, "couldn't use hardware sound buffer" );
    }

    /* Stop here if we were just probing */
    if( b_probe )
    {
        IDirectSoundBuffer_Release( sys->p_dsbuffer );
        sys->p_dsbuffer = NULL;
        return DS_OK;
    }

    sys->i_rate = i_rate;
    sys->i_channel_mask = waveformat.dwChannelMask;
    sys->chans_to_reorder =
        aout_CheckChannelReorder( pi_channels_in, pi_channels_out,
                                  waveformat.dwChannelMask, sys->chan_table );
    if( sys->chans_to_reorder )
        msg_Dbg( obj, "channel reordering needed" );

    hr = IDirectSoundBuffer_QueryInterface( sys->p_dsbuffer,
                                            &IID_IDirectSoundNotify,
                                            (void **) &sys->p_notify );
    if( hr != DS_OK )
    {
        msg_Err( obj, "Couldn't query IDirectSoundNotify" );
        sys->p_notify = NULL;
    }

    FillBuffer( obj, sys, NULL );
    return DS_OK;
}