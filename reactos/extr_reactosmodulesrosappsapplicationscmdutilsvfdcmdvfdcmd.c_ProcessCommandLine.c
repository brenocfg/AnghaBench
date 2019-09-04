#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int max_args; int (* func ) (char const**) ;int /*<<< orphan*/  hint; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 TYPE_1__* Commands ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSG_GET_STAT_NG ; 
 int /*<<< orphan*/  MSG_TOO_MANY_ARGS ; 
 int ParseCommand (char const*) ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ) ; 
 char* SystemError (scalar_t__) ; 
 int VFD_NG ; 
 scalar_t__ VfdGetDriverState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _stricmp (char const*,char*) ; 
 int /*<<< orphan*/  driver_state ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int stub1 (char const**) ; 

int ProcessCommandLine(int argc, const char **args)
{
	int		cmd;
	DWORD	ret;

	//
	//	Decide a command to perform
	//
	cmd = ParseCommand(*args);

	if (cmd < 0) {

		//	no matching command

		return VFD_NG;
	}

	if (*(++args) &&
		(!strcmp(*args, "/?") ||
		!_stricmp(*args, "/h"))) {

		//	print a short hint for the command

		PrintMessage(Commands[cmd].hint);
		return VFD_NG;
	}

	if (--argc > Commands[cmd].max_args) {

		// too many parameters for the command

		PrintMessage(MSG_TOO_MANY_ARGS);
		PrintMessage(Commands[cmd].hint);
		return VFD_NG;
	}

	//	Get the current driver state

	ret = VfdGetDriverState(&driver_state);

	if (ret != ERROR_SUCCESS) {
		PrintMessage(MSG_GET_STAT_NG);
		printf("%s", SystemError(ret));
		return VFD_NG;
	}

	//	Perform the requested operation

	return (*Commands[cmd].func)(args);
}