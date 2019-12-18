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
 scalar_t__ Install (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ALREADY_RUNNING ; 
 int /*<<< orphan*/  MSG_START_NG ; 
 int /*<<< orphan*/  MSG_START_OK ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ) ; 
 scalar_t__ SERVICE_RUNNING ; 
 char* SystemError (scalar_t__) ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (char const**) ; 
 int VFD_NG ; 
 scalar_t__ VFD_NOT_INSTALLED ; 
 scalar_t__ VFD_OK ; 
 scalar_t__ VfdStartDriver (scalar_t__*) ; 
 scalar_t__ driver_state ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int	Start(const char **args)
{
	DWORD	ret;

	UNREFERENCED_PARAMETER(args);

	//	ensure that the driver is installed

	if (driver_state == VFD_NOT_INSTALLED &&
		Install(NULL) != VFD_OK) {
		return VFD_NG;
	}

	//	ensure that the driver is up to date

	if (CheckDriver() != VFD_OK) {
		return VFD_NG;
	}

	//	ensure that the driver is not running

	if (driver_state == SERVICE_RUNNING) {
		PrintMessage(MSG_ALREADY_RUNNING);
		return VFD_NG;
	}

	//	start the driver

	ret = VfdStartDriver(&driver_state);

	if (ret != ERROR_SUCCESS) {
		PrintMessage(MSG_START_NG);
		printf("%s", SystemError(ret));
		return VFD_NG;
	}

	//	operation successfull

	PrintMessage(MSG_START_OK);

	return VFD_OK;
}