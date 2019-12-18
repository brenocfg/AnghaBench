#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  fz_caught (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_caught_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jni_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jni_rethrow(JNIEnv *env, fz_context *ctx)
{
	jni_throw(env, fz_caught(ctx), fz_caught_message(ctx));
}