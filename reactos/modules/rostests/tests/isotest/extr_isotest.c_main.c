#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_5__ {int QuadPart; TYPE_1__ u; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HexDump (char*,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ ReadBlock (scalar_t__,char*,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ReadFile (scalar_t__,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFilePointer (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 

int main (int argc, char *argv[])
{
  HANDLE hDisk;
  DWORD dwRead;
  char *Buffer;
  CHAR Filename[80];
  LARGE_INTEGER FilePosition;

  if (argc != 2)
    {
      printf("Usage: isotest [Drive:]\n");
      return 0;
    }

  strcpy(Filename, "\\\\.\\");
  strcat(Filename, argv[1]);

  hDisk = CreateFile(Filename,
		     GENERIC_READ,
		     FILE_SHARE_READ | FILE_SHARE_WRITE,
		     NULL,
		     OPEN_EXISTING,
		     0,
		     NULL);
  if (hDisk == INVALID_HANDLE_VALUE)
    {
      printf("CreateFile(): Invalid disk handle!\n");
      return 0;
    }

  Buffer = (char*)malloc(2048);
  if (Buffer == NULL)
    {
      CloseHandle(hDisk);
      printf("Out of memory!\n");
      return 0;
    }
  memset(Buffer, 0, 2048);


  FilePosition.QuadPart = 16 * 2048;
#if 0
  SetLastError(NO_ERROR);
  SetFilePointer(hDisk,
		 FilePosition.u.LowPart,
		 &FilePosition.u.HighPart,
		 FILE_BEGIN);
  if (GetLastError() != NO_ERROR)
    {
      CloseHandle(hDisk);
      free(Buffer);
      printf("SetFilePointer() failed!\n");
      return 0;
    }

  if (ReadFile(hDisk,
	       Buffer,
	       2048,
	       &dwRead,
	       NULL) == FALSE)
    {
      CloseHandle(hDisk);
      free(Buffer);
      printf("ReadFile() failed!\n");
      return 0;
    }
#endif

  if (ReadBlock(hDisk,
		Buffer,
		&FilePosition,
		2048,
		&dwRead) == FALSE)
    {
      CloseHandle(hDisk);
      free(Buffer);
#if 0
      printf("ReadBlock() failed!\n");
#endif
      return 0;
    }

  HexDump(Buffer, 128);

  CloseHandle(hDisk);

  free(Buffer);

  return 0;
}