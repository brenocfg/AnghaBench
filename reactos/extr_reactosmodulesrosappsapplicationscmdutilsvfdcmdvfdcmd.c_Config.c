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
 scalar_t__ CheckDriver () ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSG_CONFIG_NG ; 
 int /*<<< orphan*/  MSG_CONFIG_OK ; 
 int /*<<< orphan*/  MSG_DUPLICATE_ARGS ; 
 int /*<<< orphan*/  MSG_HINT_CONFIG ; 
 int /*<<< orphan*/  MSG_NOT_INSTALLED ; 
 int /*<<< orphan*/  MSG_UNKNOWN_OPTION ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,...) ; 
 scalar_t__ SERVICE_AUTO_START ; 
 scalar_t__ SERVICE_DEMAND_START ; 
 scalar_t__ SERVICE_DISABLED ; 
 char* SystemError (scalar_t__) ; 
 int VFD_NG ; 
 scalar_t__ VFD_NOT_INSTALLED ; 
 scalar_t__ VFD_OK ; 
 scalar_t__ VfdConfigDriver (scalar_t__) ; 
 int /*<<< orphan*/  _stricmp (char const*,char*) ; 
 scalar_t__ driver_state ; 
 int /*<<< orphan*/  help_progname ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int	Config(const char **args)
{
	DWORD	start_type = SERVICE_DISABLED;
	DWORD	ret;

	while (args && *args) {
		if (!_stricmp(*args, "/a") ||
			!_stricmp(*args, "/auto")) {

			if (start_type != SERVICE_DISABLED) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			start_type = SERVICE_AUTO_START;
		}
		else if (!_stricmp(*args, "/m") ||
			!_stricmp(*args, "/manual")) {

			if (start_type != SERVICE_DISABLED) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			start_type = SERVICE_DEMAND_START;
		}
		else {
			PrintMessage(MSG_UNKNOWN_OPTION, *args);
			PrintMessage(MSG_HINT_CONFIG, help_progname);
			return VFD_NG;
		}

		args++;
	}

	if (start_type == SERVICE_DISABLED) {
		//	no parameter is specified
		PrintMessage(MSG_HINT_CONFIG, help_progname);
		return VFD_NG;
	}

	//	ensure that the driver is installed

	if (driver_state == VFD_NOT_INSTALLED) {
		PrintMessage(MSG_NOT_INSTALLED);
		return VFD_NG;
	}

	//	ensure that the driver is up to date

	if (CheckDriver() != VFD_OK) {
		return VFD_NG;
	}

	//	configure the driver

	ret = VfdConfigDriver(start_type);

	if (ret != ERROR_SUCCESS) {
		PrintMessage(MSG_CONFIG_NG);
		printf("%s", SystemError(ret));
		return VFD_NG;
	}

	//	operation successfull

	PrintMessage(MSG_CONFIG_OK);

	return VFD_OK;
}