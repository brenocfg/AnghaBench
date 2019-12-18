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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  SetFilePointerEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_RETRIES ; 
 int /*<<< orphan*/  WriteFileWithRetry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL ClearPartition(HANDLE hDrive, LARGE_INTEGER offset, DWORD size)
{
	BOOL r = FALSE;
	uint8_t* buffer = calloc(size, 1);

	if (buffer == NULL)
		return FALSE;

	if (!SetFilePointerEx(hDrive, offset, NULL, FILE_BEGIN)) {
		free(buffer);
		return FALSE;
	}

	r = WriteFileWithRetry(hDrive, buffer, size, &size, WRITE_RETRIES);
	free(buffer);
	return r;
}