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
typedef  int /*<<< orphan*/  display ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateServiceA (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  DELETE ; 
 int DeleteService (int /*<<< orphan*/ *) ; 
 char* ERROR_ACCESS_DENIED ; 
 char* ERROR_DUPLICATE_SERVICE_NAME ; 
 char* ERROR_INVALID_ADDRESS ; 
 char* ERROR_INVALID_HANDLE ; 
 char* ERROR_INVALID_NAME ; 
 char* ERROR_INVALID_PARAMETER ; 
 char* ERROR_INVALID_SERVICE_ACCOUNT ; 
 char* ERROR_SERVICE_EXISTS ; 
 int FALSE ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetEnvironmentVariableA (char*,char*,int) ; 
 char* GetLastError () ; 
 int GetServiceDisplayNameA (int /*<<< orphan*/ *,char const*,char*,int*) ; 
 int /*<<< orphan*/  GetUserNameA (char*,int*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * OpenSCManagerA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceA (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SC_MANAGER_CREATE_SERVICE ; 
 int SERVICE_AUTO_START ; 
 int SERVICE_BOOT_START ; 
 int SERVICE_DISABLED ; 
 int SERVICE_FILE_SYSTEM_DRIVER ; 
 int SERVICE_INTERACTIVE_PROCESS ; 
 int SERVICE_KERNEL_DRIVER ; 
 int SERVICE_WIN32_OWN_PROCESS ; 
 int SERVICE_WIN32_SHARE_PROCESS ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int TRUE ; 
 int UNLEN ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 char const* spooler ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 

__attribute__((used)) static void test_create_delete_svc(void)
{
    SC_HANDLE scm_handle, svc_handle1, svc_handle2;
    CHAR username[UNLEN + 1], domain[MAX_PATH];
    DWORD user_size = UNLEN + 1;
    CHAR account[UNLEN + 3];
    static const CHAR servicename         [] = "Winetest";
    static const CHAR pathname            [] = "we_dont_care.exe";
    static const CHAR empty               [] = "";
    static const CHAR password            [] = "secret";
    BOOL spooler_exists = FALSE;
    BOOL ret;
    CHAR display[4096];
    DWORD display_size = sizeof(display);

    /* Get the username and turn it into an account to be used in some tests */
    GetUserNameA(username, &user_size);
    /* Get the domainname to cater for that situation */
    if (GetEnvironmentVariableA("USERDOMAIN", domain, MAX_PATH))
        sprintf(account, "%s\\%s", domain, username);
    else
        sprintf(account, ".\\%s", username);

    /* All NULL */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    scm_handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);

    /* Only a valid handle to the Service Control Manager */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_ADDRESS   /* W2K, W2K3, XP, Vista */ ||
       GetLastError() == ERROR_INVALID_PARAMETER /* NT4 */,
       "Expected ERROR_INVALID_ADDRESS or ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Now with a servicename */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_ADDRESS   /* W2K, W2K3, XP, Vista */ ||
       GetLastError() == ERROR_INVALID_PARAMETER /* NT4 */,
       "Expected ERROR_INVALID_ADDRESS or ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Or just a binary name */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, NULL, NULL, 0, 0, 0, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_ADDRESS   /* W2K, W2K3, XP, Vista */ ||
       GetLastError() == ERROR_INVALID_PARAMETER /* NT4 */,
       "Expected ERROR_INVALID_ADDRESS or ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Both servicename and binary name (We only have connect rights) */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, 0, 0, 0, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_ACCESS_DENIED, "Expected ERROR_ACCESS_DENIED, got %d\n", GetLastError());

    /* They can even be empty at this stage of parameter checking */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, empty, NULL, 0, 0, 0, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_ACCESS_DENIED, "Expected ERROR_ACCESS_DENIED, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, 0, 0, 0, 0, empty, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_ACCESS_DENIED, "Expected ERROR_ACCESS_DENIED, got %d\n", GetLastError());

    /* Open the Service Control Manager with minimal rights for creation
     * (Verified with 'SC_MANAGER_ALL_ACCESS &~ SC_MANAGER_CREATE_SERVICE')
     */
    CloseServiceHandle(scm_handle);
    SetLastError(0xdeadbeef);
    scm_handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (!scm_handle && (GetLastError() == ERROR_ACCESS_DENIED))
    {
        skip("Not enough rights to get a handle to the manager\n");
        return;
    }

    /* TODO: It looks like account (ServiceStartName) and (maybe) password are checked at this place */

    /* Empty strings for servicename and binary name are checked */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, empty, NULL, 0, 0, 0, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_NAME, "Expected ERROR_INVALID_NAME, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, 0, 0, 0, 0, empty, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, empty, NULL, 0, 0, 0, 0, empty, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_NAME, "Expected ERROR_INVALID_NAME, got %d\n", GetLastError());

    /* Valid call (as we will see later) except for the empty binary name (to proof it's indeed
     * an ERROR_INVALID_PARAMETER)
     */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, 0, SERVICE_WIN32_OWN_PROCESS,
                                 SERVICE_DISABLED, 0, empty, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Windows checks if the 'service type', 'access type' and the combination of them are valid, so let's test that */

    /* Illegal (service-type, which is used as a mask can't have a mix. Except the one with
     * SERVICE_INTERACTIVE_PROCESS which will be tested below in a valid call)
     */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, GENERIC_ALL, SERVICE_WIN32_OWN_PROCESS | SERVICE_WIN32_SHARE_PROCESS,
                                 SERVICE_DISABLED, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Illegal (SERVICE_INTERACTIVE_PROCESS is only allowed with SERVICE_WIN32_OWN_PROCESS or SERVICE_WIN32_SHARE_PROCESS) */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, GENERIC_ALL, SERVICE_FILE_SYSTEM_DRIVER | SERVICE_INTERACTIVE_PROCESS,
                                 SERVICE_DISABLED, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Illegal (this combination is only allowed when the LocalSystem account (ServiceStartName) is used)
     * Not having a correct account would have resulted in an ERROR_INVALID_SERVICE_ACCOUNT.
     */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, GENERIC_ALL, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
                                 SERVICE_DISABLED, 0, pathname, NULL, NULL, NULL, account, password);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER || GetLastError() == ERROR_INVALID_SERVICE_ACCOUNT,
       "Expected ERROR_INVALID_PARAMETER or ERROR_INVALID_SERVICE_ACCOUNT, got %d\n", GetLastError());

    /* Illegal (start-type is not a mask and should only be one of the possibilities)
     * Remark : 'OR'-ing them could result in a valid possibility (but doesn't make sense as
     * it's most likely not the wanted start-type)
     */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, GENERIC_ALL, SERVICE_WIN32_OWN_PROCESS,
                                 SERVICE_AUTO_START | SERVICE_DISABLED, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Illegal (SERVICE_BOOT_START and SERVICE_SYSTEM_START are only allowed for driver services) */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, 0, SERVICE_WIN32_OWN_PROCESS,
                                 SERVICE_BOOT_START, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Test if ServiceType can be a combined one for drivers */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, 0, SERVICE_KERNEL_DRIVER | SERVICE_FILE_SYSTEM_DRIVER,
                                 SERVICE_BOOT_START, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(!svc_handle1, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* The service already exists (check first, just in case) */
    svc_handle1 = OpenServiceA(scm_handle, spooler, GENERIC_READ);
    if (svc_handle1)
    {
        spooler_exists = TRUE;
        CloseServiceHandle(svc_handle1);
        SetLastError(0xdeadbeef);
        svc_handle1 = CreateServiceA(scm_handle, spooler, NULL, 0, SERVICE_WIN32_OWN_PROCESS,
                                     SERVICE_DISABLED, 0, pathname, NULL, NULL, NULL, NULL, NULL);
        ok(!svc_handle1, "Expected failure\n");
        ok(GetLastError() == ERROR_SERVICE_EXISTS, "Expected ERROR_SERVICE_EXISTS, got %d\n", GetLastError());
    }
    else
        skip("Spooler service doesn't exist\n");

    /* To find an existing displayname we check the 'Spooler' service. Although the registry
     * doesn't show DisplayName on NT4, this call will return a displayname which is equal
     * to the servicename and can't be used as well for a new displayname.
     */
    if (spooler_exists)
    {
        ret = GetServiceDisplayNameA(scm_handle, spooler, display, &display_size);

        if (!ret)
            skip("Could not retrieve a displayname for the Spooler service\n");
        else
        {
            svc_handle1 = CreateServiceA(scm_handle, servicename, display, 0, SERVICE_WIN32_OWN_PROCESS,
                                         SERVICE_DISABLED, 0, pathname, NULL, NULL, NULL, NULL, NULL);
            ok(!svc_handle1, "Expected failure for display name '%s'\n", display);
            ok(GetLastError() == ERROR_DUPLICATE_SERVICE_NAME,
               "Expected ERROR_DUPLICATE_SERVICE_NAME, got %d\n", GetLastError());
        }
    }
    else
        skip("Could not retrieve a displayname (Spooler service doesn't exist)\n");

    /* Windows doesn't care about the access rights for creation (which makes
     * sense as there is no service yet) as long as there are sufficient
     * rights to the manager.
     */
    SetLastError(0xdeadbeef);
    svc_handle1 = CreateServiceA(scm_handle, servicename, NULL, 0, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
                                 SERVICE_DISABLED, 0, pathname, NULL, NULL, NULL, NULL, NULL);
    ok(svc_handle1 != NULL, "Could not create the service : %d\n", GetLastError());

    /* DeleteService however must have proper rights */
    SetLastError(0xdeadbeef);
    ret = DeleteService(svc_handle1);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_ACCESS_DENIED,
       "Expected ERROR_ACCESS_DENIED, got %d\n", GetLastError());

    /* Open the service with minimal rights for deletion.
     * (Verified with 'SERVICE_ALL_ACCESS &~ DELETE')
     */
    CloseServiceHandle(svc_handle1);
    svc_handle1 = OpenServiceA(scm_handle, servicename, DELETE);

    /* Now that we have the proper rights, we should be able to delete */
    SetLastError(0xdeadbeef);
    ret = DeleteService(svc_handle1);
    ok(ret, "Expected success, got error %u\n", GetLastError());

    /* Service is marked for delete, but handle is still open. Try to open service again. */
    svc_handle2 = OpenServiceA(scm_handle, servicename, GENERIC_READ);
    ok(svc_handle2 != NULL, "got %p, error %u\n", svc_handle2, GetLastError());
    CloseServiceHandle(svc_handle2);

    CloseServiceHandle(svc_handle1);
    CloseServiceHandle(scm_handle);

    /* Wait a while. One of the following tests also does a CreateService for the
     * same servicename and this would result in an ERROR_SERVICE_MARKED_FOR_DELETE
     * error if we do this too quickly. Vista seems more picky than the others.
     */
    Sleep(1000);

    /* And a final NULL check */
    SetLastError(0xdeadbeef);
    ret = DeleteService(NULL);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE,
        "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());
}