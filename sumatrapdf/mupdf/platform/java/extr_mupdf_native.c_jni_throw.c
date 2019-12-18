#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* ThrowNew ) (TYPE_1__**,int /*<<< orphan*/ ,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int FZ_ERROR_TRYLATER ; 
 int /*<<< orphan*/  cls_RuntimeException ; 
 int /*<<< orphan*/  cls_TryLaterException ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void jni_throw(JNIEnv *env, int type, const char *mess)
{
	if (type == FZ_ERROR_TRYLATER)
		(*env)->ThrowNew(env, cls_TryLaterException, mess);
	else
		(*env)->ThrowNew(env, cls_RuntimeException, mess);
}