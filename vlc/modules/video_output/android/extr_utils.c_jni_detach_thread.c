#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* GetJavaVM ) (TYPE_2__**,TYPE_1__***) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* DetachCurrentThread ) (TYPE_1__**) ;} ;
typedef  TYPE_1__* JavaVM ;
typedef  TYPE_2__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__**) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,TYPE_1__***) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**) ; 

__attribute__((used)) static void
jni_detach_thread(void *data)
{
    JNIEnv *env = data;
    JavaVM *jvm;

    (*env)->GetJavaVM(env, &jvm);
    assert(jvm);
    (*jvm)->DetachCurrentThread(jvm);
}