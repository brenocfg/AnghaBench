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
typedef  int /*<<< orphan*/  test_html ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  blank_html ;
typedef  int WCHAR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  int /*<<< orphan*/  IInternetPriority ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int E_NOINTERFACE ; 
 scalar_t__ FAILED (int) ; 
 int IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IInternetPriority ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 int IInternetProtocol_LockRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IInternetProtocol_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IInternetProtocol_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  IInternetProtocol_Release (int /*<<< orphan*/ *) ; 
 int IInternetProtocol_UnlockRequest (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  about_blank_url ; 
 int /*<<< orphan*/  about_res_url ; 
 int /*<<< orphan*/  about_test_url ; 
 int /*<<< orphan*/  bindf ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  protocol_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_test_about_protocol(IClassFactory *factory, DWORD bf)
{
    IInternetProtocol *protocol;
    IInternetPriority *priority;
    BYTE buf[512];
    ULONG cb;
    HRESULT hres;

    static const WCHAR blank_html[] = {0xfeff,'<','H','T','M','L','>','<','/','H','T','M','L','>',0};
    static const WCHAR test_html[] =
        {0xfeff,'<','H','T','M','L','>','t','e','s','t','<','/','H','T','M','L','>',0};

    bindf = bf;

    hres = IClassFactory_CreateInstance(factory, NULL, &IID_IInternetProtocol, (void**)&protocol);
    ok(hres == S_OK, "Could not get IInternetProtocol: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IInternetProtocol_QueryInterface(protocol, &IID_IInternetPriority, (void**)&priority);
    ok(hres == E_NOINTERFACE,
       "QueryInterface(IInternetPriority) returned %08x, expected E_NOINTEFACE\n", hres);

    protocol_start(protocol, about_blank_url);
    hres = IInternetProtocol_LockRequest(protocol, 0);
    ok(hres == S_OK, "LockRequest failed: %08x\n", hres);
    hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == sizeof(blank_html), "cb=%d\n", cb);
    ok(!memcmp(buf, blank_html, cb), "Readed wrong data\n");
    hres = IInternetProtocol_UnlockRequest(protocol);
    ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);

    protocol_start(protocol, about_test_url);
    hres = IInternetProtocol_LockRequest(protocol, 0);
    ok(hres == S_OK, "LockRequest failed: %08x\n", hres);
    hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == sizeof(test_html), "cb=%d\n", cb);
    ok(!memcmp(buf, test_html, cb), "Readed wrong data\n");
    hres = IInternetProtocol_UnlockRequest(protocol);
    ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);

    protocol_start(protocol, about_res_url);
    hres = IInternetProtocol_LockRequest(protocol, 0);
    ok(hres == S_OK, "LockRequest failed: %08x\n", hres);
    hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == sizeof(blank_html), "cb=%d\n", cb);
    ok(!memcmp(buf, blank_html, cb), "Readed wrong data\n");
    hres = IInternetProtocol_UnlockRequest(protocol);
    ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);

    IInternetProtocol_Release(protocol);
}