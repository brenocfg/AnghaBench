#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
struct TYPE_9__ {int /*<<< orphan*/  hThread; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; } ;
struct TYPE_7__ {int cb; int dwFlags; void* hStdError; void* hStdOutput; int /*<<< orphan*/  wShowWindow; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ SECURITY_ATTRIBUTES ;
typedef  TYPE_3__ PROCESS_INFORMATION ;
typedef  void* HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CREATE_NO_WINDOW ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreatePipe (void**,void**,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  CreateProcessU (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char const*,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  GetExitCodeProcess (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 void* INVALID_HANDLE_VALUE ; 
 int NORMAL_PRIORITY_CLASS ; 
 scalar_t__ PeekNamedPipe (void*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ReadFile (void*,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int STARTF_PREVENTPINNING ; 
 int STARTF_TITLEISAPPID ; 
 int STARTF_USESHOWWINDOW ; 
 int STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_closehandle (void*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

DWORD RunCommand(const char* cmd, const char* dir, BOOL log)
{
	DWORD ret, dwRead, dwAvail, dwPipeSize = 4096;
	STARTUPINFOA si = {0};
	PROCESS_INFORMATION pi = {0};
	SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
	HANDLE hOutputRead = INVALID_HANDLE_VALUE, hOutputWrite = INVALID_HANDLE_VALUE;
	static char* output;

	si.cb = sizeof(si);
	if (log) {
		// NB: The size of a pipe is a suggestion, NOT an absolute guarantee
		// This means that you may get a pipe of 4K even if you requested 1K
		if (!CreatePipe(&hOutputRead, &hOutputWrite, &sa, dwPipeSize)) {
			ret = GetLastError();
			uprintf("Could not set commandline pipe: %s", WindowsErrorString());
			goto out;
		}
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES | STARTF_PREVENTPINNING | STARTF_TITLEISAPPID;
		si.wShowWindow = SW_HIDE;
		si.hStdOutput = hOutputWrite;
		si.hStdError = hOutputWrite;
	}

	if (!CreateProcessU(NULL, cmd, NULL, NULL, TRUE,
		NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, dir, &si, &pi)) {
		ret = GetLastError();
		uprintf("Unable to launch command '%s': %s", cmd, WindowsErrorString());
		goto out;
	}

	if (log) {
		while (1) {
			// coverity[string_null]
			if (PeekNamedPipe(hOutputRead, NULL, dwPipeSize, NULL, &dwAvail, NULL)) {
				if (dwAvail != 0) {
					output = malloc(dwAvail + 1);
					if ((output != NULL) && (ReadFile(hOutputRead, output, dwAvail, &dwRead, NULL)) && (dwRead != 0)) {
						output[dwAvail] = 0;
						// coverity[tainted_string]
						uprintf(output);
					}
					free(output);
				}
			}
			if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0)
				break;
			Sleep(100);
		};
	} else {
		WaitForSingleObject(pi.hProcess, INFINITE);
	}

	if (!GetExitCodeProcess(pi.hProcess, &ret))
		ret = GetLastError();
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

out:
	safe_closehandle(hOutputWrite);
	safe_closehandle(hOutputRead);
	return ret;
}