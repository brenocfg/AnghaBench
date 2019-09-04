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
typedef  int UINT ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFileMapping (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_MAP_ALL_ACCESS ; 
 int /*<<< orphan*/  FillMemory (int /*<<< orphan*/ *,int,char) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/ * MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 

int main(int argc, char* argv[])
{
  HANDLE hFile;
  HANDLE Section;
  PVOID BaseAddress;

  printf("Section Test\n");

  hFile = CreateFile(_T("sectest.txt"),
		     GENERIC_READ | GENERIC_WRITE,
		     0,
		     NULL,
		     CREATE_ALWAYS,
		     0,
		     0);
  if (hFile == INVALID_HANDLE_VALUE)
    {
      printf("Failed to create file (err=%ld)", GetLastError());
      return 1;
    }

  Section = CreateFileMapping(hFile,
			      NULL,
			      PAGE_READWRITE,
			      0,
			      4096,
			      NULL);
  if (Section == NULL)
    {
      printf("Failed to create section (err=%ld)", GetLastError());
      return 1;
    }

  printf("Mapping view of section\n");
  BaseAddress = MapViewOfFile(Section,
			      FILE_MAP_ALL_ACCESS,
			      0,
			      0,
			      4096);
  printf("BaseAddress %x\n", (UINT) BaseAddress);
  if (BaseAddress == NULL)
    {
      printf("Failed to map section (%ld)\n", GetLastError());
      return 1;
    }

  printf("Clearing section\n");
  FillMemory(BaseAddress, 4096, ' ');
  printf("Copying test data to section\n");
  strcpy(BaseAddress, "test data");

  if (!UnmapViewOfFile(BaseAddress))
    {
      printf("Failed to unmap view of file (%ld)\n", GetLastError());
      return 1;
    }

  if (!CloseHandle(hFile))
    {
      printf("Failed to close file (%ld)\n", GetLastError());
      return 1;
    }

  return 0;
}