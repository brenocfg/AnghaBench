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
typedef  char* PCSTR ;
typedef  int KMT_OPERATION ;
typedef  int INT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  KMTEST_DEVICE_PATH ; 
 int KMT_DO_NOTHING ; 
#define  KMT_LIST_ALL_TESTS 130 
#define  KMT_LIST_TESTS 129 
#define  KMT_RUN_TEST 128 
 int /*<<< orphan*/  KmtCloseService (int /*<<< orphan*/ *) ; 
 scalar_t__ KmtCreateAndStartService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ KmtCreateService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ KmtDeleteService (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KmtFreeResultBuffer (scalar_t__) ; 
 scalar_t__ KmtServiceCleanup (int /*<<< orphan*/ ) ; 
 scalar_t__ KmtServiceInit () ; 
 scalar_t__ KmtStartService (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ KmtStopService (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ KmtestHandle ; 
 int /*<<< orphan*/  KmtestServiceHandle ; 
 scalar_t__ ListTests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  OutputError (scalar_t__) ; 
 scalar_t__ ResultBuffer ; 
 scalar_t__ RunTest (char*) ; 
 int /*<<< orphan*/  SERVICE_DESCRIPTION ; 
 int /*<<< orphan*/  SERVICE_NAME ; 
 int /*<<< orphan*/  SERVICE_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  error_goto (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int
main(
    int ArgCount,
    char **Arguments)
{
    INT Status = EXIT_SUCCESS;
    DWORD Error = ERROR_SUCCESS;
    PCSTR AppName = "kmtest.exe";
    PCSTR TestName = NULL;
    KMT_OPERATION Operation = KMT_DO_NOTHING;
    BOOLEAN ShowHidden = FALSE;

    Error = KmtServiceInit();
    if (Error)
        goto cleanup;

    if (ArgCount >= 1)
        AppName = Arguments[0];

    if (ArgCount <= 1)
    {
        printf("Usage: %s <test_name>                 - run the specified test (creates/starts the driver(s) as appropriate)\n", AppName);
        printf("       %s --list                      - list available tests\n", AppName);
        printf("       %s --list-all                  - list available tests, including hidden\n", AppName);
        printf("       %s <create|delete|start|stop>  - manage the kmtest driver\n\n", AppName);
        Operation = KMT_LIST_TESTS;
    }
    else
    {
        TestName = Arguments[1];
        if (!lstrcmpA(TestName, "create"))
            Error = KmtCreateService(SERVICE_NAME, SERVICE_PATH, SERVICE_DESCRIPTION, &KmtestServiceHandle);
        else if (!lstrcmpA(TestName, "delete"))
            Error = KmtDeleteService(SERVICE_NAME, &KmtestServiceHandle);
        else if (!lstrcmpA(TestName, "start"))
            Error = KmtStartService(SERVICE_NAME, &KmtestServiceHandle);
        else if (!lstrcmpA(TestName, "stop"))
            Error = KmtStopService(SERVICE_NAME, &KmtestServiceHandle);

        else if (!lstrcmpA(TestName, "--list"))
            Operation = KMT_LIST_TESTS;
        else if (!lstrcmpA(TestName, "--list-all"))
            Operation = KMT_LIST_ALL_TESTS;
        else
            Operation = KMT_RUN_TEST;
    }

    if (Operation)
    {
        Error = KmtCreateAndStartService(SERVICE_NAME, SERVICE_PATH, SERVICE_DESCRIPTION, &KmtestServiceHandle, FALSE);
        if (Error)
            goto cleanup;

        KmtestHandle = CreateFile(KMTEST_DEVICE_PATH, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (KmtestHandle == INVALID_HANDLE_VALUE)
            error_goto(Error, cleanup);

        switch (Operation)
        {
            case KMT_LIST_ALL_TESTS:
                ShowHidden = TRUE;
                /* fall through */
            case KMT_LIST_TESTS:
                Error = ListTests(ShowHidden);
                break;
            case KMT_RUN_TEST:
                Error = RunTest(TestName);
                break;
            default:
                assert(FALSE);
        }
    }

cleanup:
    if (KmtestHandle)
        CloseHandle(KmtestHandle);

    if (ResultBuffer)
        KmtFreeResultBuffer(ResultBuffer);

    KmtCloseService(&KmtestServiceHandle);

    if (Error)
        KmtServiceCleanup(TRUE);
    else
        Error = KmtServiceCleanup(FALSE);

    if (Error)
    {
        OutputError(Error);

        Status = EXIT_FAILURE;
    }

    return Status;
}