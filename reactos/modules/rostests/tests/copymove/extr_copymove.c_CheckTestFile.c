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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetFileAttributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int INVALID_FILE_ATTRIBUTES ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
CheckTestFile(LPCTSTR filename, DWORD attributes)
{
	HANDLE file;
	char buffer[4096];
	DWORD read;
	int c;
	DWORD diskattr;

	file = CreateFile(filename,
	                  GENERIC_READ,
	                  0,
	                  NULL,
	                  OPEN_EXISTING,
	                  0,
	                  0);

	if (INVALID_HANDLE_VALUE == file) {
		fprintf(stderr, "CreateFile failed with code %lu\n", GetLastError());
		exit(1);
	}

	if (! ReadFile(file, buffer, sizeof(buffer), &read, NULL)) {
		fprintf(stderr, "ReadFile failed with code %lu\n", GetLastError());
		exit(1);
	}
	if (read != sizeof(buffer)) {
		fprintf(stderr, "Trying to read %u bytes but got %lu bytes\n", sizeof(buffer), read);
		exit(1);
	}
	for(c = 0; c < sizeof(buffer); c++) {
		if (buffer[c] != (char) c) {
			fprintf(stderr, "File contents changed at position %u\n", c);
			exit(1);
		}
	}

	CloseHandle(file);

	diskattr = GetFileAttributes(filename);
	if (INVALID_FILE_ATTRIBUTES == diskattr) {
		fprintf(stderr, "GetFileAttributes failed with code %lu\n", GetLastError());
		exit(1);
	}
	if (diskattr != attributes) {
		fprintf(stderr, "Attribute mismatch, expected 0x%08lx found 0x%08lx\n", attributes, diskattr);
		exit(1);
	}
}