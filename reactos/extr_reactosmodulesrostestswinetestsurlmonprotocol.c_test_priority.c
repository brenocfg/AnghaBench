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
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  int /*<<< orphan*/  IInternetPriority ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_IInternetPriority ; 
 scalar_t__ IInternetPriority_GetPriority (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IInternetPriority_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetPriority_SetPriority (int /*<<< orphan*/ *,int) ; 
 scalar_t__ IInternetProtocol_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_priority(IInternetProtocol *protocol)
{
    IInternetPriority *priority;
    LONG pr;
    HRESULT hres;

    hres = IInternetProtocol_QueryInterface(protocol, &IID_IInternetPriority,
                                            (void**)&priority);
    ok(hres == S_OK, "QueryInterface(IID_IInternetPriority) failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IInternetPriority_GetPriority(priority, &pr);
    ok(hres == S_OK, "GetPriority failed: %08x\n", hres);
    ok(pr == 0, "pr=%d, expected 0\n", pr);

    hres = IInternetPriority_SetPriority(priority, 1);
    ok(hres == S_OK, "SetPriority failed: %08x\n", hres);

    hres = IInternetPriority_GetPriority(priority, &pr);
    ok(hres == S_OK, "GetPriority failed: %08x\n", hres);
    ok(pr == 1, "pr=%d, expected 1\n", pr);

    IInternetPriority_Release(priority);
}