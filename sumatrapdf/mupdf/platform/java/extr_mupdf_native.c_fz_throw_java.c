#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ jthrowable ;
typedef  scalar_t__ jobject ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_10__ {char* (* GetStringUTFChars ) (TYPE_1__**,scalar_t__,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ReleaseStringUTFChars ) (TYPE_1__**,scalar_t__,char const*) ;int /*<<< orphan*/  (* ExceptionClear ) (TYPE_1__**) ;scalar_t__ (* ExceptionCheck ) (TYPE_1__**) ;scalar_t__ (* CallObjectMethod ) (TYPE_1__**,scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ (* ExceptionOccurred ) (TYPE_1__**) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mid_Object_toString ; 
 scalar_t__ stub1 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**) ; 
 scalar_t__ stub3 (TYPE_1__**,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__**) ; 
 char* stub6 (TYPE_1__**,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__**,scalar_t__,char const*) ; 

__attribute__((used)) static void fz_throw_java(fz_context *ctx, JNIEnv *env)
{
	jthrowable ex = (*env)->ExceptionOccurred(env);
	if (ex)
	{
		jobject msg;
		(*env)->ExceptionClear(env);
		msg = (*env)->CallObjectMethod(env, ex, mid_Object_toString);
		if ((*env)->ExceptionCheck(env))
			(*env)->ExceptionClear(env);
		else if (msg)
		{
			const char *p = (*env)->GetStringUTFChars(env, msg, NULL);
			if (p)
			{
				char buf[256];
				fz_strlcpy(buf, p, sizeof buf);
				(*env)->ReleaseStringUTFChars(env, msg, p);
				fz_throw(ctx, FZ_ERROR_GENERIC, "%s", buf);
			}
		}
	}
	fz_throw(ctx, FZ_ERROR_GENERIC, "unknown java error");
}