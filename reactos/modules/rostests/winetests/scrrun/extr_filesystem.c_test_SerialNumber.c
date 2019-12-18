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
typedef  int LONG ;
typedef  int /*<<< orphan*/  IDrive ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * E_POINTER ; 
 int /*<<< orphan*/  IDrive_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IDrive_get_FileSystem (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IDrive_get_SerialNumber (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * IDrive_get_VolumeName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_fixed_drive () ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_SerialNumber(void)
{
    IDrive *drive;
    LONG serial;
    HRESULT hr;
    BSTR name;

    drive = get_fixed_drive();
    if (!drive) {
        skip("No fixed drive found, skipping test.\n");
        return;
    }

    hr = IDrive_get_SerialNumber(drive, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    serial = 0xdeadbeef;
    hr = IDrive_get_SerialNumber(drive, &serial);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(serial != 0xdeadbeef, "got %x\n", serial);

    hr = IDrive_get_FileSystem(drive, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    name = NULL;
    hr = IDrive_get_FileSystem(drive, &name);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(name != NULL, "got %p\n", name);
    SysFreeString(name);

    hr = IDrive_get_VolumeName(drive, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    name = NULL;
    hr = IDrive_get_VolumeName(drive, &name);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(name != NULL, "got %p\n", name);
    SysFreeString(name);

    IDrive_Release(drive);
}