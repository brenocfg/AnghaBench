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
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CheckDriver () ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_WRITE_PROTECT ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MSG_ACCESS_NG ; 
 int /*<<< orphan*/  MSG_DUPLICATE_ARGS ; 
 int /*<<< orphan*/  MSG_GET_MEDIA_NG ; 
 int /*<<< orphan*/  MSG_HINT_PROTECT ; 
 int /*<<< orphan*/  MSG_MEDIA_PROTECTED ; 
 int /*<<< orphan*/  MSG_MEDIA_WRITABLE ; 
 int /*<<< orphan*/  MSG_NOT_INSTALLED ; 
 int /*<<< orphan*/  MSG_NOT_STARTED ; 
 int /*<<< orphan*/  MSG_PROTECT_NG ; 
 int /*<<< orphan*/  MSG_TARGET_NOTICE ; 
 int /*<<< orphan*/  MSG_UNKNOWN_OPTION ; 
 scalar_t__ PROTECT_NONE ; 
 scalar_t__ PROTECT_OFF ; 
 scalar_t__ PROTECT_ON ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,...) ; 
 scalar_t__ SERVICE_RUNNING ; 
 char* SystemError (scalar_t__) ; 
 scalar_t__ TARGET_NONE ; 
 int VFD_NG ; 
 scalar_t__ VFD_NOT_INSTALLED ; 
 scalar_t__ VFD_OK ; 
 scalar_t__ VfdGetMediaState (scalar_t__) ; 
 scalar_t__ VfdOpenDevice (scalar_t__) ; 
 scalar_t__ VfdWriteProtect (scalar_t__,int) ; 
 scalar_t__ _stricmp (char const*,char*) ; 
 scalar_t__ driver_state ; 
 int /*<<< orphan*/  help_progname ; 
 scalar_t__ isalnum (char const) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ toupper (char const) ; 

int	Protect(const char **args)
{
#define PROTECT_NONE	0
#define PROTECT_ON		1
#define PROTECT_OFF		2
	ULONG	protect	= PROTECT_NONE;
	ULONG	target	= TARGET_NONE;
	HANDLE	hDevice;
	DWORD	ret;

	//	check parameters

	while (args && *args) {

		//	Disk type options

		if (_stricmp(*args, "/on") == 0) {

			if (protect) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			protect = PROTECT_ON;
		}
		else if (_stricmp(*args, "/off") == 0) {

			if (protect) {
				PrintMessage(MSG_DUPLICATE_ARGS, *args);
				return VFD_NG;
			}

			protect = PROTECT_OFF;
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
			PrintMessage(MSG_HINT_PROTECT, help_progname);
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

	//	open the target drive

	hDevice = VfdOpenDevice(target);

	if (hDevice == INVALID_HANDLE_VALUE) {
		ret = GetLastError();
		PrintMessage(MSG_ACCESS_NG, target);
		printf("%s", SystemError(ret));
		return VFD_NG;
	}

	if (protect) {
		//	change protect state

		ret = VfdWriteProtect(
			hDevice, (protect == PROTECT_ON));

		if (ret != ERROR_SUCCESS) {
			PrintMessage(MSG_PROTECT_NG, target);
			printf("%s", SystemError(ret));

			CloseHandle(hDevice);
			return VFD_NG;
		}
	}

	//	get the current protect state

	ret = VfdGetMediaState(hDevice);

	CloseHandle(hDevice);

	if (ret == ERROR_SUCCESS) {
		PrintMessage(MSG_MEDIA_WRITABLE);
	}
	else if (ret == ERROR_WRITE_PROTECT) {
		PrintMessage(MSG_MEDIA_PROTECTED);
	}
	else {
		PrintMessage(MSG_GET_MEDIA_NG);
		printf("%s", SystemError(ret));
		return VFD_NG;
	}

	return VFD_OK;
}