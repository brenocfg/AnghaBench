#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ (* GetEnv ) (TYPE_2__**,void**,int /*<<< orphan*/ ) ;scalar_t__ (* AttachCurrentThread ) (TYPE_2__**,int /*<<< orphan*/ **,TYPE_1__*) ;} ;
struct TYPE_6__ {char* name; int /*<<< orphan*/ * group; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ JavaVMAttachArgs ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 scalar_t__ JNI_OK ; 
 int /*<<< orphan*/  JNI_VERSION_1_2 ; 
 TYPE_2__** s_jvm ; 
 scalar_t__ stub1 (TYPE_2__**,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_2__**,int /*<<< orphan*/ **,TYPE_1__*) ; 

__attribute__((used)) static JNIEnv *get_env(bool *p_detach)
{
    JNIEnv *env;
    if ((*s_jvm)->GetEnv(s_jvm, (void **)&env, JNI_VERSION_1_2) != JNI_OK)
    {
        /* attach the thread to the Java VM */
        JavaVMAttachArgs args;

        args.version = JNI_VERSION_1_2;
        args.name = "config_GetGenericDir";
        args.group = NULL;

        if ((*s_jvm)->AttachCurrentThread(s_jvm, &env, &args) != JNI_OK)
            return NULL;
        *p_detach = true;
    }
    else
        *p_detach = false;
    return env;
}