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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CheckDriver () ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int InputChar (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MSG_ACCESS_NG ; 
 int /*<<< orphan*/  MSG_DUPLICATE_ARGS ; 
 int /*<<< orphan*/  MSG_FORMAT_FORCE ; 
 int /*<<< orphan*/  MSG_FORMAT_NG ; 
 int /*<<< orphan*/  MSG_FORMAT_OK ; 
 int /*<<< orphan*/  MSG_FORMAT_QUIT ; 
 int /*<<< orphan*/  MSG_HINT_FORMAT ; 
 int /*<<< orphan*/  MSG_LOCK_NG ; 
 int /*<<< orphan*/  MSG_NOT_INSTALLED ; 
 int /*<<< orphan*/  MSG_NOT_STARTED ; 
 int /*<<< orphan*/  MSG_RETRY_FORCE_CANCEL ; 
 int /*<<< orphan*/  MSG_TARGET_NOTICE ; 
 int /*<<< orphan*/  MSG_UNKNOWN_OPTION ; 
 int OPERATION_ASK ; 
 int OPERATION_FORCE ; 
 int OPERATION_QUIT ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,...) ; 
 scalar_t__ SERVICE_RUNNING ; 
 char* SystemError (scalar_t__) ; 
 int /*<<< orphan*/  TARGET_NONE ; 
 int TRUE ; 
 int VFD_NG ; 
 scalar_t__ VFD_NOT_INSTALLED ; 
 scalar_t__ VFD_OK ; 
 scalar_t__ VfdDismountVolume (scalar_t__,int) ; 
 scalar_t__ VfdFormatMedia (scalar_t__) ; 
 scalar_t__ VfdGetMediaState (scalar_t__) ; 
 scalar_t__ VfdOpenDevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _stricmp (char const*,char*) ; 
 scalar_t__ driver_state ; 
 int /*<<< orphan*/  help_progname ; 
 scalar_t__ isalnum (char const) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  toupper (char const) ; 

int	Format(const char **args)
{
	int		mode = OPERATION_ASK;
	ULONG	target	= TARGET_NONE;
	HANDLE	hDevice;
	DWORD	ret;

	//	check parameters

	while (args && *args) {

		if (!_stricmp(*args, "/f") ||
			!_stricmp(*args, "/force")) {

			if (mode != OPERATION_ASK) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			mode = OPERATION_FORCE;
		}
		else if (!_stricmp(*args, "/q") ||
			!_stricmp(*args, "/quit")) {

			if (mode != OPERATION_ASK) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			mode = OPERATION_QUIT;
		}
		else if (isalnum(**args)) {
			if (target != TARGET_NONE) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			target = toupper(**args);
		}
		else {
			PrintMessage(MSG_UNKNOWN_OPTION, *args);
			PrintMessage(MSG_HINT_FORMAT, help_progname);
			return VFD_NG;
		}

		args++;
	}

	if (target == TARGET_NONE) {
		target = '0';
		PrintMessage(MSG_TARGET_NOTICE, target);
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

	//	ensure that the driver is running

	if (driver_state != SERVICE_RUNNING) {
		PrintMessage(MSG_NOT_STARTED);
		return VFD_NG;
	}

	//	Open the device

	hDevice = VfdOpenDevice(target);

	if (hDevice == INVALID_HANDLE_VALUE) {
		ret = GetLastError();
		PrintMessage(MSG_ACCESS_NG, target);
		printf("%s", SystemError(ret));
		return VFD_NG;
	}

	//	check if the media is writable

	ret = VfdGetMediaState(hDevice);

	if (ret != ERROR_SUCCESS) {
		PrintMessage(MSG_FORMAT_NG, target);
		printf("%s", SystemError(ret));

		CloseHandle(hDevice);
		return VFD_NG;
	}

	//	format the media

retry:
	ret = VfdDismountVolume(
		hDevice, (mode == OPERATION_FORCE));

	if (ret == ERROR_ACCESS_DENIED) {

		PrintMessage(MSG_LOCK_NG, target);

		if (mode == OPERATION_FORCE) {
			PrintMessage(MSG_FORMAT_FORCE);
		}
		else if (mode == OPERATION_QUIT) {
			PrintMessage(MSG_FORMAT_QUIT);
			CloseHandle(hDevice);
			return VFD_NG;
		}
		else {
			int c = InputChar(MSG_RETRY_FORCE_CANCEL, "rfc");

			if (c == 'r') {			// retry
				goto retry;
			}
			else if (c == 'f') {	//	force
				VfdDismountVolume(hDevice, TRUE);
			}
			else {					//	cancel
				CloseHandle(hDevice);
				return VFD_NG;
			}
		}
	}
	else if (ret != ERROR_SUCCESS) {
		PrintMessage(MSG_LOCK_NG, target);
		CloseHandle(hDevice);
		return VFD_NG;
	}

	ret = VfdFormatMedia(hDevice);

	CloseHandle(hDevice);

	if (ret != ERROR_SUCCESS) {
		PrintMessage(MSG_FORMAT_NG, target);
		printf("%s", SystemError(ret));
		return VFD_NG;
	}

	//	successful operation

	PrintMessage(MSG_FORMAT_OK);

	return VFD_OK;
}