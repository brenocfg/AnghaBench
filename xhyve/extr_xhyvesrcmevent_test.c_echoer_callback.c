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
struct esync {int /*<<< orphan*/  e_mt; int /*<<< orphan*/  e_cond; } ;
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
echoer_callback(int fd, enum ev_type type, void *param)
{
	struct esync *sync = param;

	pthread_mutex_lock(&sync->e_mt);
	pthread_cond_signal(&sync->e_cond);
	pthread_mutex_unlock(&sync->e_mt);
}