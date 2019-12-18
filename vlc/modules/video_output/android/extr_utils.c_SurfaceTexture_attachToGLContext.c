#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  p_jvm; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_1__ AWindowHandler ;

/* Variables and functions */
 int /*<<< orphan*/  CallBooleanMethod ; 
 scalar_t__ JNI_STEXCALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * android_getEnvCommon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  attachToGLContext ; 

int
SurfaceTexture_attachToGLContext(AWindowHandler *p_awh, int tex_name)
{
    JNIEnv *p_env = android_getEnvCommon(NULL, p_awh->p_jvm, "SurfaceTexture");
    if (!p_env)
        return VLC_EGENERIC;

    return JNI_STEXCALL(CallBooleanMethod, attachToGLContext, tex_name) ?
           VLC_SUCCESS : VLC_EGENERIC;
}