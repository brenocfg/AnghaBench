#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned char* rp; unsigned char* wp; int pos; TYPE_2__* state; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_12__ {int (* CallIntMethod ) (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetByteArrayRegion ) (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ;scalar_t__ (* ExceptionCheck ) (TYPE_3__**) ;} ;
struct TYPE_11__ {scalar_t__ buffer; int /*<<< orphan*/  array; int /*<<< orphan*/  stream; } ;
typedef  TYPE_2__ SeekableStreamState ;
typedef  TYPE_3__* JNIEnv ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_throw_java (int /*<<< orphan*/ *,TYPE_3__**) ; 
 TYPE_3__** jni_attach_thread (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  jni_detach_thread (int) ; 
 int /*<<< orphan*/  mid_SeekableInputStream_read ; 
 int stub1 (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_3__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int SeekableInputStream_next(fz_context *ctx, fz_stream *stm, size_t max)
{
	SeekableStreamState *state = stm->state;
	JNIEnv *env;
	int detach;
	int n, ch;

	env = jni_attach_thread(ctx, &detach);
	if (env == NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot attach to JVM in SeekableInputStream_next");

	n = (*env)->CallIntMethod(env, state->stream, mid_SeekableInputStream_read, state->array);
	if ((*env)->ExceptionCheck(env)) {
		jni_detach_thread(detach);
		fz_throw_java(ctx, env);
	}

	if (n > 0)
	{
		(*env)->GetByteArrayRegion(env, state->array, 0, n, state->buffer);

		/* update stm->pos so fz_tell knows the current position */
		stm->rp = (unsigned char *)state->buffer;
		stm->wp = stm->rp + n;
		stm->pos += n;

		ch = *stm->rp++;
	}
	else if (n < 0)
	{
		ch = EOF;
	}
	else
	{
		jni_detach_thread(detach);
		fz_throw(ctx, FZ_ERROR_GENERIC, "no bytes read");
	}

	jni_detach_thread(detach);
	return ch;
}