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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  char CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateDirectoryA (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetVersion () ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ *) ; 
 scalar_t__ RemoveDirectoryA (char const*) ; 
 int /*<<< orphan*/ * SHSimpleIDListFromPath (char const*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_pidl (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void test_SHSimpleIDListFromPath(void)
{
    const WCHAR adirW[] = {'C',':','\\','s','i','d','l','f','p','d','i','r',0};
    const CHAR adirA[] = "C:\\sidlfpdir";
    BOOL br, is_unicode = !(GetVersion() & 0x80000000);

    LPITEMIDLIST pidl = NULL;

    br = CreateDirectoryA(adirA, NULL);
    ok(br == TRUE, "CreateDirectory failed: %d\n", GetLastError());

    if(is_unicode)
        pidl = SHSimpleIDListFromPath(adirW);
    else
        pidl = SHSimpleIDListFromPath((const WCHAR *)adirA);
    verify_pidl(pidl, adirW);
    ILFree(pidl);

    br = RemoveDirectoryA(adirA);
    ok(br == TRUE, "RemoveDirectory failed: %d\n", GetLastError());

    if(is_unicode)
        pidl = SHSimpleIDListFromPath(adirW);
    else
        pidl = SHSimpleIDListFromPath((const WCHAR *)adirA);
    verify_pidl(pidl, adirW);
    ILFree(pidl);
}