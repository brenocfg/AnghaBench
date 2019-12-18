#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int (* GetEnv ) (TYPE_1__**,void*,int /*<<< orphan*/ ) ;int (* AttachCurrentThread ) (TYPE_1__**,void*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int JNI_EDETACHED ; 
 int JNI_OK ; 
 int /*<<< orphan*/  MY_JNI_VERSION ; 
 TYPE_1__** jvm ; 
 int stub1 (TYPE_1__**,void*,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_1__**,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static JNIEnv *jni_attach_thread(fz_context *ctx, int *detach)
{
	JNIEnv *env = NULL;
	int state;

	*detach = 0;
	state = (*jvm)->GetEnv(jvm, (void*)&env, MY_JNI_VERSION);
	if (state == JNI_EDETACHED)
	{
		*detach = 1;
		state = (*jvm)->AttachCurrentThread(jvm, (void*)&env, NULL);
	}

	if (state != JNI_OK)
		return NULL;

	return env;
}