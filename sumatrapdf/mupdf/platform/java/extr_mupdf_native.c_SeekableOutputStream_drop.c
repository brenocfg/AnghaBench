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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  (* DeleteGlobalRef ) (TYPE_2__**,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  array; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ SeekableStreamState ;
typedef  TYPE_2__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__** jni_attach_thread (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  jni_detach_thread (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SeekableOutputStream_drop(fz_context *ctx, void *streamState_)
{
	SeekableStreamState *state = streamState_;
	JNIEnv *env;
	int detach;

	env = jni_attach_thread(ctx, &detach);
	if (env == NULL) {
		fz_warn(ctx, "cannot attach to JVM in SeekableOutputStream_drop; leaking output stream");
		return;
	}

	(*env)->DeleteGlobalRef(env, state->stream);
	(*env)->DeleteGlobalRef(env, state->array);

	fz_free(ctx, state);

	jni_detach_thread(detach);
}