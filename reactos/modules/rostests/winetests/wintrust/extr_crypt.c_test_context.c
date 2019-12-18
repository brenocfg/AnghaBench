#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_6__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
typedef  void* HCATADMIN ;
typedef  TYPE_2__ GUID ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetFileAttributesA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * catroot ; 
 int /*<<< orphan*/ * catroot2 ; 
 TYPE_2__ dummy ; 
 int /*<<< orphan*/  lstrcatA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCryptCATAdminAcquireContext (void**,TYPE_2__*,int) ; 
 int pCryptCATAdminReleaseContext (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_context(void)
{
    BOOL ret;
    HCATADMIN hca;
    static GUID unknown = { 0xC689AABA, 0x8E78, 0x11D0, { 0x8C,0x47,0x00,0xC0,0x4F,0xC2,0x95,0xEE }}; /* WINTRUST.DLL */
    CHAR dummydir[MAX_PATH];
    DWORD attrs;

    /* When CryptCATAdminAcquireContext is successful it will create
     * several directories if they don't exist:
     *
     * ...\system32\CatRoot\{GUID}, this directory holds the .cat files
     * ...\system32\CatRoot2\{GUID}  (WinXP and up), here we find the catalog database for that GUID
     *
     * Windows Vista uses lowercase catroot and catroot2.
     *
     * When passed a NULL GUID it will create the following directories although on
     * WinXP and up these directories are already present when Windows is installed:
     *
     * ...\system32\CatRoot\{127D0A1D-4EF2-11D1-8608-00C04FC295EE}
     * ...\system32\CatRoot2\{127D0A1D-4EF2-11D1-8608-00C04FC295EE} (WinXP up)
     *
     * TODO: Find out what this GUID is/does.
     *
     * On WinXP and up there is also a TimeStamp file in some of directories that
     * seem to indicate the last change to the catalog database for that GUID.
     *
     * On Windows 2000 some files are created/updated:
     *
     * ...\system32\CatRoot\SYSMAST.cbk
     * ...\system32\CatRoot\SYSMAST.cbd
     * ...\system32\CatRoot\{GUID}\CATMAST.cbk
     * ...\system32\CatRoot\{GUID}\CATMAST.cbd
     *
     */

    /* All NULL */
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminAcquireContext(NULL, NULL, 0);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* NULL GUID */
    if (0) { /* crashes on 64-bit win10 */
    ret = pCryptCATAdminAcquireContext(&hca, NULL, 0);
    ok(ret, "Expected success, got FALSE with %d\n", GetLastError());
    ok(hca != NULL, "Expected a context handle, got NULL\n");

    /* Proper release */
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminReleaseContext(hca, 0);
    ok(ret, "Expected success, got FALSE with %d\n", GetLastError());

    /* Try to release a second time */
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminReleaseContext(hca, 0);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    }

    /* All NULL */
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminReleaseContext(NULL, 0);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* NULL context handle and dummy GUID */
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminAcquireContext(NULL, &dummy, 0);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Correct context handle and dummy GUID
     *
     * The tests run in the past unfortunately made sure that some directories were created.
     *
     * FIXME:
     * We don't want to mess too much with these for now so we should delete only the ones
     * that shouldn't be there like the deadbeef ones. We first have to figure out if it's
     * safe to remove files and directories from CatRoot/CatRoot2.
     */

    ret = pCryptCATAdminAcquireContext(&hca, &dummy, 0);
    ok(ret || GetLastError() == ERROR_ACCESS_DENIED, "CryptCATAdminAcquireContext failed %u\n", GetLastError());
    if (!ret && GetLastError() == ERROR_ACCESS_DENIED)
    {
        win_skip("Not running as administrator\n");
        return;
    }
    ok(hca != NULL, "Expected a context handle, got NULL\n");

    attrs = GetFileAttributesA(catroot);
    ok(attrs != INVALID_FILE_ATTRIBUTES, "Expected the CatRoot directory to exist\n");

    /* Windows creates the GUID directory in capitals */
    lstrcpyA(dummydir, catroot);
    lstrcatA(dummydir, "\\{DEADBEEF-DEAD-BEEF-DEAD-BEEFDEADBEEF}");
    attrs = GetFileAttributesA(dummydir);
    ok(attrs != INVALID_FILE_ATTRIBUTES,
       "Expected CatRoot\\{DEADBEEF-DEAD-BEEF-DEAD-BEEFDEADBEEF} directory to exist\n");

    /* Only present on XP or higher. */
    attrs = GetFileAttributesA(catroot2);
    if (attrs != INVALID_FILE_ATTRIBUTES)
    {
        lstrcpyA(dummydir, catroot2);
        lstrcatA(dummydir, "\\{DEADBEEF-DEAD-BEEF-DEAD-BEEFDEADBEEF}");
        attrs = GetFileAttributesA(dummydir);
        ok(attrs != INVALID_FILE_ATTRIBUTES,
            "Expected CatRoot2\\{DEADBEEF-DEAD-BEEF-DEAD-BEEFDEADBEEF} directory to exist\n");
    }

    ret = pCryptCATAdminReleaseContext(hca, 0);
    ok(ret, "Expected success, got FALSE with %d\n", GetLastError());

    /* Correct context handle and GUID */
    ret = pCryptCATAdminAcquireContext(&hca, &unknown, 0);
    ok(ret, "Expected success, got FALSE with %d\n", GetLastError());
    ok(hca != NULL, "Expected a context handle, got NULL\n");

    ret = pCryptCATAdminReleaseContext(hca, 0);
    ok(ret, "Expected success, got FALSE with %d\n", GetLastError());

    hca = (void *) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    /* Flags is documented as unused, but the parameter is checked since win8 */
    ret = pCryptCATAdminAcquireContext(&hca, &unknown, 1);
    ok((!ret && (GetLastError() == ERROR_INVALID_PARAMETER) && (hca == (void *) 0xdeadbeef)) ||
        broken(ret && hca != NULL && hca != (void *) 0xdeadbeef),
        "Expected FALSE and ERROR_INVALID_PARAMETER with untouched handle, got %d and %u with %p\n",
        ret, GetLastError(), hca);

    if (ret && hca)
    {
        SetLastError(0xdeadbeef);
        ret = pCryptCATAdminReleaseContext(hca, 0);
        ok(ret, "Expected success, got FALSE with %d\n", GetLastError());
    }
}