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
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IConnectionPointContainer ;
typedef  int /*<<< orphan*/  IConnectionPoint ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IConnectionPointContainer_FindConnectionPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IConnectionPointContainer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IConnectionPointContainer ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static IConnectionPoint *get_cp(IUnknown *unk, REFIID riid)
{
    IConnectionPointContainer *cp_container;
    IConnectionPoint *cp;
    HRESULT hres;

    hres = IUnknown_QueryInterface(unk, &IID_IConnectionPointContainer, (void**)&cp_container);
    ok(hres == S_OK, "Could not get IConnectionPointContainer: %08x\n", hres);

    hres = IConnectionPointContainer_FindConnectionPoint(cp_container, riid, &cp);
    IConnectionPointContainer_Release(cp_container);
    ok(hres == S_OK, "FindConnectionPoint failed: %08x\n", hres);

    return cp;
}