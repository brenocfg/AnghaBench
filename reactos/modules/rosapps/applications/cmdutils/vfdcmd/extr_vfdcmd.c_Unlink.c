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
typedef  int ULONG ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ CheckDriver () ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MSG_ACCESS_NG ; 
 int /*<<< orphan*/  MSG_DUPLICATE_ARGS ; 
 int /*<<< orphan*/  MSG_HINT_ULINK ; 
 int /*<<< orphan*/  MSG_NOT_INSTALLED ; 
 int /*<<< orphan*/  MSG_NOT_STARTED ; 
 int /*<<< orphan*/  MSG_TARGET_NOTICE ; 
 int /*<<< orphan*/  MSG_UNKNOWN_OPTION ; 
 int /*<<< orphan*/  PrintDriveLetter (scalar_t__,int) ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,...) ; 
 scalar_t__ SERVICE_RUNNING ; 
 char* SystemError (int /*<<< orphan*/ ) ; 
 int TARGET_NONE ; 
 int VFD_MAXIMUM_DEVICES ; 
 int VFD_NG ; 
 scalar_t__ VFD_NOT_INSTALLED ; 
 scalar_t__ VFD_OK ; 
 int /*<<< orphan*/  VfdGetDeviceNumber (scalar_t__,int*) ; 
 scalar_t__ VfdOpenDevice (int) ; 
 int /*<<< orphan*/  VfdSetGlobalLink (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VfdSetLocalLink (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ driver_state ; 
 int help_progname ; 
 scalar_t__ isalnum (char const) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int Unlink(const char **args)
{
	ULONG	target_min = TARGET_NONE;
	ULONG	target_max = TARGET_NONE;
	HANDLE	hDevice;
	DWORD	ret;

	while (args && *args) {
		if ((isalnum(**args) || **args == '*') &&
			(*(*args + 1) == ':' || *(*args + 1) == '\0')) {

			if (target_min != TARGET_NONE) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			if (**args == '*') {
				target_min = '0';
				target_max = '0' + VFD_MAXIMUM_DEVICES;
			}
			else {
				target_min = **args;
				target_max = target_min + 1;
			}
		}
		else {
			PrintMessage(MSG_UNKNOWN_OPTION, *args);
			PrintMessage(MSG_HINT_ULINK, help_progname);
			return VFD_NG;
		}

		args++;
	}

	if (target_min == TARGET_NONE) {
		// default: drive 0
		target_min = '0';
		target_max = '1';
		PrintMessage(MSG_TARGET_NOTICE, target_min);
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

	while (target_min < target_max) {
		ULONG number;

		hDevice = VfdOpenDevice(target_min);

		if (hDevice == INVALID_HANDLE_VALUE) {
			ret = GetLastError();
			PrintMessage(MSG_ACCESS_NG, target_min);
			printf("%s", SystemError(ret));
			target_min++;
			continue;
		}

		ret = VfdGetDeviceNumber(hDevice, &number);

		if (ret != ERROR_SUCCESS) {
			PrintMessage(MSG_ACCESS_NG, target_min);
			printf("%s", SystemError(ret));
			CloseHandle(hDevice);
			target_min++;
			continue;
		}

		VfdSetGlobalLink(hDevice, 0);
		VfdSetLocalLink(hDevice, 0);

		PrintDriveLetter(hDevice, number);

		CloseHandle(hDevice);

		target_min++;
	}

	return VFD_OK;
}