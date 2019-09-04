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
struct event_base {int dummy; } ;

/* Variables and functions */
 struct event_base* event_init () ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

struct event_base *
osdep_event_init(void)
{
	struct event_base	*base;

	/*
	 * On OS X, kqueue and poll are both completely broken and don't
	 * work on anything except socket file descriptors (yes, really).
	 */
	setenv("EVENT_NOKQUEUE", "1", 1);
	setenv("EVENT_NOPOLL", "1", 1);

	base = event_init();
	unsetenv("EVENT_NOKQUEUE");
	unsetenv("EVENT_NOPOLL");
	return (base);
}