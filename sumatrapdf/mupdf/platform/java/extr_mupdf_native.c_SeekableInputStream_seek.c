#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {unsigned char* rp; unsigned char* wp; int /*<<< orphan*/  pos; TYPE_2__* state; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_11__ {scalar_t__ (* ExceptionCheck ) (TYPE_3__**) ;int /*<<< orphan*/  (* CallLongMethod ) (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_10__ {scalar_t__ buffer; int /*<<< orphan*/  stream; } ;
typedef  TYPE_2__ SeekableStreamState ;
typedef  TYPE_3__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_throw_java (int /*<<< orphan*/ *,TYPE_3__**) ; 
 TYPE_3__** jni_attach_thread (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  jni_detach_thread (int) ; 
 int /*<<< orphan*/  mid_SeekableStream_seek ; 
 int /*<<< orphan*/  stub1 (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (TYPE_3__**) ; 

__attribute__((used)) static void SeekableInputStream_seek(fz_context *ctx, fz_stream *stm, int64_t offset, int whence)
{
	SeekableStreamState *state = stm->state;
	JNIEnv *env;
	int detach;
	int64_t pos;

	env = jni_attach_thread(ctx, &detach);
	if (env == NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot attach to JVM in SeekableInputStream_seek");

	pos = (*env)->CallLongMethod(env, state->stream, mid_SeekableStream_seek, offset, whence);
	if ((*env)->ExceptionCheck(env)) {
		jni_detach_thread(detach);
		fz_throw_java(ctx, env);
	}

	stm->pos = pos;
	stm->rp = stm->wp = (unsigned char *)state->buffer;

	jni_detach_thread(detach);
}