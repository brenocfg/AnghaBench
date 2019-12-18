#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  jint ;
struct TYPE_20__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_21__ {int /*<<< orphan*/  p_audiotrack; } ;
typedef  TYPE_3__ aout_sys_t ;
struct TYPE_22__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_4__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* NewGlobalRef ) (TYPE_4__**,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {scalar_t__ STATE_INITIALIZED; int /*<<< orphan*/  release; int /*<<< orphan*/  getState; scalar_t__ has_ctor_21; } ;
struct TYPE_18__ {TYPE_1__ AudioTrack; } ;
typedef  TYPE_4__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AudioTrack_New21 (TYPE_4__**,TYPE_2__*,unsigned int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AudioTrack_NewLegacy (TYPE_4__**,TYPE_2__*,unsigned int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CHECK_AT_EXCEPTION (char*) ; 
 scalar_t__ JNI_CALL_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JNI_CALL_VOID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_11__ jfields ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritInteger (TYPE_2__*,char*) ; 

__attribute__((used)) static int
AudioTrack_New( JNIEnv *env, audio_output_t *p_aout, unsigned int i_rate,
                int i_channel_config, int i_format, int i_size )
{
    aout_sys_t *p_sys = p_aout->sys;
    jint session_id = var_InheritInteger( p_aout, "audiotrack-session-id" );

    jobject p_audiotrack;
    if( jfields.AudioTrack.has_ctor_21 )
        p_audiotrack = AudioTrack_New21( env, p_aout, i_rate, i_channel_config,
                                         i_format, i_size, session_id );
    else
        p_audiotrack = AudioTrack_NewLegacy( env, p_aout, i_rate,
                                             i_channel_config, i_format, i_size,
                                             session_id );
    if( CHECK_AT_EXCEPTION( "AudioTrack<init>" ) || !p_audiotrack )
    {
        msg_Warn( p_aout, "AudioTrack Init failed" );
        return -1;
    }
    if( JNI_CALL_INT( p_audiotrack, jfields.AudioTrack.getState )
        != jfields.AudioTrack.STATE_INITIALIZED )
    {
        JNI_CALL_VOID( p_audiotrack, jfields.AudioTrack.release );
        (*env)->DeleteLocalRef( env, p_audiotrack );
        msg_Err( p_aout, "AudioTrack getState failed" );
        return -1;
    }

    p_sys->p_audiotrack = (*env)->NewGlobalRef( env, p_audiotrack );
    (*env)->DeleteLocalRef( env, p_audiotrack );
    if( !p_sys->p_audiotrack )
        return -1;

    return 0;
}