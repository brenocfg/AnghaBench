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
struct window_mode_entry {int dummy; } ;
struct session {int dummy; } ;
struct job {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_NOWAIT ; 
 int /*<<< orphan*/  bufferevent_write (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  job_get_event (struct job*) ; 
 struct job* job_run (char const*,struct session*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_copy_copy_buffer (struct window_mode_entry*,char const*,void*,size_t) ; 
 void* window_copy_get_selection (struct window_mode_entry*,size_t*) ; 

__attribute__((used)) static void
window_copy_copy_pipe(struct window_mode_entry *wme, struct session *s,
    const char *prefix, const char *command)
{
	void		*buf;
	size_t		 len;
	struct job	*job;

	buf = window_copy_get_selection(wme, &len);
	if (buf == NULL)
		return;

	job = job_run(command, s, NULL, NULL, NULL, NULL, NULL, JOB_NOWAIT);
	bufferevent_write(job_get_event(job), buf, len);
	window_copy_copy_buffer(wme, prefix, buf, len);
}