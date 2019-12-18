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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSG_DRIVE_LETTER ; 
 int /*<<< orphan*/  MSG_EPHEMERAL ; 
 int /*<<< orphan*/  MSG_PERSISTENT ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VfdGetGlobalLink (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ VfdGetLocalLink (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ isalpha (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  toupper (int /*<<< orphan*/ ) ; 

void PrintDriveLetter(
	HANDLE			hDevice,
	ULONG			nDrive)
{
	CHAR			letter;

	PrintMessage(MSG_DRIVE_LETTER, nDrive);

	VfdGetGlobalLink(hDevice, &letter);

	if (isalpha(letter)) {
		PrintMessage(MSG_PERSISTENT, toupper(letter));
	}

	while (VfdGetLocalLink(hDevice, &letter) == ERROR_SUCCESS &&
		isalpha(letter)) {
		PrintMessage(MSG_EPHEMERAL, toupper(letter));
	}

	printf("\n");
}