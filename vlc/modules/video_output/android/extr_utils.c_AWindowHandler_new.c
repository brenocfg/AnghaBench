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

/* Type definitions */
typedef  int /*<<< orphan*/  vout_window_t ;
typedef  void* jobject ;
typedef  int /*<<< orphan*/  jlong ;
typedef  int jint ;
typedef  void* jfloatArray ;
typedef  int /*<<< orphan*/  awh_events_t ;
struct TYPE_20__ {int /*<<< orphan*/  jtransform_mtx_array; int /*<<< orphan*/ * jtransform_mtx; } ;
struct TYPE_19__ {int /*<<< orphan*/  cb; } ;
struct TYPE_22__ {int b_has_video_layout_listener; TYPE_2__ stex; int /*<<< orphan*/  jobj; TYPE_1__ event; int /*<<< orphan*/ * wnd; int /*<<< orphan*/ * p_jvm; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* DeleteGlobalRef ) (TYPE_3__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_3__**,void*) ;int /*<<< orphan*/  (* NewGlobalRef ) (TYPE_3__**,void*) ;int /*<<< orphan*/  (* ExceptionClear ) (TYPE_3__**) ;scalar_t__ (* ExceptionCheck ) (TYPE_3__**) ;void* (* NewFloatArray ) (TYPE_3__**,int) ;} ;
typedef  int /*<<< orphan*/  JavaVM ;
typedef  TYPE_3__* JNIEnv ;
typedef  TYPE_4__ AWindowHandler ;

/* Variables and functions */
 int const AWINDOW_REGISTER_FLAGS_HAS_VIDEO_LAYOUT_LISTENER ; 
 int const AWINDOW_REGISTER_FLAGS_SUCCESS ; 
 int /*<<< orphan*/  CallIntMethod ; 
 scalar_t__ InitJNIFields (TYPE_3__**,int /*<<< orphan*/ ,void*) ; 
 int JNI_ANWCALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadNativeWindowAPI (TYPE_4__*) ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_SUCCESS ; 
 TYPE_3__** android_getEnvCommon (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  registerNative ; 
 int /*<<< orphan*/  stub1 (TYPE_3__**,void*) ; 
 void* stub2 (TYPE_3__**,int) ; 
 scalar_t__ stub3 (TYPE_3__**) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__**) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__**,void*) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__**,void*) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (TYPE_3__**,int /*<<< orphan*/ ) ; 
 void* var_InheritAddress (int /*<<< orphan*/ *,char*) ; 

AWindowHandler *
AWindowHandler_new(vout_window_t *wnd, awh_events_t *p_events)
{
#define AWINDOW_REGISTER_FLAGS_SUCCESS 0x1
#define AWINDOW_REGISTER_FLAGS_HAS_VIDEO_LAYOUT_LISTENER 0x2

    AWindowHandler *p_awh;
    JNIEnv *p_env;
    JavaVM *p_jvm = var_InheritAddress(wnd, "android-jvm");
    jobject jobj = var_InheritAddress(wnd, "drawable-androidwindow");

    if (!p_jvm || !jobj)
    {
        msg_Err(wnd, "libvlc_media_player options not set");
        return NULL;
    }

    p_env = android_getEnvCommon(NULL, p_jvm, "AWindowHandler");
    if (!p_env)
    {
        msg_Err(wnd, "can't get JNIEnv");
        return NULL;
    }

    if (InitJNIFields(p_env, VLC_OBJECT(wnd), jobj) != VLC_SUCCESS)
    {
        msg_Err(wnd, "InitJNIFields failed");
        return NULL;
    }
    msg_Dbg(wnd, "InitJNIFields success");

    p_awh = calloc(1, sizeof(AWindowHandler));
    if (!p_awh)
        return NULL;

    p_awh->p_jvm = p_jvm;
    p_awh->jobj = (*p_env)->NewGlobalRef(p_env, jobj);

    p_awh->wnd = wnd;
    p_awh->event.cb = *p_events;

    jfloatArray jarray = (*p_env)->NewFloatArray(p_env, 16);
    if ((*p_env)->ExceptionCheck(p_env))
    {
        (*p_env)->ExceptionClear(p_env);
        free(p_awh);
        return NULL;
    }
    p_awh->stex.jtransform_mtx_array = (*p_env)->NewGlobalRef(p_env, jarray);
    (*p_env)->DeleteLocalRef(p_env, jarray);
    p_awh->stex.jtransform_mtx = NULL;

    const jint flags = JNI_ANWCALL(CallIntMethod, registerNative,
                                   (jlong)(intptr_t)p_awh);
    if ((flags & AWINDOW_REGISTER_FLAGS_SUCCESS) == 0)
    {
        msg_Err(wnd, "AWindow already registered");
        (*p_env)->DeleteGlobalRef(p_env, p_awh->jobj);
        (*p_env)->DeleteGlobalRef(p_env, p_awh->stex.jtransform_mtx_array);
        free(p_awh);
        return NULL;
    }
    LoadNativeWindowAPI(p_awh);

    p_awh->b_has_video_layout_listener =
        flags & AWINDOW_REGISTER_FLAGS_HAS_VIDEO_LAYOUT_LISTENER;

    return p_awh;
}