#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_11__ {int /*<<< orphan*/  channel_type; int /*<<< orphan*/  i_rate; void* i_physical_channels; int /*<<< orphan*/  i_format; int /*<<< orphan*/  i_frame_length; int /*<<< orphan*/  i_bytes_per_frame; } ;
typedef  TYPE_1__ audio_sample_format_t ;
struct TYPE_12__ {int b_playing; int /*<<< orphan*/ * p_dsobject; int /*<<< orphan*/ * p_dsbuffer; int /*<<< orphan*/ * p_notify; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; scalar_t__ i_data; scalar_t__ i_last_read; scalar_t__ i_write; int /*<<< orphan*/  eraser_thread; } ;
typedef  TYPE_2__ aout_stream_sys_t ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  A52_FRAME_NB ; 
 void* AOUT_CHANS_2_0 ; 
 void* AOUT_CHANS_4_0 ; 
 void* AOUT_CHANS_5_1 ; 
 void* AOUT_CHANS_7_1 ; 
 void* AOUT_CHAN_CENTER ; 
 scalar_t__ AOUT_FMT_HDMI (TYPE_1__*) ; 
 scalar_t__ AOUT_FMT_SPDIF (TYPE_1__*) ; 
 int /*<<< orphan*/  AOUT_SPDIF_SIZE ; 
 int /*<<< orphan*/  AUDIO_CHANNEL_TYPE_BITMAP ; 
 scalar_t__ CreateDSBuffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CreateDSBufferPCM (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DSERR_UNSUPPORTED ; 
 int /*<<< orphan*/  DSSCL_EXCLUSIVE ; 
#define  DSSPEAKER_5POINT1 135 
#define  DSSPEAKER_5POINT1_SURROUND 134 
#define  DSSPEAKER_7POINT1 133 
#define  DSSPEAKER_7POINT1_SURROUND 132 
 int DSSPEAKER_CONFIG (int) ; 
#define  DSSPEAKER_MONO 131 
#define  DSSPEAKER_QUAD 130 
#define  DSSPEAKER_STEREO 129 
#define  DSSPEAKER_SURROUND 128 
 scalar_t__ DS_OK ; 
 int ENOMEM ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSoundNotify_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound_GetSpeakerConfig (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IDirectSound_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlayedDataEraser ; 
 int /*<<< orphan*/  VLC_CODEC_SPDIFL ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int VLC_VAR_BOOL ; 
 int VLC_VAR_DOINHERIT ; 
 int aout_FormatNbChannels (TYPE_1__*) ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 char** speaker_list ; 
 int /*<<< orphan*/  strlen (char const* const) ; 
 int /*<<< orphan*/  strncmp (char const* const,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int) ; 
 char* var_CreateGetString (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 int vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Start( vlc_object_t *obj, aout_stream_sys_t *sys,
                      audio_sample_format_t *restrict pfmt )
{
    if( aout_FormatNbChannels( pfmt ) == 0 )
        return E_FAIL;

#if !VLC_WINSTORE_APP
    /* Set DirectSound Cooperative level, ie what control we want over Windows
     * sound device. In our case, DSSCL_EXCLUSIVE means that we can modify the
     * settings of the primary buffer, but also that only the sound of our
     * application will be hearable when it will have the focus.
     * !!! (this is not really working as intended yet because to set the
     * cooperative level you need the window handle of your application, and
     * I don't know of any easy way to get it. Especially since we might play
     * sound without any video, and so what window handle should we use ???
     * The hack for now is to use the Desktop window handle - it seems to be
     * working */
    if( IDirectSound_SetCooperativeLevel( sys->p_dsobject, GetDesktopWindow(),
                                          DSSCL_EXCLUSIVE) )
        msg_Warn( obj, "cannot set direct sound cooperative level" );
#endif

    if( AOUT_FMT_HDMI( pfmt ) )
        return E_FAIL;

    audio_sample_format_t fmt = *pfmt;
    const char *const *ppsz_compare = speaker_list;
    char *psz_speaker;
    int i = 0;
    HRESULT hr = DSERR_UNSUPPORTED;

    /* Retrieve config values */
    var_Create( obj, "directx-audio-float32",
                VLC_VAR_BOOL | VLC_VAR_DOINHERIT );
    psz_speaker = var_CreateGetString( obj, "directx-audio-speaker" );

    while ( *ppsz_compare != NULL )
    {
        if ( !strncmp( *ppsz_compare, psz_speaker, strlen(*ppsz_compare) ) )
        {
            break;
        }
        ppsz_compare++; i++;
    }

    if ( *ppsz_compare == NULL )
    {
        msg_Err( obj, "(%s) isn't valid speaker setup option", psz_speaker );
        msg_Err( obj, "Defaulting to Windows default speaker config");
        i = 0;
    }
    free( psz_speaker );

    vlc_mutex_init(&sys->lock);
    vlc_cond_init(&sys->cond);

    if( AOUT_FMT_SPDIF( &fmt ) )
    {
        if( var_InheritBool( obj, "spdif" ) )
            hr = CreateDSBuffer( obj, sys, VLC_CODEC_SPDIFL,
                                 fmt.i_physical_channels,
                                 aout_FormatNbChannels(&fmt), fmt.i_rate, false );

        if( hr == DS_OK )
        {
            msg_Dbg( obj, "using A/52 pass-through over S/PDIF" );
            fmt.i_format = VLC_CODEC_SPDIFL;

            /* Calculate the frame size in bytes */
            fmt.i_bytes_per_frame = AOUT_SPDIF_SIZE;
            fmt.i_frame_length = A52_FRAME_NB;
        }
        else
        {
            vlc_mutex_destroy(&sys->lock);
            vlc_cond_destroy(&sys->cond);
            return E_FAIL;
        }
    }

    if( hr != DS_OK )
    {
        if( i == 0 )
        {
            DWORD ui_speaker_config;
            int i_channels = 2; /* Default to stereo */
            int i_orig_channels = aout_FormatNbChannels( &fmt );

            /* Check the speaker configuration to determine which channel
             * config should be the default */
            hr = IDirectSound_GetSpeakerConfig( sys->p_dsobject,
                                                &ui_speaker_config );
            if( FAILED(hr) )
            {
                ui_speaker_config = DSSPEAKER_STEREO;
                msg_Dbg( obj, "GetSpeakerConfig failed" );
            }

            const char *name = "Unknown";
            switch( DSSPEAKER_CONFIG(ui_speaker_config) )
            {
                case DSSPEAKER_7POINT1:
                case DSSPEAKER_7POINT1_SURROUND:
                    name = "7.1";
                    i_channels = 8;
                    break;
                case DSSPEAKER_5POINT1:
                case DSSPEAKER_5POINT1_SURROUND:
                    name = "5.1";
                    i_channels = 6;
                    break;
                case DSSPEAKER_QUAD:
                    name = "Quad";
                    i_channels = 4;
                    break;
#if 0 /* Lots of people just get their settings wrong and complain that
       * this is a problem with VLC so just don't ever set mono by default. */
                case DSSPEAKER_MONO:
                    name = "Mono";
                    i_channels = 1;
                    break;
#endif
                case DSSPEAKER_SURROUND:
                    name = "Surround";
                    i_channels = 4;
                    break;
                case DSSPEAKER_STEREO:
                    name = "Stereo";
                    i_channels = 2;
                    break;
            }

            if( i_channels >= i_orig_channels )
                i_channels = i_orig_channels;

            msg_Dbg( obj, "%s speaker config: %s and stream has "
                     "%d channels, using %d channels", "Windows", name,
                     i_orig_channels, i_channels );

            switch( i_channels )
            {
                case 8:
                    fmt.i_physical_channels = AOUT_CHANS_7_1;
                    break;
                case 7:
                case 6:
                    fmt.i_physical_channels = AOUT_CHANS_5_1;
                    break;
                case 5:
                case 4:
                    fmt.i_physical_channels = AOUT_CHANS_4_0;
                    break;
                default:
                    fmt.i_physical_channels = AOUT_CHANS_2_0;
                    break;
            }
        }
        else
        {   /* Overriden speaker configuration */
            const char *name = "Non-existant";
            switch( i )
            {
                case 1: /* Mono */
                    name = "Mono";
                    fmt.i_physical_channels = AOUT_CHAN_CENTER;
                    break;
                case 2: /* Stereo */
                    name = "Stereo";
                    fmt.i_physical_channels = AOUT_CHANS_2_0;
                    break;
                case 3: /* Quad */
                    name = "Quad";
                    fmt.i_physical_channels = AOUT_CHANS_4_0;
                    break;
                case 4: /* 5.1 */
                    name = "5.1";
                    fmt.i_physical_channels = AOUT_CHANS_5_1;
                    break;
                case 5: /* 7.1 */
                    name = "7.1";
                    fmt.i_physical_channels = AOUT_CHANS_7_1;
                    break;
            }
            msg_Dbg( obj, "%s speaker config: %s", "VLC", name );
        }

        /* Open the device */
        aout_FormatPrepare( &fmt );

        hr = CreateDSBufferPCM( obj, sys, &fmt.i_format,
                                fmt.i_physical_channels, fmt.i_rate, false );
        if( hr != DS_OK )
        {
            msg_Err( obj, "cannot open directx audio device" );
            goto error;
        }
    }

    int ret = vlc_clone(&sys->eraser_thread, PlayedDataEraser, (void*) obj,
                        VLC_THREAD_PRIORITY_LOW);
    if( unlikely( ret ) )
    {
        if( ret != ENOMEM )
            msg_Err( obj, "Couldn't start eraser thread" );

        hr = E_FAIL;
        goto error;
    }

    fmt.channel_type = AUDIO_CHANNEL_TYPE_BITMAP;

    *pfmt = fmt;
    sys->b_playing = false;
    sys->i_write = 0;
    sys->i_last_read =  0;
    sys->i_data = 0;

    return DS_OK;

error:
    vlc_cond_destroy(&sys->cond);
    vlc_mutex_destroy(&sys->lock);

    if( sys->p_notify != NULL )
    {
        IDirectSoundNotify_Release( sys->p_notify );
        sys->p_notify = NULL;
    }
    if( sys->p_dsbuffer != NULL )
    {
        IDirectSoundBuffer_Release( sys->p_dsbuffer );
        sys->p_dsbuffer = NULL;
    }
    IDirectSound_Release( sys->p_dsobject );
    sys->p_dsobject = NULL;
    return hr;
}