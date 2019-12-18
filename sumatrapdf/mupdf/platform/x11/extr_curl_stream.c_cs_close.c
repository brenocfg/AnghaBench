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
struct curlstate {int kill_thread; struct curlstate* map; struct curlstate* buffer; int /*<<< orphan*/  easy; int /*<<< orphan*/  mutex; int /*<<< orphan*/  thread; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,struct curlstate*) ; 
 int /*<<< orphan*/  lock (struct curlstate*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (struct curlstate*) ; 

__attribute__((used)) static void cs_close(fz_context *ctx, void *state_)
{
	struct curlstate *state = state_;

	lock(state);
	state->kill_thread = 1;
	unlock(state);

#ifdef _WIN32
	WaitForSingleObject(state->thread, INFINITE);
	CloseHandle(state->thread);
	CloseHandle(state->mutex);
#else
	pthread_join(state->thread, NULL);
	pthread_mutex_destroy(&state->mutex);
#endif

	curl_easy_cleanup(state->easy);
	fz_free(ctx, state->buffer);
	fz_free(ctx, state->map);
	fz_free(ctx, state);
}