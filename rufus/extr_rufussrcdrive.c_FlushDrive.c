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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateFileA (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 scalar_t__ FlushFileBuffers (scalar_t__) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 
 int /*<<< orphan*/  uprintf (char*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL FlushDrive(char drive_letter)
{
	HANDLE hDrive = INVALID_HANDLE_VALUE;
	BOOL r = FALSE;
	char logical_drive[] = "\\\\.\\#:";

	logical_drive[4] = drive_letter;
	hDrive = CreateFileA(logical_drive, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDrive == INVALID_HANDLE_VALUE) {
		uprintf("Failed to open %c: for flushing: %s", drive_letter, WindowsErrorString());
		goto out;
	}
	r = FlushFileBuffers(hDrive);
	if (r == FALSE)
		uprintf("Failed to flush %c: %s", drive_letter, WindowsErrorString());

out:
	safe_closehandle(hDrive);
	return r;
}