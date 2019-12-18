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
typedef  int /*<<< orphan*/ * jmethodID ;
struct TYPE_4__ {int /*<<< orphan*/ * (* GetMethodID ) (TYPE_1__**,int /*<<< orphan*/ ,char const*,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  LOGI (char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  current_class ; 
 int /*<<< orphan*/  current_class_name ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static jmethodID get_method(int *failed, JNIEnv *env, const char *method, const char *sig)
{
	jmethodID mid;

	if (*failed || !current_class) return NULL;

	mid = (*env)->GetMethodID(env, current_class, method, sig);
	if (mid == 0)
	{
		LOGI("Failed to get method for %s %s %s", current_class_name, method, sig);
		*failed = 1;
	}

	return mid;
}