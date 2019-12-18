#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  jtransform_mtx_array; } ;
struct TYPE_14__ {TYPE_1__ stex; scalar_t__ p_anw_dl; int /*<<< orphan*/  jobj; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* DeleteGlobalRef ) (TYPE_2__**,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* JNIEnv ;
typedef  TYPE_3__ AWindowHandler ;

/* Variables and functions */
 TYPE_2__** AWindowHandler_getEnv (TYPE_3__*) ; 
 int /*<<< orphan*/  AWindowHandler_releaseANativeWindowEnv (TYPE_3__*,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AWindow_Subtitles ; 
 int /*<<< orphan*/  AWindow_Video ; 
 int /*<<< orphan*/  CallVoidMethod ; 
 int /*<<< orphan*/  JNI_ANWCALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlclose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregisterNative ; 

void
AWindowHandler_destroy(AWindowHandler *p_awh)
{
    JNIEnv *p_env = AWindowHandler_getEnv(p_awh);

    if (p_env)
    {
        JNI_ANWCALL(CallVoidMethod, unregisterNative);
        AWindowHandler_releaseANativeWindowEnv(p_awh, p_env, AWindow_Video);
        AWindowHandler_releaseANativeWindowEnv(p_awh, p_env, AWindow_Subtitles);
        (*p_env)->DeleteGlobalRef(p_env, p_awh->jobj);
    }

    if (p_awh->p_anw_dl)
        dlclose(p_awh->p_anw_dl);

    (*p_env)->DeleteGlobalRef(p_env, p_awh->stex.jtransform_mtx_array);
    free(p_awh);
}