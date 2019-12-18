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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  LPTHREAD_START_ROUTINE ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ ConnectNamedPipe (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateNamedPipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DisconnectNamedPipe (scalar_t__) ; 
 scalar_t__ ERROR_PIPE_CONNECTED ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ InstanceThread ; 
 int /*<<< orphan*/  MyErrExit (char*) ; 
 int /*<<< orphan*/  PIPE_ACCESS_DUPLEX ; 
 int PIPE_READMODE_MESSAGE ; 
 int /*<<< orphan*/  PIPE_TIMEOUT ; 
 int PIPE_TYPE_MESSAGE ; 
 int /*<<< orphan*/  PIPE_UNLIMITED_INSTANCES ; 
 int PIPE_WAIT ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char *argv[])
{
   BOOL fConnected;
   DWORD dwThreadId;
   HANDLE hPipe, hThread;
   LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");

//   for (;;)
//     {
	hPipe = CreateNamedPipe(lpszPipename,
				PIPE_ACCESS_DUPLEX,
				PIPE_TYPE_MESSAGE |
				PIPE_READMODE_MESSAGE |
				PIPE_WAIT,
				PIPE_UNLIMITED_INSTANCES,
				BUFSIZE,
				BUFSIZE,
				PIPE_TIMEOUT,
				NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	  {
	     printf("CreateNamedPipe() failed\n");
	     return 0;
	  }

	fConnected = ConnectNamedPipe(hPipe,
				      NULL) ? TRUE : (GetLastError () ==
					    ERROR_PIPE_CONNECTED);
	if (fConnected)
	  {
	     printf("Pipe connected!\n");

	     DisconnectNamedPipe(hPipe);

#if 0
	     hThread = CreateThread(NULL,
				    0,
				    (LPTHREAD_START_ROUTINE) InstanceThread,
				    (LPVOID) hPipe,
				    0,
				    &dwThreadId);
	     if (hThread == NULL)
	       MyErrExit("CreateThread");
#endif
	  }
	else
	  {
//	     CloseHandle(hPipe);
	  }
//     }

   CloseHandle(hPipe);

   return 0;
}