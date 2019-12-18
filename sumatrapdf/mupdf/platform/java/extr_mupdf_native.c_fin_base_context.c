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
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int FZ_LOCK_MAX ; 
 int /*<<< orphan*/ * base_context ; 
 int /*<<< orphan*/  fz_drop_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mutexes ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fin_base_context(JNIEnv *env)
{
	int i;

	for (i = 0; i < FZ_LOCK_MAX; i++)
#ifdef _WIN32
		DeleteCriticalSection(&mutexes[i]);
#else
		(void)pthread_mutex_destroy(&mutexes[i]);
#endif

	fz_drop_context(base_context);
	base_context = NULL;
}