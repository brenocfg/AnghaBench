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
struct getdrivename_test {int /*<<< orphan*/ * drive; scalar_t__* path; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  IFileSystem3_GetDriveName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SysAllocString (scalar_t__*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs3 ; 
 struct getdrivename_test* getdrivenametestdata ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GetDriveName(void)
{
    const struct getdrivename_test *ptr = getdrivenametestdata;
    HRESULT hr;
    BSTR name;

    hr = IFileSystem3_GetDriveName(fs3, NULL, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    name = (void*)0xdeadbeef;
    hr = IFileSystem3_GetDriveName(fs3, NULL, &name);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(name == NULL, "got %p\n", name);

    while (*ptr->path) {
        BSTR path = SysAllocString(ptr->path);
        name = (void*)0xdeadbeef;
        hr = IFileSystem3_GetDriveName(fs3, path, &name);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        if (name)
            ok(!lstrcmpW(ptr->drive, name), "got %s, expected %s\n", wine_dbgstr_w(name), wine_dbgstr_w(ptr->drive));
        else
            ok(!*ptr->drive, "got %s, expected %s\n", wine_dbgstr_w(name), wine_dbgstr_w(ptr->drive));
        SysFreeString(path);
        SysFreeString(name);
        ptr++;
    }
}