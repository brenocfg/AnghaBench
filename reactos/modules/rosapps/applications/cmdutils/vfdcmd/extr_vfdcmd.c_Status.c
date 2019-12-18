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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int HIWORD (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LOWORD (scalar_t__) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSG_ACCESS_NG ; 
 int /*<<< orphan*/  MSG_DRIVER_FILE ; 
 int /*<<< orphan*/  MSG_DRIVER_STATUS ; 
 int /*<<< orphan*/  MSG_DRIVER_VERSION ; 
 int /*<<< orphan*/  MSG_GET_CONFIG_NG ; 
 int /*<<< orphan*/  MSG_GET_VERSION_NG ; 
 int /*<<< orphan*/  MSG_NOT_INSTALLED ; 
 int /*<<< orphan*/  MSG_SHELLEXT_DISABLED ; 
 int /*<<< orphan*/  MSG_SHELLEXT_ENABLED ; 
 int /*<<< orphan*/  MSG_START_AUTO ; 
 int /*<<< orphan*/  MSG_START_BOOT ; 
 int /*<<< orphan*/  MSG_START_DEMAND ; 
 int /*<<< orphan*/  MSG_START_DISABLED ; 
 int /*<<< orphan*/  MSG_START_SYSTEM ; 
 int /*<<< orphan*/  MSG_START_TYPE ; 
 int /*<<< orphan*/  MSG_STATUS_CONT_P ; 
 int /*<<< orphan*/  MSG_STATUS_PAUSED ; 
 int /*<<< orphan*/  MSG_STATUS_PAUSE_P ; 
 int /*<<< orphan*/  MSG_STATUS_RUNNING ; 
 int /*<<< orphan*/  MSG_STATUS_START_P ; 
 int /*<<< orphan*/  MSG_STATUS_STOPPED ; 
 int /*<<< orphan*/  MSG_STATUS_STOP_P ; 
 int /*<<< orphan*/  MSG_UNKNOWN_LONG ; 
 int /*<<< orphan*/  PrintImageInfo (scalar_t__) ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,...) ; 
#define  SERVICE_AUTO_START 139 
#define  SERVICE_BOOT_START 138 
#define  SERVICE_CONTINUE_PENDING 137 
#define  SERVICE_DEMAND_START 136 
#define  SERVICE_DISABLED 135 
#define  SERVICE_PAUSED 134 
#define  SERVICE_PAUSE_PENDING 133 
#define  SERVICE_RUNNING 132 
#define  SERVICE_START_PENDING 131 
#define  SERVICE_STOPPED 130 
#define  SERVICE_STOP_PENDING 129 
#define  SERVICE_SYSTEM_START 128 
 char* SystemError (scalar_t__) ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (char const**) ; 
 int VFD_MAXIMUM_DEVICES ; 
 int VFD_NG ; 
 int VFD_NOT_INSTALLED ; 
 int VFD_OK ; 
 scalar_t__ VfdCheckDriverFile (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ VfdCheckHandlers () ; 
 scalar_t__ VfdGetDriverConfig (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ VfdGetDriverVersion (scalar_t__,scalar_t__*) ; 
 scalar_t__ VfdOpenDevice (int) ; 
 int driver_state ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int	Status(const char **args)
{
	HANDLE	hDevice;
	TCHAR	path[MAX_PATH];
	DWORD	start_type;
	DWORD	version;
	ULONG	target;
	DWORD	ret;

	UNREFERENCED_PARAMETER(args);

	if (driver_state == VFD_NOT_INSTALLED) {
		PrintMessage(MSG_NOT_INSTALLED);
	}
	else {

		//	get current driver config

		ret = VfdGetDriverConfig(path, &start_type);

		if (ret != ERROR_SUCCESS) {
			PrintMessage(MSG_GET_CONFIG_NG);
			printf("%s", SystemError(ret));
			return VFD_NG;
		}

		//	print driver file path

		PrintMessage(MSG_DRIVER_FILE, path);

		//	print driver version
		version = 0;

		if (driver_state == SERVICE_RUNNING) {

			hDevice = VfdOpenDevice(0);

			if (hDevice != INVALID_HANDLE_VALUE) {
				ret = VfdGetDriverVersion(hDevice, &version);

				CloseHandle(hDevice);
			}

		}

		if (version == 0) {
			ret = VfdCheckDriverFile(path, &version);
		}

		if (ret == ERROR_SUCCESS) {
			PrintMessage(MSG_DRIVER_VERSION,
				HIWORD(version) & 0x7fff,
				LOWORD(version),
				(version & 0x80000000) ? "(debug)" : "");
		}
		else {
			PrintMessage(MSG_GET_VERSION_NG);
			printf("%s", SystemError(ret));
		}


		//	print driver start type

		PrintMessage(MSG_START_TYPE);

		switch (start_type) {
		case SERVICE_AUTO_START:
			PrintMessage(MSG_START_AUTO);
			break;

		case SERVICE_BOOT_START:
			PrintMessage(MSG_START_BOOT);
			break;

		case SERVICE_DEMAND_START:
			PrintMessage(MSG_START_DEMAND);
			break;

		case SERVICE_DISABLED:
			PrintMessage(MSG_START_DISABLED);
			break;

		case SERVICE_SYSTEM_START :
			PrintMessage(MSG_START_SYSTEM);
			break;

		default:
			PrintMessage(MSG_UNKNOWN_LONG, start_type);
			break;
		}

		//	print current driver state

		PrintMessage(MSG_DRIVER_STATUS);

		switch (driver_state) {
		case SERVICE_STOPPED:
			PrintMessage(MSG_STATUS_STOPPED);
			break;

		case SERVICE_START_PENDING:
			PrintMessage(MSG_STATUS_START_P);
			break;

		case SERVICE_STOP_PENDING:
			PrintMessage(MSG_STATUS_STOP_P);
			break;

		case SERVICE_RUNNING:
			PrintMessage(MSG_STATUS_RUNNING);
			break;

		case SERVICE_CONTINUE_PENDING:
			PrintMessage(MSG_STATUS_CONT_P);
			break;

		case SERVICE_PAUSE_PENDING:
			PrintMessage(MSG_STATUS_PAUSE_P);
			break;

		case SERVICE_PAUSED:
			PrintMessage(MSG_STATUS_PAUSED);
			break;

		default:
			PrintMessage(MSG_UNKNOWN_LONG, driver_state);
			break;
		}
	}

	//	print shell extension status

	printf("\n");

	if (VfdCheckHandlers() == ERROR_SUCCESS) {
		PrintMessage(MSG_SHELLEXT_ENABLED);
	}
	else {
		PrintMessage(MSG_SHELLEXT_DISABLED);
	}

	//	if driver is not running, no more info

	if (driver_state != SERVICE_RUNNING) {
		return VFD_OK;
	}

	//	print image information

	for (target = 0; target < VFD_MAXIMUM_DEVICES; target++) {
		HANDLE hDevice = VfdOpenDevice(target);

		if (hDevice == INVALID_HANDLE_VALUE) {
			ret = GetLastError();
			PrintMessage(MSG_ACCESS_NG, target + '0');
			printf("%s", SystemError(ret));
			return VFD_NG;
		}

		PrintImageInfo(hDevice);

		CloseHandle(hDevice);
	}

	return VFD_OK;
}