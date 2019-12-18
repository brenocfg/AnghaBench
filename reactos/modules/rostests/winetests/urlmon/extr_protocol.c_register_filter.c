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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 scalar_t__ IInternetSession_RegisterMimeFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetSession_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetSession_UnregisterMimeFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  gifW ; 
 int /*<<< orphan*/  mimefilter_cf ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCoInternetGetSession (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjpegW ; 

__attribute__((used)) static void register_filter(BOOL do_register)
{
    IInternetSession *session;
    HRESULT hres;

    hres = pCoInternetGetSession(0, &session, 0);
    ok(hres == S_OK, "CoInternetGetSession failed: %08x\n", hres);

    if(do_register) {
        hres = IInternetSession_RegisterMimeFilter(session, &mimefilter_cf, &IID_IInternetProtocol, pjpegW);
        ok(hres == S_OK, "RegisterMimeFilter failed: %08x\n", hres);
        hres = IInternetSession_RegisterMimeFilter(session, &mimefilter_cf, &IID_IInternetProtocol, gifW);
        ok(hres == S_OK, "RegisterMimeFilter failed: %08x\n", hres);
    }else {
        hres = IInternetSession_UnregisterMimeFilter(session, &mimefilter_cf, pjpegW);
        ok(hres == S_OK, "RegisterMimeFilter failed: %08x\n", hres);
        hres = IInternetSession_UnregisterMimeFilter(session, &mimefilter_cf, gifW);
        ok(hres == S_OK, "RegisterMimeFilter failed: %08x\n", hres);
    }

    IInternetSession_Release(session);
}