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
typedef  int /*<<< orphan*/  LPOLESTR ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 scalar_t__ IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IMoniker_IsSystemMoniker (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ MKSYS_URLMONIKER ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_mon_displayname(IMoniker *mon, const char *exname, const char *broken_name)
{
    LPOLESTR display_name;
    DWORD mksys;
    HRESULT hres;

    hres = IMoniker_GetDisplayName(mon, NULL, NULL, &display_name);
    ok(hres == S_OK, "GetDisplayName failed: %08x\n", hres);
    ok(!strcmp_wa(display_name, exname) || broken(broken_name && !strcmp_wa(display_name, broken_name)),
        "display_name = %s\n", wine_dbgstr_w(display_name));
    CoTaskMemFree(display_name);

    hres = IMoniker_IsSystemMoniker(mon, &mksys);
    ok(hres == S_OK, "IsSystemMoniker failed: %08x\n", hres);
    ok(mksys == MKSYS_URLMONIKER, "mksys = %d\n", mksys);
}