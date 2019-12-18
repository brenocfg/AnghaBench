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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteTestFile (int /*<<< orphan*/ ) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetFileAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
CreateTestFile(LPCTSTR filename, DWORD attributes)
{
	HANDLE file;
	char buffer[4096];
	DWORD wrote;
	int c;

	DeleteTestFile(filename);
	file = CreateFile(filename,
	                  GENERIC_READ | GENERIC_WRITE,
	                  0,
	                  NULL,
	                  CREATE_ALWAYS,
	                  0,
	                  0);

	if (INVALID_HANDLE_VALUE == file) {
		fprintf(stderr, "CreateFile failed with code %lu\n", GetLastError());
		exit(1);
	}
	for(c = 0; c < sizeof(buffer); c++) {
		buffer[c] = (char) c;
	}
	if (! WriteFile(file, buffer, sizeof(buffer), &wrote, NULL)) {
		fprintf(stderr, "WriteFile failed with code %lu\n", GetLastError());
		exit(1);
	}
	CloseHandle(file);

	if (! SetFileAttributes(filename, attributes)) {
		fprintf(stderr, "SetFileAttributes failed with code %lu\n", GetLastError());
		exit(1);
	}
}