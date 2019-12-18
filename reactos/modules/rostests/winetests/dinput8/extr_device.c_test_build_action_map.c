#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ddi ;
struct TYPE_9__ {scalar_t__ dwHow; int /*<<< orphan*/  guidInstance; int /*<<< orphan*/  dwObjID; } ;
struct TYPE_8__ {TYPE_3__* rgoAction; } ;
struct TYPE_7__ {int dwSize; int /*<<< orphan*/  guidInstance; } ;
typedef  int /*<<< orphan*/  IDirectInputDevice8A ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ DIDEVICEINSTANCEA ;
typedef  TYPE_2__ DIACTIONFORMATA ;
typedef  TYPE_3__ DIACTIONA ;

/* Variables and functions */
 scalar_t__ DIAH_DEFAULT ; 
 scalar_t__ DIAH_USERCONFIG ; 
 int /*<<< orphan*/  DIDBAM_HWDEFAULTS ; 
 scalar_t__ DIDFT_GETINSTANCE (int /*<<< orphan*/ ) ; 
 scalar_t__ DIDFT_GETTYPE (int /*<<< orphan*/ ) ; 
 int IDirectInputDevice8_BuildActionMap (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectInputDevice_GetDeviceInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SUCCEEDED (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_build_action_map(IDirectInputDevice8A *lpdid, DIACTIONFORMATA *lpdiaf,
                                  int action_index, DWORD expected_type, DWORD expected_inst)
{
    HRESULT hr;
    DIACTIONA *actions;
    DWORD instance, type, how;
    GUID assigned_to;
    DIDEVICEINSTANCEA ddi;

    ddi.dwSize = sizeof(ddi);
    IDirectInputDevice_GetDeviceInfo(lpdid, &ddi);

    hr = IDirectInputDevice8_BuildActionMap(lpdid, lpdiaf, NULL, DIDBAM_HWDEFAULTS);
    ok (SUCCEEDED(hr), "BuildActionMap failed hr=%08x\n", hr);

    actions = lpdiaf->rgoAction;
    instance = DIDFT_GETINSTANCE(actions[action_index].dwObjID);
    type = DIDFT_GETTYPE(actions[action_index].dwObjID);
    how = actions[action_index].dwHow;
    assigned_to = actions[action_index].guidInstance;

    ok (how == DIAH_USERCONFIG || how == DIAH_DEFAULT, "Action was not set dwHow=%08x\n", how);
    ok (instance == expected_inst, "Action not mapped correctly instance=%08x expected=%08x\n", instance, expected_inst);
    ok (type == expected_type, "Action type not mapped correctly type=%08x expected=%08x\n", type, expected_type);
    ok (IsEqualGUID(&assigned_to, &ddi.guidInstance), "Action and device GUID do not match action=%d\n", action_index);
}