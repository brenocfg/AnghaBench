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
typedef  int ULONG ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPSECURITY_ATTRIBUTES ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (char*) ; 

int main(int argc, char *argv[])
{
   HANDLE hMailslot;
   LPSTR lpszMailslotName = "\\\\.\\MAILSLOT\\mymailslot";
   LPSTR lpszTestMessage = "Mailslot test message!";
   DWORD cbLength, cbWritten;

   hMailslot = CreateFile(lpszMailslotName,
			  GENERIC_WRITE,
			  FILE_SHARE_READ,
			  (LPSECURITY_ATTRIBUTES)NULL,
			  OPEN_EXISTING,
			  FILE_ATTRIBUTE_NORMAL,
			  (HANDLE)NULL);
   printf("hMailslot %x\n", (DWORD)hMailslot);
   if (hMailslot == INVALID_HANDLE_VALUE)
     {
	printf("CreateFile() failed\n");
	return 0;
     }

   cbLength = (ULONG)strlen(lpszTestMessage)+1;

   WriteFile(hMailslot,
	     lpszTestMessage,
	     cbLength,
	     &cbWritten,
	     NULL);

   CloseHandle(hMailslot);

   return 0;
}