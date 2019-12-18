#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_format; int /*<<< orphan*/  i_channel_config; int /*<<< orphan*/  i_rate; } ;
struct TYPE_12__ {TYPE_1__ audiotrack_args; int /*<<< orphan*/ * p_audiotrack; } ;
typedef  TYPE_3__ aout_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* DeleteGlobalRef ) (TYPE_4__**,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__* JNIEnv ;

/* Variables and functions */
 int AudioTrack_New (TYPE_4__**,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JNI_AT_CALL_VOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release ; 
 int /*<<< orphan*/  stub1 (TYPE_4__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
AudioTrack_Recreate( JNIEnv *env, audio_output_t *p_aout )
{
    aout_sys_t *p_sys = p_aout->sys;

    JNI_AT_CALL_VOID( release );
    (*env)->DeleteGlobalRef( env, p_sys->p_audiotrack );
    p_sys->p_audiotrack = NULL;
    return AudioTrack_New( env, p_aout, p_sys->audiotrack_args.i_rate,
                           p_sys->audiotrack_args.i_channel_config,
                           p_sys->audiotrack_args.i_format,
                           p_sys->audiotrack_args.i_size );
}