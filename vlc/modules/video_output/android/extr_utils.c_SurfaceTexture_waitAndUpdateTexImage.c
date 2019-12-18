#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float* jtransform_mtx; int /*<<< orphan*/  jtransform_mtx_array; } ;
struct TYPE_10__ {TYPE_1__ stex; int /*<<< orphan*/  p_jvm; } ;
struct TYPE_9__ {float* (* GetFloatArrayElements ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ReleaseFloatArrayElements ) (TYPE_2__**,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* JNIEnv ;
typedef  TYPE_3__ AWindowHandler ;

/* Variables and functions */
 int /*<<< orphan*/  CallBooleanMethod ; 
 int /*<<< orphan*/  JNI_ABORT ; 
 int JNI_STEXCALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 TYPE_2__** android_getEnvCommon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 float* stub2 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitAndUpdateTexImage ; 

int
SurfaceTexture_waitAndUpdateTexImage(AWindowHandler *p_awh,
                                     const float **pp_transform_mtx)
{
    JNIEnv *p_env = android_getEnvCommon(NULL, p_awh->p_jvm, "SurfaceTexture");
    if (!p_env)
        return VLC_EGENERIC;

    if (p_awh->stex.jtransform_mtx != NULL)
        (*p_env)->ReleaseFloatArrayElements(p_env, p_awh->stex.jtransform_mtx_array,
                                            p_awh->stex.jtransform_mtx,
                                            JNI_ABORT);

    bool ret = JNI_STEXCALL(CallBooleanMethod, waitAndUpdateTexImage,
                            p_awh->stex.jtransform_mtx_array);
    if (ret)
    {
        p_awh->stex.jtransform_mtx = (*p_env)->GetFloatArrayElements(p_env,
                                            p_awh->stex.jtransform_mtx_array, NULL);
        *pp_transform_mtx = p_awh->stex.jtransform_mtx;
        return VLC_SUCCESS;
    }
    else
    {
        p_awh->stex.jtransform_mtx = NULL;
        return VLC_EGENERIC;
    }
}