#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {scalar_t__ (* GetEnv ) (TYPE_2__**,void**,int /*<<< orphan*/ ) ;scalar_t__ (* AttachCurrentThread ) (TYPE_2__**,int /*<<< orphan*/ **,TYPE_1__*) ;int /*<<< orphan*/  (* DetachCurrentThread ) (TYPE_2__**) ;} ;
struct TYPE_9__ {char const* name; int /*<<< orphan*/ * group; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ JavaVMAttachArgs ;
typedef  TYPE_2__* JavaVM ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 scalar_t__ JNI_OK ; 
 int /*<<< orphan*/  JNI_VERSION_1_2 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jni_env_key ; 
 int /*<<< orphan*/  jni_env_key_create ; 
 int /*<<< orphan*/  jni_env_key_once ; 
 int /*<<< orphan*/ * pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_setspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__**,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_2__**,int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**) ; 
 TYPE_2__** var_InheritAddress (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static JNIEnv *
android_getEnvCommon(vlc_object_t *p_obj, JavaVM *jvm, const char *psz_name)
{
    assert((p_obj && !jvm) || (!p_obj && jvm));

    JNIEnv *env;

    pthread_once(&jni_env_key_once, jni_env_key_create);
    env = pthread_getspecific(jni_env_key);
    if (env == NULL)
    {
        if (!jvm)
            jvm = var_InheritAddress(p_obj, "android-jvm");

        if (!jvm)
            return NULL;

        /* if GetEnv returns JNI_OK, the thread is already attached to the
         * JavaVM, so we are already in a java thread, and we don't have to
         * setup any destroy callbacks */
        if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_2) != JNI_OK)
        {
            /* attach the thread to the Java VM */
            JavaVMAttachArgs args;

            args.version = JNI_VERSION_1_2;
            args.name = psz_name;
            args.group = NULL;

            if ((*jvm)->AttachCurrentThread(jvm, &env, &args) != JNI_OK)
                return NULL;

            /* Set the attached env to the thread-specific data area (TSD) */
            if (pthread_setspecific(jni_env_key, env) != 0)
            {
                (*jvm)->DetachCurrentThread(jvm);
                return NULL;
            }
        }
    }

    return env;
}