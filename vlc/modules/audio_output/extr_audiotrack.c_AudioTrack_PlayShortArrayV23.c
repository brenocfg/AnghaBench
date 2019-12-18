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
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ audio_output_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_shortarray; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
struct TYPE_12__ {TYPE_2__ circular; } ;
typedef  TYPE_5__ aout_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  WRITE_NON_BLOCKING; } ;
struct TYPE_13__ {TYPE_3__ AudioTrack; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int JNI_AT_CALL_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 TYPE_6__ jfields ; 
 int /*<<< orphan*/  writeShortV23 ; 

__attribute__((used)) static int
AudioTrack_PlayShortArrayV23( JNIEnv *env, audio_output_t *p_aout,
                               size_t i_data_size, size_t i_data_offset )
{
    aout_sys_t *p_sys = p_aout->sys;
    int i_ret;

    i_ret = JNI_AT_CALL_INT( writeShortV23, p_sys->circular.u.p_shortarray,
                             i_data_offset / 2, i_data_size / 2,
                             jfields.AudioTrack.WRITE_NON_BLOCKING );
    if( i_ret < 0 )
        return i_ret;
    else
        return i_ret * 2;
}