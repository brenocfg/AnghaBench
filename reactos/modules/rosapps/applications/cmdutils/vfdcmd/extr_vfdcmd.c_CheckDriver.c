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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSG_WRONG_DRIVER ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ) ; 
 scalar_t__ SERVICE_RUNNING ; 
 int VFD_NG ; 
 int VFD_OK ; 
 scalar_t__ VfdCheckDriverFile (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ VfdGetDriverConfig (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ VfdOpenDevice (int /*<<< orphan*/ ) ; 
 scalar_t__ driver_state ; 

int CheckDriver()
{
	char	path[MAX_PATH];
	DWORD	start;

	//	check installed driver file version

	if (VfdGetDriverConfig(path, &start) == ERROR_SUCCESS &&
		VfdCheckDriverFile(path, NULL) == ERROR_SUCCESS) {

		HANDLE hDevice;

		if (driver_state != SERVICE_RUNNING) {
			return VFD_OK;
		}

		//	check running driver version

		hDevice = VfdOpenDevice(0);

		if (hDevice != INVALID_HANDLE_VALUE) {
			CloseHandle(hDevice);
			return VFD_OK;
		}
	}

	PrintMessage(MSG_WRONG_DRIVER);
	return VFD_NG;
}