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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {scalar_t__ (* ExceptionCheck ) (TYPE_2__**) ;int /*<<< orphan*/  (* CallLongMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ SeekableStreamState ;
typedef  TYPE_2__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_throw_java (int /*<<< orphan*/ *,TYPE_2__**) ; 
 TYPE_2__** jni_attach_thread (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  jni_detach_thread (int) ; 
 int /*<<< orphan*/  mid_SeekableStream_position ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_2__**) ; 

__attribute__((used)) static int64_t SeekableOutputStream_tell(fz_context *ctx, void *streamState_)
{
	SeekableStreamState *state = streamState_;
	JNIEnv *env;
	int detach;
	int64_t pos = 0;

	env = jni_attach_thread(ctx, &detach);
	if (env == NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot attach to JVM in SeekableOutputStream_tell");

	pos = (*env)->CallLongMethod(env, state->stream, mid_SeekableStream_position);
	if ((*env)->ExceptionCheck(env)) {
		jni_detach_thread(detach);
		fz_throw_java(ctx, env);
	}

	jni_detach_thread(detach);

	return pos;
}