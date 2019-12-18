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
struct utsname {char const* sysname; long release; int /*<<< orphan*/  version; } ;
struct tmuxproc {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_VERSION ; 
 int /*<<< orphan*/  VERSION ; 
 int /*<<< orphan*/  event_get_method () ; 
 int /*<<< orphan*/  event_get_version () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  log_debug (char*,char const*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_open (char const*) ; 
 int /*<<< orphan*/  memset (struct utsname*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setproctitle (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_path ; 
 scalar_t__ uname (struct utsname*) ; 
 struct tmuxproc* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

struct tmuxproc *
proc_start(const char *name)
{
	struct tmuxproc	*tp;
	struct utsname	 u;

	log_open(name);
	setproctitle("%s (%s)", name, socket_path);

	if (uname(&u) < 0)
		memset(&u, 0, sizeof u);

	log_debug("%s started (%ld): version %s, socket %s, protocol %d", name,
	    (long)getpid(), VERSION, socket_path, PROTOCOL_VERSION);
	log_debug("on %s %s %s; libevent %s (%s)", u.sysname, u.release,
	    u.version, event_get_version(), event_get_method());

	tp = xcalloc(1, sizeof *tp);
	tp->name = xstrdup(name);

	return (tp);
}