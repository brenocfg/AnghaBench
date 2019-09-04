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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IObjectSafety ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IObjectSafety ; 
 int /*<<< orphan*/  IObjectSafety_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IObjectSafety_SetInterfaceSafetyOptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void set_safety_opt(IUnknown *unk, DWORD mask, DWORD opts)
{
    IObjectSafety *obj_safety;
    HRESULT hr;

    hr = IUnknown_QueryInterface(unk, &IID_IObjectSafety, (void**)&obj_safety);
    ok(hr == S_OK, "Could not get IObjectSafety iface: %08x\n", hr);

    hr = IObjectSafety_SetInterfaceSafetyOptions(obj_safety, &IID_IDispatch, mask, mask&opts);
    ok(hr == S_OK, "SetInterfaceSafetyOptions failed: %08x\n", hr);

    IObjectSafety_Release(obj_safety);
}