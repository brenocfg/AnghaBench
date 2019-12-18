#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_11__ {int b_audiotrack_exception; int b_error; } ;
typedef  TYPE_2__ aout_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* ExceptionClear ) (TYPE_3__**) ;int /*<<< orphan*/  (* ExceptionDescribe ) (TYPE_3__**) ;scalar_t__ (* ExceptionCheck ) (TYPE_3__**) ;} ;
typedef  TYPE_3__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char const*,char const*) ; 
 scalar_t__ stub1 (TYPE_3__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__**) ; 

__attribute__((used)) static inline bool
check_exception( JNIEnv *env, audio_output_t *p_aout,
                 const char *class, const char *method )
{
    if( (*env)->ExceptionCheck( env ) )
    {
        aout_sys_t *p_sys = p_aout->sys;

        p_sys->b_audiotrack_exception = true;
        p_sys->b_error = true;
        (*env)->ExceptionDescribe( env );
        (*env)->ExceptionClear( env );
        msg_Err( p_aout, "%s.%s triggered an exception !", class, method );
        return true;
    } else
        return false;
}