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
typedef  int ULONGLONG ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ ** objects ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pApphelpCheckShellObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ApphelpCheckShellObject(void)
{
    ULONGLONG flags;
    BOOL res;
    int i;

    if (!pApphelpCheckShellObject)
    {
        win_skip("ApphelpCheckShellObject not available\n");
        return;
    }

    for (i = 0; objects[i]; i++)
    {
        flags = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pApphelpCheckShellObject(objects[i], FALSE, &flags);
        ok(res && (flags == 0), "%s 0: got %d and 0x%x%08x with 0x%x (expected TRUE and 0)\n",
            wine_dbgstr_guid(objects[i]), res, (ULONG)(flags >> 32), (ULONG)flags, GetLastError());

        flags = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pApphelpCheckShellObject(objects[i], TRUE, &flags);
        ok(res && (flags == 0), "%s 1: got %d and 0x%x%08x with 0x%x (expected TRUE and 0)\n",
            wine_dbgstr_guid(objects[i]), res, (ULONG)(flags >> 32), (ULONG)flags, GetLastError());

    }

    /* NULL as pointer to flags is checked */
    SetLastError(0xdeadbeef);
    res = pApphelpCheckShellObject(&GUID_NULL, FALSE, NULL);
    ok(res, "%s 0: got %d with 0x%x (expected != FALSE)\n", wine_dbgstr_guid(&GUID_NULL), res, GetLastError());

    /* NULL as CLSID* crash on Windows */
    if (0)
    {
        flags = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pApphelpCheckShellObject(NULL, FALSE, &flags);
        trace("NULL as CLSID*: got %d and 0x%x%08x with 0x%x\n", res, (ULONG)(flags >> 32), (ULONG)flags, GetLastError());
    }
}