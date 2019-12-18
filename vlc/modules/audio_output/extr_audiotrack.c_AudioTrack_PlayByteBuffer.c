#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_6__* sys; } ;
typedef  TYPE_5__ audio_output_t ;
struct TYPE_16__ {scalar_t__ p_obj; int /*<<< orphan*/  p_data; } ;
struct TYPE_17__ {TYPE_1__ bytebuffer; } ;
struct TYPE_18__ {TYPE_2__ u; int /*<<< orphan*/  i_size; } ;
struct TYPE_21__ {TYPE_3__ circular; } ;
typedef  TYPE_6__ aout_sys_t ;
struct TYPE_22__ {int /*<<< orphan*/  (* ExceptionClear ) (TYPE_7__**) ;scalar_t__ (* ExceptionCheck ) (TYPE_7__**) ;scalar_t__ (* NewDirectByteBuffer ) (TYPE_7__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_7__**,scalar_t__) ;} ;
struct TYPE_19__ {int ERROR; int /*<<< orphan*/  WRITE_NON_BLOCKING; } ;
struct TYPE_15__ {TYPE_4__ AudioTrack; } ;
typedef  TYPE_7__* JNIEnv ;

/* Variables and functions */
 int JNI_AT_CALL_INT (int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 TYPE_12__ jfields ; 
 int /*<<< orphan*/  stub1 (TYPE_7__**,scalar_t__) ; 
 scalar_t__ stub2 (TYPE_7__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_7__**) ; 
 int /*<<< orphan*/  stub4 (TYPE_7__**) ; 
 int /*<<< orphan*/  writeBufferV21 ; 

__attribute__((used)) static int
AudioTrack_PlayByteBuffer( JNIEnv *env, audio_output_t *p_aout,
                           size_t i_data_size, size_t i_data_offset )
{
    aout_sys_t *p_sys = p_aout->sys;

    /* The same DirectByteBuffer will be used until the data_offset reaches 0.
     * The internal position of this buffer is moved by the writeBufferV21
     * wall. */
    if( i_data_offset == 0 )
    {
        /* No need to get a global ref, this object will be only used from the
         * same Thread */
        if( p_sys->circular.u.bytebuffer.p_obj )
            (*env)->DeleteLocalRef( env, p_sys->circular.u.bytebuffer.p_obj );

        p_sys->circular.u.bytebuffer.p_obj = (*env)->NewDirectByteBuffer( env,
                                            p_sys->circular.u.bytebuffer.p_data,
                                            p_sys->circular.i_size );
        if( !p_sys->circular.u.bytebuffer.p_obj )
        {
            if( (*env)->ExceptionCheck( env ) )
                (*env)->ExceptionClear( env );
            return jfields.AudioTrack.ERROR;
        }
    }

    return JNI_AT_CALL_INT( writeBufferV21, p_sys->circular.u.bytebuffer.p_obj,
                            i_data_size,
                            jfields.AudioTrack.WRITE_NON_BLOCKING );
}