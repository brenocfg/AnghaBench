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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IEnumVARIANT ;
typedef  int /*<<< orphan*/  IDriveCollection ;
typedef  int /*<<< orphan*/  IDrive ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DriveTypeConst ;

/* Variables and functions */
 scalar_t__ Fixed ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDriveCollection_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDriveCollection_get__NewEnum (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDrive_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDrive_get_DriveType (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IEnumVARIANT_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumVARIANT_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IFileSystem3_get_Drives (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IDrive ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static IDrive *get_fixed_drive(void)
{
    IDriveCollection *drives;
    IEnumVARIANT *iter;
    IDrive *drive;
    HRESULT hr;

    hr = IFileSystem3_get_Drives(fs3, &drives);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IDriveCollection_get__NewEnum(drives, (IUnknown**)&iter);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    IDriveCollection_Release(drives);

    while (1) {
        DriveTypeConst type;
        VARIANT var;

        hr = IEnumVARIANT_Next(iter, 1, &var, NULL);
        if (hr == S_FALSE) {
            drive = NULL;
            break;
        }
        ok(hr == S_OK, "got 0x%08x\n", hr);

        hr = IDispatch_QueryInterface(V_DISPATCH(&var), &IID_IDrive, (void**)&drive);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        VariantClear(&var);

        hr = IDrive_get_DriveType(drive, &type);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        if (type == Fixed)
            break;

        IDrive_Release(drive);
    }

    IEnumVARIANT_Release(iter);
    return drive;
}