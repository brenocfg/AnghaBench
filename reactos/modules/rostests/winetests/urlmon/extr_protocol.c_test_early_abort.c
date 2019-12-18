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
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  E_ABORT ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 scalar_t__ IInternetProtocol_Abort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocol_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_early_abort(const CLSID *clsid)
{
    IInternetProtocol *protocol;
    HRESULT hres;

    hres = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IInternetProtocol, (void**)&protocol);
    ok(hres == S_OK, "CoCreateInstance failed: %08x\n", hres);

    hres = IInternetProtocol_Abort(protocol, E_ABORT, 0);
    ok(hres == S_OK, "Abort failed: %08x\n", hres);

    hres = IInternetProtocol_Abort(protocol, E_FAIL, 0);
    ok(hres == S_OK, "Abort failed: %08x\n", hres);

    IInternetProtocol_Release(protocol);
}