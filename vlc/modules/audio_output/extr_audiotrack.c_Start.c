#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_30__ ;
typedef  struct TYPE_49__   TYPE_2__ ;
typedef  struct TYPE_48__   TYPE_1__ ;
typedef  struct TYPE_47__   TYPE_12__ ;
typedef  struct TYPE_46__   TYPE_11__ ;
typedef  struct TYPE_45__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ jshortArray ;
typedef  scalar_t__ jobject ;
typedef  scalar_t__ jfloatArray ;
typedef  scalar_t__ jbyteArray ;
struct TYPE_57__ {scalar_t__ channel_type; scalar_t__ i_format; int i_bytes_per_frame; int i_frame_length; scalar_t__ i_rate; int /*<<< orphan*/  i_physical_channels; } ;
typedef  TYPE_9__ audio_sample_format_t ;
struct TYPE_45__ {int /*<<< orphan*/  (* mute_set ) (TYPE_10__*,int) ;int /*<<< orphan*/  (* volume_set ) (TYPE_10__*,int /*<<< orphan*/ ) ;TYPE_11__* sys; } ;
typedef  TYPE_10__ audio_output_t ;
struct TYPE_48__ {int /*<<< orphan*/  p_data; } ;
struct TYPE_55__ {TYPE_1__ bytebuffer; int /*<<< orphan*/  p_floatarray; int /*<<< orphan*/  p_shortarray; int /*<<< orphan*/  p_bytearray; } ;
struct TYPE_56__ {int i_size; TYPE_7__ u; scalar_t__ i_write; scalar_t__ i_read; } ;
struct TYPE_52__ {int /*<<< orphan*/  p_obj; } ;
struct TYPE_49__ {int /*<<< orphan*/  i_size; } ;
struct TYPE_46__ {scalar_t__ at_dev; int i_write_type; int b_thread_running; int b_thread_paused; TYPE_9__ fmt; scalar_t__ mute; int /*<<< orphan*/  volume; int /*<<< orphan*/  thread; TYPE_8__ circular; TYPE_4__ timestamp; TYPE_2__ audiotrack_args; int /*<<< orphan*/  i_max_audiotrack_samples; } ;
typedef  TYPE_11__ aout_sys_t ;
struct TYPE_54__ {scalar_t__ writeBufferV21; scalar_t__ writeV23; } ;
struct TYPE_53__ {int /*<<< orphan*/  has_ENCODING_IEC61937; } ;
struct TYPE_51__ {int /*<<< orphan*/  ctor; scalar_t__ clazz; } ;
struct TYPE_50__ {TYPE_6__ AudioTrack; TYPE_5__ AudioFormat; TYPE_3__ AudioTimestamp; } ;
struct TYPE_47__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_12__**,scalar_t__) ;int /*<<< orphan*/  (* NewGlobalRef ) (TYPE_12__**,scalar_t__) ;scalar_t__ (* NewFloatArray ) (TYPE_12__**,int) ;scalar_t__ (* NewShortArray ) (TYPE_12__**,int) ;scalar_t__ (* NewByteArray ) (TYPE_12__**,int) ;} ;
typedef  TYPE_12__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHANS_STEREO ; 
 scalar_t__ AOUT_FMT_LINEAR (TYPE_9__*) ; 
 int /*<<< orphan*/  AOUT_MAX_PREPARE_TIME ; 
 scalar_t__ AT_DEV_ENCODED ; 
 int AT_DEV_MAX_CHANNELS ; 
 scalar_t__ AT_DEV_STEREO ; 
 scalar_t__ AUDIO_CHANNEL_TYPE_AMBISONICS ; 
 scalar_t__ AUDIO_CHANNEL_TYPE_BITMAP ; 
 int /*<<< orphan*/  AudioTrack_Reset (TYPE_12__**,TYPE_10__*) ; 
 int /*<<< orphan*/  AudioTrack_Thread ; 
 int /*<<< orphan*/  BYTES_TO_FRAMES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_AT_EXCEPTION (char*) ; 
 TYPE_12__** GET_ENV () ; 
 int /*<<< orphan*/  JNI_AT_CALL_VOID (int /*<<< orphan*/ ) ; 
 scalar_t__ JNI_CALL (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewObject ; 
 int StartPCM (TYPE_12__**,TYPE_10__*,unsigned int) ; 
 int StartPassthrough (TYPE_12__**,TYPE_10__*) ; 
 int /*<<< orphan*/  Stop (TYPE_10__*) ; 
 scalar_t__ VLC_CODEC_FL32 ; 
 scalar_t__ VLC_CODEC_SPDIFL ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
#define  WRITE_BYTEARRAY 132 
#define  WRITE_BYTEARRAYV23 131 
#define  WRITE_BYTEBUFFER 130 
#define  WRITE_FLOATARRAY 129 
#define  WRITE_SHORTARRAYV23 128 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_9__*) ; 
 int /*<<< orphan*/  aout_FormatPrint (TYPE_10__*,char*,TYPE_9__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_30__ jfields ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_10__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_10__*,char*) ; 
 int /*<<< orphan*/  play ; 
 int samples_from_vlc_tick (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_12__**,scalar_t__) ; 
 int /*<<< orphan*/  stub10 (TYPE_12__**,scalar_t__) ; 
 int /*<<< orphan*/  stub11 (TYPE_12__**,scalar_t__) ; 
 int /*<<< orphan*/  stub12 (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (TYPE_10__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_12__**,scalar_t__) ; 
 scalar_t__ stub3 (TYPE_12__**,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_12__**,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (TYPE_12__**,scalar_t__) ; 
 scalar_t__ stub6 (TYPE_12__**,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_12__**,scalar_t__) ; 
 int /*<<< orphan*/  stub8 (TYPE_12__**,scalar_t__) ; 
 scalar_t__ stub9 (TYPE_12__**,int) ; 
 int var_InheritBool (TYPE_10__*,char*) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
Start( audio_output_t *p_aout, audio_sample_format_t *restrict p_fmt )
{
    aout_sys_t *p_sys = p_aout->sys;
    JNIEnv *env;
    int i_ret;
    bool b_try_passthrough;
    unsigned i_max_channels;

    if( p_sys->at_dev == AT_DEV_ENCODED )
    {
        b_try_passthrough = true;
        i_max_channels = AT_DEV_MAX_CHANNELS;
    }
    else
    {
        b_try_passthrough = var_InheritBool( p_aout, "spdif" );
        i_max_channels = p_sys->at_dev == AT_DEV_STEREO ? 2 : AT_DEV_MAX_CHANNELS;
    }

    if( !( env = GET_ENV() ) )
        return VLC_EGENERIC;

    p_sys->fmt = *p_fmt;

    aout_FormatPrint( p_aout, "VLC is looking for:", &p_sys->fmt );

    bool low_latency = false;
    if (p_sys->fmt.channel_type == AUDIO_CHANNEL_TYPE_AMBISONICS)
    {
        p_sys->fmt.channel_type = AUDIO_CHANNEL_TYPE_BITMAP;

        /* TODO: detect sink channel layout */
        p_sys->fmt.i_physical_channels = AOUT_CHANS_STEREO;
        aout_FormatPrepare(&p_sys->fmt);
        low_latency = true;
    }

    if( AOUT_FMT_LINEAR( &p_sys->fmt ) )
        i_ret = StartPCM( env, p_aout, i_max_channels );
    else if( b_try_passthrough )
        i_ret = StartPassthrough( env, p_aout );
    else
        return VLC_EGENERIC;

    if( i_ret != 0 )
        return VLC_EGENERIC;

    p_sys->i_max_audiotrack_samples = BYTES_TO_FRAMES( p_sys->audiotrack_args.i_size );

#ifdef AUDIOTRACK_HW_LATENCY
    if( jfields.AudioTimestamp.clazz )
    {
        /* create AudioTimestamp object */
        jobject p_obj = JNI_CALL( NewObject, jfields.AudioTimestamp.clazz,
                                 jfields.AudioTimestamp.ctor );
        if( p_obj )
        {
            p_sys->timestamp.p_obj = (*env)->NewGlobalRef( env, p_obj );
            (*env)->DeleteLocalRef( env, p_obj );
        }
        if( !p_sys->timestamp.p_obj )
            goto error;
    }
#endif

    AudioTrack_Reset( env, p_aout );

    if( p_sys->fmt.i_format == VLC_CODEC_FL32 )
    {
        msg_Dbg( p_aout, "using WRITE_FLOATARRAY");
        p_sys->i_write_type = WRITE_FLOATARRAY;
    }
    else if( p_sys->fmt.i_format == VLC_CODEC_SPDIFL )
    {
        assert( jfields.AudioFormat.has_ENCODING_IEC61937 );
        msg_Dbg( p_aout, "using WRITE_SHORTARRAYV23");
        p_sys->i_write_type = WRITE_SHORTARRAYV23;
    }
    else if( jfields.AudioTrack.writeV23 )
    {
        msg_Dbg( p_aout, "using WRITE_BYTEARRAYV23");
        p_sys->i_write_type = WRITE_BYTEARRAYV23;
    }
    else if( jfields.AudioTrack.writeBufferV21 )
    {
        msg_Dbg( p_aout, "using WRITE_BYTEBUFFER");
        p_sys->i_write_type = WRITE_BYTEBUFFER;
    }
    else
    {
        msg_Dbg( p_aout, "using WRITE_BYTEARRAY");
        p_sys->i_write_type = WRITE_BYTEARRAY;
    }

    p_sys->circular.i_read = p_sys->circular.i_write = 0;
    p_sys->circular.i_size = (int)p_sys->fmt.i_rate
                           * p_sys->fmt.i_bytes_per_frame
                           / p_sys->fmt.i_frame_length;
    if (low_latency)
    {
        /* 40 ms of buffering */
        p_sys->circular.i_size = p_sys->circular.i_size / 25;
    }
    else
    {
        /* 2 seconds of buffering */
        p_sys->circular.i_size = samples_from_vlc_tick(AOUT_MAX_PREPARE_TIME, p_sys->circular.i_size);
    }

    /* Allocate circular buffer */
    switch( p_sys->i_write_type )
    {
        case WRITE_BYTEARRAY:
        case WRITE_BYTEARRAYV23:
        {
            jbyteArray p_bytearray;

            p_bytearray = (*env)->NewByteArray( env, p_sys->circular.i_size );
            if( p_bytearray )
            {
                p_sys->circular.u.p_bytearray = (*env)->NewGlobalRef( env, p_bytearray );
                (*env)->DeleteLocalRef( env, p_bytearray );
            }

            if( !p_sys->circular.u.p_bytearray )
            {
                msg_Err(p_aout, "byte array allocation failed");
                goto error;
            }
            break;
        }
        case WRITE_SHORTARRAYV23:
        {
            jshortArray p_shortarray;

            p_shortarray = (*env)->NewShortArray( env,
                                                  p_sys->circular.i_size / 2 );
            if( p_shortarray )
            {
                p_sys->circular.u.p_shortarray = (*env)->NewGlobalRef( env, p_shortarray );
                (*env)->DeleteLocalRef( env, p_shortarray );
            }
            if( !p_sys->circular.u.p_shortarray )
            {
                msg_Err(p_aout, "short array allocation failed");
                goto error;
            }
            break;
        }
        case WRITE_FLOATARRAY:
        {
            jfloatArray p_floatarray;

            p_floatarray = (*env)->NewFloatArray( env,
                                                  p_sys->circular.i_size / 4 );
            if( p_floatarray )
            {
                p_sys->circular.u.p_floatarray = (*env)->NewGlobalRef( env, p_floatarray );
                (*env)->DeleteLocalRef( env, p_floatarray );
            }
            if( !p_sys->circular.u.p_floatarray )
            {
                msg_Err(p_aout, "float array allocation failed");
                goto error;
            }
            break;
        }
        case WRITE_BYTEBUFFER:
            p_sys->circular.u.bytebuffer.p_data = malloc( p_sys->circular.i_size );
            if( !p_sys->circular.u.bytebuffer.p_data )
            {
                msg_Err(p_aout, "bytebuffer allocation failed");
                goto error;
            }
            break;
    }

    /* Run AudioTrack_Thread */
    p_sys->b_thread_running = true;
    p_sys->b_thread_paused = false;
    if ( vlc_clone( &p_sys->thread, AudioTrack_Thread, p_aout,
                    VLC_THREAD_PRIORITY_LOW ) )
    {
        msg_Err(p_aout, "vlc clone failed");
        goto error;
    }

    JNI_AT_CALL_VOID( play );
    CHECK_AT_EXCEPTION( "play" );

    *p_fmt = p_sys->fmt;

    p_aout->volume_set(p_aout, p_sys->volume);
    if (p_sys->mute)
        p_aout->mute_set(p_aout, true);
    aout_FormatPrint( p_aout, "VLC will output:", &p_sys->fmt );

    return VLC_SUCCESS;

error:
    Stop( p_aout );
    return VLC_EGENERIC;
}