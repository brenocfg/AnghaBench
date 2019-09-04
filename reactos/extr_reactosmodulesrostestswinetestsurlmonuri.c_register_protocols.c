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
typedef  int /*<<< orphan*/  IInternetSession ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_NULL ; 
 scalar_t__ IInternetSession_RegisterNameSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetSession_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCoInternetGetSession (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protocol_cf ; 
 int /*<<< orphan*/  winetestW ; 

__attribute__((used)) static void register_protocols(void)
{
    IInternetSession *session;
    HRESULT hres;

    hres = pCoInternetGetSession(0, &session, 0);
    ok(hres == S_OK, "CoInternetGetSession failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IInternetSession_RegisterNameSpace(session, &protocol_cf, &IID_NULL,
            winetestW, 0, NULL, 0);
    ok(hres == S_OK, "RegisterNameSpace failed: %08x\n", hres);

    IInternetSession_Release(session);
}