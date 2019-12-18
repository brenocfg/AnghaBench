#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jclass ;
struct TYPE_6__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* NewGlobalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* FindClass ) (TYPE_1__**,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  LOGI (char*,char const*) ; 
 int /*<<< orphan*/ * current_class ; 
 char const* current_class_name ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,char const*) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static jclass get_class(int *failed, JNIEnv *env, const char *name)
{
	jclass local;

	if (*failed) return NULL;

	current_class_name = name;
	local = (*env)->FindClass(env, name);
	if (!local)
	{
		LOGI("Failed to find class %s", name);
		*failed = 1;
		return NULL;
	}

	current_class = (*env)->NewGlobalRef(env, local);
	if (!current_class)
	{
		LOGI("Failed to make global ref for %s", name);
		*failed = 1;
		return NULL;
	}

	(*env)->DeleteLocalRef(env, local);

	return current_class;
}