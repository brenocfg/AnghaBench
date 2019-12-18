#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ae_nvl; int /*<<< orphan*/  ae_subclass; int /*<<< orphan*/  ae_class; } ;
typedef  TYPE_1__ agent_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  agent_cond ; 
 int /*<<< orphan*/  agent_events ; 
 scalar_t__ agent_exiting ; 
 int /*<<< orphan*/  agent_lock ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 scalar_t__ list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_agent_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
zfs_agent_consumer_thread(void *arg)
{
	for (;;) {
		agent_event_t *event;

		(void) pthread_mutex_lock(&agent_lock);

		/* wait for an event to show up */
		while (!agent_exiting && list_is_empty(&agent_events))
			(void) pthread_cond_wait(&agent_cond, &agent_lock);

		if (agent_exiting) {
			(void) pthread_mutex_unlock(&agent_lock);
			zed_log_msg(LOG_INFO, "zfs_agent_consumer_thread: "
			    "exiting");
			return (NULL);
		}

		if ((event = (list_head(&agent_events))) != NULL) {
			list_remove(&agent_events, event);

			(void) pthread_mutex_unlock(&agent_lock);

			/* dispatch to all event subscribers */
			zfs_agent_dispatch(event->ae_class, event->ae_subclass,
			    event->ae_nvl);

			nvlist_free(event->ae_nvl);
			free(event);
			continue;
		}

		(void) pthread_mutex_unlock(&agent_lock);
	}

	return (NULL);
}