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
typedef  int /*<<< orphan*/  IApplicationAssociationRegistration ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_POINTER ; 
 scalar_t__ IApplicationAssociationRegistration_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IApplicationAssociationRegistration_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IApplicationAssociationRegistration ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_IApplicationAssociationRegistration_QueryInterface(IApplicationAssociationRegistration *appreg)
{
    IApplicationAssociationRegistration *appreg2;
    IUnknown *unk;
    HRESULT hr;

    hr = IApplicationAssociationRegistration_QueryInterface(appreg, &IID_IApplicationAssociationRegistration,
       (void**)&appreg2);
    ok(hr == S_OK, "QueryInterface (IApplicationAssociationRegistration) returned 0x%x\n", hr);
    if (SUCCEEDED(hr)) {
        IApplicationAssociationRegistration_Release(appreg2);
    }

    hr = IApplicationAssociationRegistration_QueryInterface(appreg, &IID_IUnknown, (void**)&unk);
    ok(hr == S_OK, "QueryInterface (IUnknown) returned 0x%x\n", hr);
    if (SUCCEEDED(hr)) {
        IUnknown_Release(unk);
    }

    hr = IApplicationAssociationRegistration_QueryInterface(appreg, &IID_IUnknown, NULL);
    ok(hr == E_POINTER, "got 0x%x (expected E_POINTER)\n", hr);
}