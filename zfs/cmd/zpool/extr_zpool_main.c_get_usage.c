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
typedef  int zpool_help_t ;

/* Variables and functions */
#define  HELP_ADD 159 
#define  HELP_ATTACH 158 
#define  HELP_CHECKPOINT 157 
#define  HELP_CLEAR 156 
#define  HELP_CREATE 155 
#define  HELP_DESTROY 154 
#define  HELP_DETACH 153 
#define  HELP_EVENTS 152 
#define  HELP_EXPORT 151 
#define  HELP_GET 150 
#define  HELP_HISTORY 149 
#define  HELP_IMPORT 148 
#define  HELP_INITIALIZE 147 
#define  HELP_IOSTAT 146 
#define  HELP_LABELCLEAR 145 
#define  HELP_LIST 144 
#define  HELP_OFFLINE 143 
#define  HELP_ONLINE 142 
#define  HELP_REGUID 141 
#define  HELP_REMOVE 140 
#define  HELP_REOPEN 139 
#define  HELP_REPLACE 138 
#define  HELP_RESILVER 137 
#define  HELP_SCRUB 136 
#define  HELP_SET 135 
#define  HELP_SPLIT 134 
#define  HELP_STATUS 133 
#define  HELP_SYNC 132 
#define  HELP_TRIM 131 
#define  HELP_UPGRADE 130 
#define  HELP_VERSION 129 
#define  HELP_WAIT 128 
 int /*<<< orphan*/  abort () ; 
 char const* gettext (char*) ; 

__attribute__((used)) static const char *
get_usage(zpool_help_t idx)
{
	switch (idx) {
	case HELP_ADD:
		return (gettext("\tadd [-fgLnP] [-o property=value] "
		    "<pool> <vdev> ...\n"));
	case HELP_ATTACH:
		return (gettext("\tattach [-fw] [-o property=value] "
		    "<pool> <device> <new-device>\n"));
	case HELP_CLEAR:
		return (gettext("\tclear [-nF] <pool> [device]\n"));
	case HELP_CREATE:
		return (gettext("\tcreate [-fnd] [-o property=value] ... \n"
		    "\t    [-O file-system-property=value] ... \n"
		    "\t    [-m mountpoint] [-R root] <pool> <vdev> ...\n"));
	case HELP_CHECKPOINT:
		return (gettext("\tcheckpoint [-d [-w]] <pool> ...\n"));
	case HELP_DESTROY:
		return (gettext("\tdestroy [-f] <pool>\n"));
	case HELP_DETACH:
		return (gettext("\tdetach <pool> <device>\n"));
	case HELP_EXPORT:
		return (gettext("\texport [-af] <pool> ...\n"));
	case HELP_HISTORY:
		return (gettext("\thistory [-il] [<pool>] ...\n"));
	case HELP_IMPORT:
		return (gettext("\timport [-d dir] [-D]\n"
		    "\timport [-o mntopts] [-o property=value] ... \n"
		    "\t    [-d dir | -c cachefile] [-D] [-l] [-f] [-m] [-N] "
		    "[-R root] [-F [-n]] -a\n"
		    "\timport [-o mntopts] [-o property=value] ... \n"
		    "\t    [-d dir | -c cachefile] [-D] [-l] [-f] [-m] [-N] "
		    "[-R root] [-F [-n]]\n"
		    "\t    [--rewind-to-checkpoint] <pool | id> [newpool]\n"));
	case HELP_IOSTAT:
		return (gettext("\tiostat [[[-c [script1,script2,...]"
		    "[-lq]]|[-rw]] [-T d | u] [-ghHLpPvy]\n"
		    "\t    [[pool ...]|[pool vdev ...]|[vdev ...]]"
		    " [[-n] interval [count]]\n"));
	case HELP_LABELCLEAR:
		return (gettext("\tlabelclear [-f] <vdev>\n"));
	case HELP_LIST:
		return (gettext("\tlist [-gHLpPv] [-o property[,...]] "
		    "[-T d|u] [pool] ... \n"
		    "\t    [interval [count]]\n"));
	case HELP_OFFLINE:
		return (gettext("\toffline [-f] [-t] <pool> <device> ...\n"));
	case HELP_ONLINE:
		return (gettext("\tonline [-e] <pool> <device> ...\n"));
	case HELP_REPLACE:
		return (gettext("\treplace [-fw] [-o property=value] "
		    "<pool> <device> [new-device]\n"));
	case HELP_REMOVE:
		return (gettext("\tremove [-npsw] <pool> <device> ...\n"));
	case HELP_REOPEN:
		return (gettext("\treopen [-n] <pool>\n"));
	case HELP_INITIALIZE:
		return (gettext("\tinitialize [-c | -s] [-w] <pool> "
		    "[<device> ...]\n"));
	case HELP_SCRUB:
		return (gettext("\tscrub [-s | -p] [-w] <pool> ...\n"));
	case HELP_RESILVER:
		return (gettext("\tresilver <pool> ...\n"));
	case HELP_TRIM:
		return (gettext("\ttrim [-d] [-r <rate>] [-c | -s] <pool> "
		    "[<device> ...]\n"));
	case HELP_STATUS:
		return (gettext("\tstatus [-c [script1,script2,...]] "
		    "[-igLpPstvxD]  [-T d|u] [pool] ... \n"
		    "\t    [interval [count]]\n"));
	case HELP_UPGRADE:
		return (gettext("\tupgrade\n"
		    "\tupgrade -v\n"
		    "\tupgrade [-V version] <-a | pool ...>\n"));
	case HELP_EVENTS:
		return (gettext("\tevents [-vHf [pool] | -c]\n"));
	case HELP_GET:
		return (gettext("\tget [-Hp] [-o \"all\" | field[,...]] "
		    "<\"all\" | property[,...]> <pool> ...\n"));
	case HELP_SET:
		return (gettext("\tset <property=value> <pool> \n"));
	case HELP_SPLIT:
		return (gettext("\tsplit [-gLnPl] [-R altroot] [-o mntopts]\n"
		    "\t    [-o property=value] <pool> <newpool> "
		    "[<device> ...]\n"));
	case HELP_REGUID:
		return (gettext("\treguid <pool>\n"));
	case HELP_SYNC:
		return (gettext("\tsync [pool] ...\n"));
	case HELP_VERSION:
		return (gettext("\tversion\n"));
	case HELP_WAIT:
		return (gettext("\twait [-Hp] [-T d|u] [-t <activity>[,...]] "
		    "<pool> [interval]\n"));
	}

	abort();
	/* NOTREACHED */
}