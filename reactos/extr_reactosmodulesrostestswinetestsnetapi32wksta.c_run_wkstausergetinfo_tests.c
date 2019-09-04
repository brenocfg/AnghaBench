#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WKSTA_USER_INFO_1101 ;
typedef  int /*<<< orphan*/  WKSTA_USER_INFO_1 ;
typedef  int /*<<< orphan*/  WKSTA_USER_INFO_0 ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  wkui1101_oth_domains; int /*<<< orphan*/  wkui1_oth_domains; int /*<<< orphan*/  wkui1_logon_server; int /*<<< orphan*/  wkui1_logon_domain; int /*<<< orphan*/  wkui1_username; int /*<<< orphan*/  wkui0_username; } ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  TYPE_1__* LPWKSTA_USER_INFO_1101 ;
typedef  TYPE_1__* LPWKSTA_USER_INFO_1 ;
typedef  TYPE_1__* LPWKSTA_USER_INFO_0 ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_LEVEL ; 
 scalar_t__ NERR_Success ; 
 scalar_t__ NERR_WkstaNotStarted ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pNetApiBufferFree (TYPE_1__*) ; 
 int /*<<< orphan*/  pNetApiBufferSize (TYPE_1__*,int*) ; 
 scalar_t__ pNetWkstaUserGetInfo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  user_name ; 

__attribute__((used)) static void run_wkstausergetinfo_tests(void)
{
    LPWKSTA_USER_INFO_0 ui0 = NULL;
    LPWKSTA_USER_INFO_1 ui1 = NULL;
    LPWKSTA_USER_INFO_1101 ui1101 = NULL;
    DWORD dwSize;
    NET_API_STATUS rc;

    /* Level 0 */
    rc = pNetWkstaUserGetInfo(NULL, 0, (LPBYTE *)&ui0);
    if (rc == NERR_WkstaNotStarted)
    {
        skip("Workstation service not running\n");
        return;
    }
    ok(!rc && ui0, "got %d and %p (expected NERR_Success and != NULL\n", rc, ui0);

    /* This failure occurred when I ran sshd as service and didn't authenticate
     * Since the test dereferences ui0, the rest of this test is worthless
     */
    if (!ui0)
    {
        return;
    }

    ok(!lstrcmpW(user_name, ui0->wkui0_username), "This is really user name\n");
    pNetApiBufferSize(ui0, &dwSize);
    ok(dwSize >= (sizeof(WKSTA_USER_INFO_0) +
                 lstrlenW(ui0->wkui0_username) * sizeof(WCHAR)),
       "Is allocated with NetApiBufferAllocate\n");

    /* Level 1 */
    ok(pNetWkstaUserGetInfo(NULL, 1, (LPBYTE *)&ui1) == NERR_Success,
       "NetWkstaUserGetInfo is successful\n");
    ok(lstrcmpW(ui1->wkui1_username, ui0->wkui0_username) == 0,
       "the same name as returned for level 0\n");
    pNetApiBufferSize(ui1, &dwSize);
    ok(dwSize >= (sizeof(WKSTA_USER_INFO_1) +
                  (lstrlenW(ui1->wkui1_username) +
                   lstrlenW(ui1->wkui1_logon_domain) +
                   lstrlenW(ui1->wkui1_oth_domains) +
                   lstrlenW(ui1->wkui1_logon_server)) * sizeof(WCHAR)),
       "Is allocated with NetApiBufferAllocate\n");

    /* Level 1101 */
    ok(pNetWkstaUserGetInfo(NULL, 1101, (LPBYTE *)&ui1101) == NERR_Success,
       "NetWkstaUserGetInfo is successful\n");
    ok(lstrcmpW(ui1101->wkui1101_oth_domains, ui1->wkui1_oth_domains) == 0,
       "the same oth_domains as returned for level 1\n");
    pNetApiBufferSize(ui1101, &dwSize);
    ok(dwSize >= (sizeof(WKSTA_USER_INFO_1101) +
                 lstrlenW(ui1101->wkui1101_oth_domains) * sizeof(WCHAR)),
       "Is allocated with NetApiBufferAllocate\n");

    pNetApiBufferFree(ui0);
    pNetApiBufferFree(ui1);
    pNetApiBufferFree(ui1101);

    /* errors handling */
    ok(pNetWkstaUserGetInfo(NULL, 10000, (LPBYTE *)&ui0) == ERROR_INVALID_LEVEL,
       "Invalid level\n");
}