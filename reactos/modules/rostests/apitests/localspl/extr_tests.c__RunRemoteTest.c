#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szBuffer ;
typedef  int /*<<< orphan*/  WIN32_FIND_DATAW ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ dwCurrentState; } ;
typedef  TYPE_1__ SERVICE_STATUS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_PIPE_NAME ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConnectNamedPipe (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateNamedPipeW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateServiceW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ERROR_PIPE_CONNECTED ; 
 int /*<<< orphan*/ * ERROR_SERVICE_DOES_NOT_EXIST ; 
 int /*<<< orphan*/  EnumPrintersW (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ExitProcess (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  OUTPUT_PIPE_NAME ; 
 int /*<<< orphan*/ * OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_ACCESS_INBOUND ; 
 int /*<<< orphan*/  PIPE_ACCESS_OUTBOUND ; 
 int PIPE_READMODE_BYTE ; 
 int PIPE_READMODE_MESSAGE ; 
 int PIPE_TYPE_BYTE ; 
 int PIPE_TYPE_MESSAGE ; 
 int PIPE_WAIT ; 
 int PRINTER_ENUM_LOCAL ; 
 int PRINTER_ENUM_NAME ; 
 int /*<<< orphan*/  QueryServiceStatus (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ReadFile (scalar_t__,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SC_MANAGER_ALL_ACCESS ; 
 int /*<<< orphan*/  SERVICE_ALL_ACCESS ; 
 int /*<<< orphan*/  SERVICE_DEMAND_START ; 
 int /*<<< orphan*/  SERVICE_ERROR_IGNORE ; 
 char* SERVICE_NAME ; 
 int /*<<< orphan*/  SERVICE_QUERY_STATUS ; 
 scalar_t__ SERVICE_RUNNING ; 
 int /*<<< orphan*/  SERVICE_WIN32_OWN_PROCESS ; 
 int /*<<< orphan*/  StartServiceW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char const*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcsrchr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
_RunRemoteTest(const char* szTestName)
{
    BOOL bSuccessful = FALSE;
    char szBuffer[1024];
    DWORD cbRead;
    DWORD cbWritten;
    HANDLE hCommandPipe = INVALID_HANDLE_VALUE;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    HANDLE hOutputPipe = INVALID_HANDLE_VALUE;
    PWSTR p;
    SC_HANDLE hSC = NULL;
    SC_HANDLE hService = NULL;
    SERVICE_STATUS ServiceStatus;
    WCHAR wszFilePath[MAX_PATH + 20];
    WIN32_FIND_DATAW fd;

    // Do a dummy EnumPrintersW call.
    // This guarantees that the Spooler Service has actually loaded localspl.dll, which is a requirement for our injected DLL to work properly.
    EnumPrintersW(PRINTER_ENUM_LOCAL | PRINTER_ENUM_NAME, NULL, 1, NULL, 0, &cbRead, &cbWritten);

    // Get the full path to our EXE file.
    if (!GetModuleFileNameW(NULL, wszFilePath, MAX_PATH))
    {
        skip("GetModuleFileNameW failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    // Replace the extension.
    p = wcsrchr(wszFilePath, L'.');
    if (!p)
    {
        skip("File path has no file extension: %S\n", wszFilePath);
        goto Cleanup;
    }

    wcscpy(p, L".dll");

    // Check if the corresponding DLL file exists.
    hFind = FindFirstFileW(wszFilePath, &fd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        skip("My DLL file \"%S\" does not exist!\n", wszFilePath);
        goto Cleanup;
    }

    // Change the extension back to .exe and add the parameters.
    wcscpy(p, L".exe service dummy");

    // Open a handle to the service manager.
    hSC = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!hSC)
    {
        skip("OpenSCManagerW failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    // Ensure that the spooler service is running.
    hService = OpenServiceW(hSC, L"spooler", SERVICE_QUERY_STATUS);
    if (!hService)
    {
        skip("OpenServiceW failed for the spooler service with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    if (!QueryServiceStatus(hService, &ServiceStatus))
    {
        skip("QueryServiceStatus failed for the spooler service with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    if (ServiceStatus.dwCurrentState != SERVICE_RUNNING)
    {
        skip("Spooler Service is not running!\n");
        goto Cleanup;
    }

    CloseServiceHandle(hService);

    // Try to open the service if we've created it in a previous run.
    hService = OpenServiceW(hSC, SERVICE_NAME, SERVICE_ALL_ACCESS);
    if (!hService)
    {
        if (GetLastError() == ERROR_SERVICE_DOES_NOT_EXIST)
        {
            // Create the service.
            hService = CreateServiceW(hSC, SERVICE_NAME, NULL, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, wszFilePath, NULL, NULL, NULL, NULL, NULL);
            if (!hService)
            {
                skip("CreateServiceW failed with error %lu!\n", GetLastError());
                goto Cleanup;
            }
        }
        else
        {
            skip("OpenServiceW failed with error %lu!\n", GetLastError());
            goto Cleanup;
        }
    }

    // Create pipes for the communication with the injected DLL.
    hCommandPipe = CreateNamedPipeW(COMMAND_PIPE_NAME, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 1, 1024, 1024, 10000, NULL);
    if (hCommandPipe == INVALID_HANDLE_VALUE)
    {
        skip("CreateNamedPipeW failed for the command pipe with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    hOutputPipe = CreateNamedPipeW(OUTPUT_PIPE_NAME, PIPE_ACCESS_INBOUND, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 1024, 1024, 10000, NULL);
    if (hOutputPipe == INVALID_HANDLE_VALUE)
    {
        skip("CreateNamedPipeW failed for the output pipe with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    // Start the service with "service" and a dummy parameter (to distinguish it from a call by rosautotest to localspl_apitest:service)
    if (!StartServiceW(hService, 0, NULL))
    {
        skip("StartServiceW failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    // Wait till it has injected the DLL and the DLL expects its test name.
    if (!ConnectNamedPipe(hCommandPipe, NULL) && GetLastError() != ERROR_PIPE_CONNECTED)
    {
        skip("ConnectNamedPipe failed for the command pipe with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    // Send the test name.
    if (!WriteFile(hCommandPipe, szTestName, strlen(szTestName) + sizeof(char), &cbWritten, NULL))
    {
        skip("WriteFile failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    // Now wait for the DLL to connect to the output pipe.
    if (!ConnectNamedPipe(hOutputPipe, NULL))
    {
        skip("ConnectNamedPipe failed for the output pipe with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    // Get all testing messages from the pipe and output them on stdout.
    while (ReadFile(hOutputPipe, szBuffer, sizeof(szBuffer), &cbRead, NULL) && cbRead)
        fwrite(szBuffer, sizeof(char), cbRead, stdout);

    bSuccessful = TRUE;

Cleanup:
    if (hCommandPipe != INVALID_HANDLE_VALUE)
        CloseHandle(hCommandPipe);

    if (hOutputPipe != INVALID_HANDLE_VALUE)
        CloseHandle(hOutputPipe);

    if (hFind != INVALID_HANDLE_VALUE)
        FindClose(hFind);

    if (hService)
        CloseServiceHandle(hService);

    if (hSC)
        CloseServiceHandle(hSC);

    // If we successfully received test output through the named pipe, we have also output a summary line already.
    // Prevent the testing framework from outputting another "0 tests executed" line in this case.
    if (bSuccessful)
        ExitProcess(0);
}