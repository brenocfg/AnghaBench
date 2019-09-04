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
struct TYPE_5__ {int /*<<< orphan*/  IDirectInputDevice8A_iface; int /*<<< orphan*/  IDirectInputDevice8W_iface; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
typedef  TYPE_2__ SysMouseImpl ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int /*<<< orphan*/ * REFGUID ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  IDirectInputImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DIERR_DEVICENOTREG ; 
 int /*<<< orphan*/  DIERR_NOINTERFACE ; 
 int /*<<< orphan*/  DIERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DI_OK ; 
 int /*<<< orphan*/  GUID_SysMouse ; 
 int /*<<< orphan*/  IID_IDirectInputDevice2A ; 
 int /*<<< orphan*/  IID_IDirectInputDevice2W ; 
 int /*<<< orphan*/  IID_IDirectInputDevice7A ; 
 int /*<<< orphan*/  IID_IDirectInputDevice7W ; 
 int /*<<< orphan*/  IID_IDirectInputDevice8A ; 
 int /*<<< orphan*/  IID_IDirectInputDevice8W ; 
 int /*<<< orphan*/  IID_IDirectInputDeviceA ; 
 int /*<<< orphan*/  IID_IDirectInputDeviceW ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 TYPE_2__* alloc_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT mousedev_create_device(IDirectInputImpl *dinput, REFGUID rguid, REFIID riid, LPVOID *pdev, int unicode)
{
    TRACE("%p %s %s %p %i\n", dinput, debugstr_guid(rguid), debugstr_guid(riid), pdev, unicode);
    *pdev = NULL;

    if (IsEqualGUID(&GUID_SysMouse, rguid)) /* Wine Mouse */
    {
        SysMouseImpl *This;

        if (riid == NULL)
            ;/* nothing */
        else if (IsEqualGUID(&IID_IDirectInputDeviceA,  riid) ||
                 IsEqualGUID(&IID_IDirectInputDevice2A, riid) ||
                 IsEqualGUID(&IID_IDirectInputDevice7A, riid) ||
                 IsEqualGUID(&IID_IDirectInputDevice8A, riid))
        {
            unicode = 0;
        }
        else if (IsEqualGUID(&IID_IDirectInputDeviceW,  riid) ||
                 IsEqualGUID(&IID_IDirectInputDevice2W, riid) ||
                 IsEqualGUID(&IID_IDirectInputDevice7W, riid) ||
                 IsEqualGUID(&IID_IDirectInputDevice8W, riid))
        {
            unicode = 1;
        }
        else
        {
            WARN("no interface\n");
            return DIERR_NOINTERFACE;
        }

        This = alloc_device(rguid, dinput);
        TRACE("Created a Mouse device (%p)\n", This);

        if (!This) return DIERR_OUTOFMEMORY;

        if (unicode)
            *pdev = &This->base.IDirectInputDevice8W_iface;
        else
            *pdev = &This->base.IDirectInputDevice8A_iface;

        return DI_OK;
    }

    return DIERR_DEVICENOTREG;
}