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
typedef  char const* PCSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CheckDriver () ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MSG_ACCESS_NG ; 
 int /*<<< orphan*/  MSG_DUPLICATE_ARGS ; 
 int /*<<< orphan*/  MSG_HINT_LINK ; 
 int /*<<< orphan*/  MSG_LINK_FULL ; 
 int /*<<< orphan*/  MSG_LINK_NG ; 
 int /*<<< orphan*/  MSG_NOT_INSTALLED ; 
 int /*<<< orphan*/  MSG_NOT_STARTED ; 
 int /*<<< orphan*/  MSG_TARGET_NOTICE ; 
 int /*<<< orphan*/  MSG_UNKNOWN_OPTION ; 
 int /*<<< orphan*/  PrintDriveLetter (scalar_t__,int) ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,...) ; 
 scalar_t__ SERVICE_RUNNING ; 
 char* SystemError (int /*<<< orphan*/ ) ; 
 int TARGET_NONE ; 
 scalar_t__ TRUE ; 
 int VFD_MAXIMUM_DEVICES ; 
 int VFD_NG ; 
 scalar_t__ VFD_NOT_INSTALLED ; 
 scalar_t__ VFD_OK ; 
 scalar_t__ VfdChooseLetter () ; 
 int /*<<< orphan*/  VfdGetDeviceNumber (scalar_t__,int*) ; 
 scalar_t__ VfdOpenDevice (int) ; 
 int /*<<< orphan*/  VfdSetGlobalLink (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VfdSetLocalLink (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _stricmp (char const*,char*) ; 
 scalar_t__ driver_state ; 
 int /*<<< orphan*/  help_progname ; 
 scalar_t__ isalpha (char const) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ toupper (int /*<<< orphan*/ ) ; 

int Link(const char **args)
{
	ULONG	target_min = TARGET_NONE;
	ULONG	target_max = TARGET_NONE;
	PCSTR	letters = NULL;
	BOOL	global	= TRUE;
	HANDLE	hDevice;
	DWORD	ret;

	while (args && *args) {
		if (!_stricmp(*args, "/g")) {
			global = TRUE;
		}
		else if (!_stricmp(*args, "/l")) {
			global = FALSE;
		}
		else if (isdigit(**args) || **args == '*') {
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
		else if (isalpha(**args)) {
			if (letters) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}
			letters = *args;
		}
		else {
			PrintMessage(MSG_UNKNOWN_OPTION, *args);
			PrintMessage(MSG_HINT_LINK, help_progname);
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
		CHAR letter;

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

		if (letters && isalpha(*letters)) {
			letter = (CHAR)toupper(*(letters++));
		}
		else {
			letter = VfdChooseLetter();
		}

		if (letter) {
			if (global) {
				ret = VfdSetGlobalLink(hDevice, letter);
			}
			else {
				ret = VfdSetLocalLink(hDevice, letter);
			}

			if (ret != ERROR_SUCCESS) {
				PrintMessage(MSG_LINK_NG, number, letter);
				printf("%s", SystemError(ret));
			}
		}
		else {
			PrintMessage(MSG_LINK_FULL);
		}

		PrintDriveLetter(hDevice, number);

		CloseHandle(hDevice);

		target_min++;
	}

	return VFD_OK;
}