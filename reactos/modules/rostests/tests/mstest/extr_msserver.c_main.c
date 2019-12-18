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
typedef  char* LPTSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  char CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateMailslot (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MAILSLOT_WAIT_FOREVER ; 
 scalar_t__ ReadFile (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char *argv[])
{
   HANDLE hMailslot;
   CHAR chBuf[512];
   BOOL fResult;
   DWORD cbRead;
   LPTSTR lpszMailslotName = "\\\\.\\mailslot\\mymailslot";

   hMailslot = CreateMailslot(lpszMailslotName,
			      512,
			      MAILSLOT_WAIT_FOREVER,
			      NULL);
for (;;)
{
   fResult = ReadFile(hMailslot,
		      chBuf,
		      512,
		      &cbRead,
		      NULL);
   if (fResult == FALSE)
     {
	printf("ReadFile() failed!\n");
	CloseHandle(hMailslot);
	return 0;
     }

   printf("Data read: %s\n", chBuf);
}

   CloseHandle(hMailslot);

   return 0;
}