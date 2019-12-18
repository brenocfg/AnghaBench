#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/ * jfieldID ;
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_14__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ ) ;scalar_t__ (* GetIntField ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ExceptionClear ) (TYPE_1__**) ;scalar_t__ (* ExceptionCheck ) (TYPE_1__**) ;int /*<<< orphan*/ * (* GetFieldID ) (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  (* GetObjectClass ) (TYPE_1__**,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub10 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**) ; 
 int /*<<< orphan*/ * stub4 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ stub5 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__**) ; 
 int /*<<< orphan*/ * stub7 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ stub8 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__**) ; 

__attribute__((used)) static void *
NativeSurface_getHandle(JNIEnv *p_env, jobject jsurf)
{
    jclass clz;
    jfieldID fid;
    intptr_t p_surface_handle = 0;

    clz = (*p_env)->GetObjectClass(p_env, jsurf);
    if ((*p_env)->ExceptionCheck(p_env))
    {
        (*p_env)->ExceptionClear(p_env);
        return NULL;
    }
    fid = (*p_env)->GetFieldID(p_env, clz, "mSurface", "I");
    if (fid == NULL)
    {
        if ((*p_env)->ExceptionCheck(p_env))
            (*p_env)->ExceptionClear(p_env);
        fid = (*p_env)->GetFieldID(p_env, clz, "mNativeSurface", "I");
        if (fid == NULL)
        {
            if ((*p_env)->ExceptionCheck(p_env))
                (*p_env)->ExceptionClear(p_env);
        }
    }
    if (fid != NULL)
        p_surface_handle = (intptr_t)(*p_env)->GetIntField(p_env, jsurf, fid);
    (*p_env)->DeleteLocalRef(p_env, clz);

    return (void *)p_surface_handle;
}