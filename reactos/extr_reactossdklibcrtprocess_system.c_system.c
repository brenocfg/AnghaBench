#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hProcess; scalar_t__ hThread; } ;
struct TYPE_6__ {int cb; scalar_t__ cbReserved2; int /*<<< orphan*/ * lpReserved2; int /*<<< orphan*/  wShowWindow; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/ * lpReserved; } ;
typedef  int /*<<< orphan*/  StartupInfo ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW_PROCESS_GROUP ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateProcessA (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  STARTF_USESHOWWINDOW ; 
 int /*<<< orphan*/  SW_SHOWDEFAULT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cwait (int*,intptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dosmaperr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* malloc (scalar_t__) ; 
 char* max (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char*,char) ; 

int system(const char *command)
{
  char *szCmdLine = NULL;
  char *szComSpec = NULL;

  PROCESS_INFORMATION ProcessInformation;
  STARTUPINFOA StartupInfo;
  char *s;
  BOOL result;

  int nStatus;

  szComSpec = getenv("COMSPEC");

// system should return 0 if command is null and the shell is found

  if (command == NULL) {
    if (szComSpec == NULL)
      return 0;
    else
      return 1;
  }

  if (szComSpec == NULL)
    return -1;

// should return 127 or 0 ( MS ) if the shell is not found
// _set_errno(ENOENT);

  if (szComSpec == NULL)
  {
    szComSpec = "cmd.exe";
  }

  /* split the path from shell command */
  s = max(strrchr(szComSpec, '\\'), strrchr(szComSpec, '/'));
  if (s == NULL)
    s = szComSpec;
  else
    s++;

  szCmdLine = malloc(strlen(s) + 4 + strlen(command) + 1);
  if (szCmdLine == NULL)
  {
     _set_errno(ENOMEM);
     return -1;
  }

  strcpy(szCmdLine, s);
  s = strrchr(szCmdLine, '.');
  if (s)
    *s = 0;
  strcat(szCmdLine, " /C ");
  strcat(szCmdLine, command);

//command file has invalid format ENOEXEC

  memset (&StartupInfo, 0, sizeof(StartupInfo));
  StartupInfo.cb = sizeof(StartupInfo);
  StartupInfo.lpReserved= NULL;
  StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
  StartupInfo.wShowWindow = SW_SHOWDEFAULT;
  StartupInfo.lpReserved2 = NULL;
  StartupInfo.cbReserved2 = 0;

// According to ansi standards the new process should ignore  SIGINT and SIGQUIT
// In order to disable ctr-c the process is created with CREATE_NEW_PROCESS_GROUP,
// thus SetConsoleCtrlHandler(NULL,TRUE) is made on behalf of the new process.


//SIGCHILD should be blocked aswell

  result = CreateProcessA(szComSpec,
	                  szCmdLine,
			  NULL,
			  NULL,
			  TRUE,
			  CREATE_NEW_PROCESS_GROUP,
			  NULL,
			  NULL,
			  &StartupInfo,
			  &ProcessInformation);
  free(szCmdLine);

  if (result == FALSE)
  {
	_dosmaperr(GetLastError());
     return -1;
  }

  CloseHandle(ProcessInformation.hThread);

// system should wait untill the calling process is finished
  _cwait(&nStatus,(intptr_t)ProcessInformation.hProcess,0);
  CloseHandle(ProcessInformation.hProcess);

  return nStatus;
}