#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_11__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ audio_output_t ;
struct TYPE_10__ {unsigned int i_rate; int i_channel_config; int i_format; int i_size; } ;
struct TYPE_12__ {TYPE_2__ audiotrack_args; } ;
typedef  TYPE_4__ aout_sys_t ;
struct TYPE_9__ {int CHANNEL_OUT_5POINT1; int CHANNEL_OUT_SIDE_LEFT; int CHANNEL_OUT_SIDE_RIGHT; int CHANNEL_OUT_MONO; int CHANNEL_OUT_STEREO; } ;
struct TYPE_13__ {TYPE_1__ AudioFormat; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
#define  AOUT_CHANS_5_1 131 
#define  AOUT_CHANS_7_1 130 
#define  AOUT_CHANS_STEREO 129 
#define  AOUT_CHAN_LEFT 128 
 scalar_t__ AudioTrack_New (int /*<<< orphan*/ *,TYPE_3__*,unsigned int,int,int,int) ; 
 int JNI_AT_CALL_STATIC_INT (int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/  getMinBufferSize ; 
 TYPE_6__ jfields ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static int
AudioTrack_Create( JNIEnv *env, audio_output_t *p_aout,
                   unsigned int i_rate,
                   int i_format,
                   uint16_t i_physical_channels )
{
    aout_sys_t *p_sys = p_aout->sys;
    int i_size, i_min_buffer_size, i_channel_config;

    switch( i_physical_channels )
    {
        case AOUT_CHANS_7_1:
            /* bitmask of CHANNEL_OUT_7POINT1 doesn't correspond to 5POINT1 and
             * SIDES */
            i_channel_config = jfields.AudioFormat.CHANNEL_OUT_5POINT1 |
                               jfields.AudioFormat.CHANNEL_OUT_SIDE_LEFT |
                               jfields.AudioFormat.CHANNEL_OUT_SIDE_RIGHT;
            break;
        case AOUT_CHANS_5_1:
            i_channel_config = jfields.AudioFormat.CHANNEL_OUT_5POINT1;
            break;
        case AOUT_CHAN_LEFT:
            i_channel_config = jfields.AudioFormat.CHANNEL_OUT_MONO;
            break;
        case AOUT_CHANS_STEREO:
            i_channel_config = jfields.AudioFormat.CHANNEL_OUT_STEREO;
            break;
        default:
            vlc_assert_unreachable();
    }

    i_min_buffer_size = JNI_AT_CALL_STATIC_INT( getMinBufferSize, i_rate,
                                                i_channel_config, i_format );
    if( i_min_buffer_size <= 0 )
    {
        msg_Warn( p_aout, "getMinBufferSize returned an invalid size" ) ;
        return -1;
    }
    i_size = i_min_buffer_size * 2;

    /* create AudioTrack object */
    if( AudioTrack_New( env, p_aout, i_rate, i_channel_config,
                        i_format , i_size ) != 0 )
        return -1;

    p_sys->audiotrack_args.i_rate = i_rate;
    p_sys->audiotrack_args.i_channel_config = i_channel_config;
    p_sys->audiotrack_args.i_format = i_format;
    p_sys->audiotrack_args.i_size = i_size;

    return 0;
}