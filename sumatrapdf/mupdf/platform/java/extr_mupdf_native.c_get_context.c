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
 scalar_t__ TlsGetValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TlsSetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base_context ; 
 int /*<<< orphan*/  context_key ; 
 int /*<<< orphan*/ * fz_clone_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jni_throw_oom (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fz_context *get_context(JNIEnv *env)
{
	fz_context *ctx = (fz_context *)
#ifdef _WIN32
		TlsGetValue(context_key);
#else
		pthread_getspecific(context_key);
#endif

	if (ctx)
		return ctx;

	ctx = fz_clone_context(base_context);
	if (!ctx) { jni_throw_oom(env, "failed to clone fz_context"); return NULL; }

#ifdef _WIN32
	TlsSetValue(context_key, ctx);
#else
	pthread_setspecific(context_key, ctx);
#endif
	return ctx;
}