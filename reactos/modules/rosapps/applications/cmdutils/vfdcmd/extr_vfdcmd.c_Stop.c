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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ Close (char const**) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int InputChar (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MSG_DUPLICATE_ARGS ; 
 int /*<<< orphan*/  MSG_HINT_STOP ; 
 int /*<<< orphan*/  MSG_NOT_INSTALLED ; 
 int /*<<< orphan*/  MSG_NOT_STARTED ; 
 int /*<<< orphan*/  MSG_RETRY_FORCE_CANCEL ; 
 int /*<<< orphan*/  MSG_STOP_FORCE ; 
 int /*<<< orphan*/  MSG_STOP_NG ; 
 int /*<<< orphan*/  MSG_STOP_OK ; 
 int /*<<< orphan*/  MSG_STOP_PENDING ; 
 int /*<<< orphan*/  MSG_STOP_QUIT ; 
 int /*<<< orphan*/  MSG_STOP_WARN ; 
 int /*<<< orphan*/  MSG_UNKNOWN_OPTION ; 
 int OPERATION_ASK ; 
 int OPERATION_FORCE ; 
 int OPERATION_QUIT ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,...) ; 
 scalar_t__ SERVICE_RUNNING ; 
 scalar_t__ SERVICE_STOPPED ; 
 char* SystemError (scalar_t__) ; 
 int VFD_NG ; 
 scalar_t__ VFD_NOT_INSTALLED ; 
 scalar_t__ VFD_OK ; 
 scalar_t__ VfdStopDriver (scalar_t__*) ; 
 int /*<<< orphan*/  _stricmp (char const*,char*) ; 
 scalar_t__ driver_state ; 
 int /*<<< orphan*/  help_progname ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int	Stop(const char **args)
{
	int			mode = OPERATION_ASK;
	const char	*close_params[] = { "*", NULL, NULL };
	DWORD		ret;

	while (args && *args) {
		if (!_stricmp(*args, "/f") ||
			!_stricmp(*args, "/force")) {

			if (mode != OPERATION_ASK) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			mode = OPERATION_FORCE;

			//	parameter to pass to the Close() function
			close_params[1] = *args;
		}
		else if (!_stricmp(*args, "/q") ||
			!_stricmp(*args, "/quit")) {

			if (mode != OPERATION_ASK) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			mode = OPERATION_QUIT;

			//	parameter to pass to the Close() function
			close_params[1] = *args;
		}
		else {
			PrintMessage(MSG_UNKNOWN_OPTION, *args);
			PrintMessage(MSG_HINT_STOP, help_progname);
			return VFD_NG;
		}

		args++;
	}

	//	ensure that the driver is installed

	if (driver_state == VFD_NOT_INSTALLED) {
		PrintMessage(MSG_NOT_INSTALLED);
		return VFD_NG;
	}

	//	ensure that the driver is running

	if (driver_state == SERVICE_STOPPED) {
		PrintMessage(MSG_NOT_STARTED);
		return VFD_NG;
	}

	//	ensure that all drives are empty

	if (driver_state == SERVICE_RUNNING) {

		//	Try to close drives with the same operation mode (/F or /Q)

		while (Close(close_params) != VFD_OK) {

			//	close failed

			if (mode == OPERATION_FORCE) {
				PrintMessage(MSG_STOP_FORCE);
				break;
			}
			else if (mode == OPERATION_QUIT) {
				PrintMessage(MSG_STOP_QUIT);
				return VFD_NG;
			}
			else {
				int c;

				PrintMessage(MSG_STOP_WARN);

				c = InputChar(MSG_RETRY_FORCE_CANCEL, "rfc");

				if (c == 'f') {			//	force
					break;
				}
				else if (c == 'c') {	//	cancel
					return VFD_NG;
				}
			}
		}
	}

	//	stop the driver

	ret = VfdStopDriver(&driver_state);

	if (ret != ERROR_SUCCESS) {
		PrintMessage(MSG_STOP_NG);
		printf("%s", SystemError(ret));
		return VFD_NG;
	}

	if (driver_state != SERVICE_STOPPED) {
		PrintMessage(MSG_STOP_PENDING);
		return VFD_NG;
	}

	//	operation successful

	PrintMessage(MSG_STOP_OK);

	return VFD_OK;
}