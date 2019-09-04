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

/* Variables and functions */
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  event_set_log_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  log_close () ; 
 int /*<<< orphan*/  log_event_cb ; 
 int /*<<< orphan*/ * log_file ; 
 scalar_t__ log_level ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*,long) ; 

void
log_open(const char *name)
{
	char	*path;

	if (log_level == 0)
		return;
	log_close();

	xasprintf(&path, "tmux-%s-%ld.log", name, (long)getpid());
	log_file = fopen(path, "a");
	free(path);
	if (log_file == NULL)
		return;

	setvbuf(log_file, NULL, _IOLBF, 0);
	event_set_log_callback(log_event_cb);
}