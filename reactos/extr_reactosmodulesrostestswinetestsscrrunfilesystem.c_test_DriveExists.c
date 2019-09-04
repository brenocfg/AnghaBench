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
struct driveexists_test {char* drivespec; int drivetype; scalar_t__ expected_ret; } ;
typedef  char WCHAR ;
typedef  scalar_t__ VARIANT_BOOL ;
typedef  scalar_t__ HRESULT ;
typedef  char* BSTR ;

/* Variables and functions */
 scalar_t__ E_POINTER ; 
 int GetDriveTypeW (char*) ; 
 scalar_t__ IFileSystem3_DriveExists (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 scalar_t__ S_OK ; 
 char* SysAllocString (char*) ; 
 int /*<<< orphan*/  SysFreeString (char*) ; 
 scalar_t__ VARIANT_FALSE ; 
 scalar_t__ VARIANT_TRUE ; 
 struct driveexists_test* driveexiststestdata ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  skip (char*,int,int /*<<< orphan*/ ) ; 
 char tolower (char) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_DriveExists(void)
{
    const struct driveexists_test *ptr = driveexiststestdata;
    HRESULT hr;
    VARIANT_BOOL ret;
    BSTR drivespec;
    WCHAR root[] = {'?',':','\\',0};

    hr = IFileSystem3_DriveExists(fs3, NULL, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    ret = VARIANT_TRUE;
    hr = IFileSystem3_DriveExists(fs3, NULL, &ret);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(ret == VARIANT_FALSE, "got %x\n", ret);

    drivespec = SysAllocString(root);
    hr = IFileSystem3_DriveExists(fs3, drivespec, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);
    SysFreeString(drivespec);

    for (; *ptr->drivespec; ptr++) {
        drivespec = SysAllocString(ptr->drivespec);
        if (ptr->drivetype != -1) {
            for (root[0] = 'A'; root[0] <= 'Z'; root[0]++)
                if (GetDriveTypeW(root) == ptr->drivetype)
                    break;
            if (root[0] > 'Z') {
                skip("No drive with type 0x%x found, skipping test %s.\n",
                        ptr->drivetype, wine_dbgstr_w(ptr->drivespec));
                SysFreeString(drivespec);
                continue;
            }

            /* Test both upper and lower case drive letters. */
            drivespec[0] = root[0];
            ret = ptr->expected_ret == VARIANT_TRUE ? VARIANT_FALSE : VARIANT_TRUE;
            hr = IFileSystem3_DriveExists(fs3, drivespec, &ret);
            ok(hr == S_OK, "got 0x%08x for drive spec %s (%s)\n",
                    hr, wine_dbgstr_w(drivespec), wine_dbgstr_w(ptr->drivespec));
            ok(ret == ptr->expected_ret, "got %d, expected %d for drive spec %s (%s)\n",
                    ret, ptr->expected_ret, wine_dbgstr_w(drivespec), wine_dbgstr_w(ptr->drivespec));

            drivespec[0] = tolower(root[0]);
        }

        ret = ptr->expected_ret == VARIANT_TRUE ? VARIANT_FALSE : VARIANT_TRUE;
        hr = IFileSystem3_DriveExists(fs3, drivespec, &ret);
        ok(hr == S_OK, "got 0x%08x for drive spec %s (%s)\n",
                hr, wine_dbgstr_w(drivespec), wine_dbgstr_w(ptr->drivespec));
        ok(ret == ptr->expected_ret, "got %d, expected %d for drive spec %s (%s)\n",
                ret, ptr->expected_ret, wine_dbgstr_w(drivespec), wine_dbgstr_w(ptr->drivespec));

        SysFreeString(drivespec);
    }
}