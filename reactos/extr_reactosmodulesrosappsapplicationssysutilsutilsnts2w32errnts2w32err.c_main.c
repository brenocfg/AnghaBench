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
typedef  int NTSTATUS ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_MR_MID_NOT_FOUND ; 
 int ERROR_SUCCESS ; 
 int EXIT_SUCCESS ; 
 int RtlNtStatusToDosError (int) ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 

int main (int argc, char * argv [])
{
	NTSTATUS Severity = 0;
	NTSTATUS StatusCode = STATUS_SUCCESS;
	NTSTATUS Status = STATUS_SUCCESS;
	DWORD    LastError = ERROR_SUCCESS;
	DWORD    Maximum = 0x40000;

	if (2 == argc)
	{
		sscanf (argv[1], "%lx", & Maximum);
	}

	printf ("NT error codes 0x0-0x%lx that get translated *not* to ERROR_MR_MID_NOT_FOUND (317)\n\n", Maximum);

	for (	Severity = 0;
		Severity < 4;
		Severity ++)
	{
		printf ("--- Severity %ld ---\n", Severity);

		for (	StatusCode = STATUS_SUCCESS;
			StatusCode <= Maximum ;
			StatusCode ++)
		{
			Status = ((Severity << 30) | StatusCode);
			LastError = RtlNtStatusToDosError (Status);
			if (ERROR_MR_MID_NOT_FOUND != LastError)
			{
				printf ("0x%08lx => %ldL\n", Status, LastError);
			}
		}
	}
	return EXIT_SUCCESS;
}