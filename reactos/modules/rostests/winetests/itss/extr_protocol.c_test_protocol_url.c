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
typedef  int /*<<< orphan*/  buf ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int E_FAIL ; 
 scalar_t__ FAILED (int) ; 
 int IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 int IInternetProtocol_LockRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IInternetProtocol_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int IInternetProtocol_Release (int /*<<< orphan*/ *) ; 
 int IInternetProtocol_Terminate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IInternetProtocol_UnlockRequest (int /*<<< orphan*/ *) ; 
 int INET_E_DATA_NOT_AVAILABLE ; 
 scalar_t__ ITS_PROTOCOL ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int protocol_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_protocol ; 
 scalar_t__ test_protocol ; 

__attribute__((used)) static void test_protocol_url(IClassFactory *factory, LPCWSTR url, BOOL expect_mime)
{
    IInternetProtocol *protocol;
    BYTE buf[512];
    ULONG cb, ref;
    HRESULT hres;

    hres = IClassFactory_CreateInstance(factory, NULL, &IID_IInternetProtocol, (void**)&protocol);
    ok(hres == S_OK, "Could not get IInternetProtocol: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = protocol_start(protocol, url, expect_mime);
    if(FAILED(hres)) {
        IInternetProtocol_Release(protocol);
        return;
    }

    hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == 13, "cb=%u expected 13\n", cb);
    ok(!memcmp(buf, "<html></html>", 13), "unexpected data\n");
    ref = IInternetProtocol_Release(protocol);
    ok(!ref, "protocol ref=%d\n", ref);

    hres = IClassFactory_CreateInstance(factory, NULL, &IID_IInternetProtocol, (void**)&protocol);
    ok(hres == S_OK, "Could not get IInternetProtocol: %08x\n", hres);
    if(FAILED(hres))
        return;

    cb = 0xdeadbeef;
    hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
    ok(hres == (test_protocol == ITS_PROTOCOL ? INET_E_DATA_NOT_AVAILABLE : E_FAIL),
       "Read returned %08x\n", hres);
    ok(cb == 0xdeadbeef, "cb=%u expected 0xdeadbeef\n", cb);

    protocol_start(protocol, url, expect_mime);
    hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == 2, "cb=%u expected 2\n", cb);
    hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == 11, "cb=%u, expected 11\n", cb);
    hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
    ok(hres == S_FALSE, "Read failed: %08x expected S_FALSE\n", hres);
    ok(cb == 0, "cb=%u expected 0\n", cb);
    hres = IInternetProtocol_UnlockRequest(protocol);
    ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);
    ref = IInternetProtocol_Release(protocol);
    ok(!ref, "protocol ref=%d\n", ref);

    hres = IClassFactory_CreateInstance(factory, NULL, &IID_IInternetProtocol, (void**)&protocol);
    ok(hres == S_OK, "Could not get IInternetProtocol: %08x\n", hres);
    if(FAILED(hres))
        return;

    protocol_start(protocol, url, expect_mime);
    hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    hres = IInternetProtocol_LockRequest(protocol, 0);
    ok(hres == S_OK, "LockRequest failed: %08x\n", hres);
    hres = IInternetProtocol_UnlockRequest(protocol);
    ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);
    hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == 11, "cb=%u, expected 11\n", cb);
    ref = IInternetProtocol_Release(protocol);
    ok(!ref, "protocol ref=%d\n", ref);

    hres = IClassFactory_CreateInstance(factory, NULL, &IID_IInternetProtocol, (void**)&protocol);
    ok(hres == S_OK, "Could not get IInternetProtocol: %08x\n", hres);
    if(FAILED(hres))
        return;

    protocol_start(protocol, url, expect_mime);
    hres = IInternetProtocol_LockRequest(protocol, 0);
    ok(hres == S_OK, "LockRequest failed: %08x\n", hres);
    hres = IInternetProtocol_Terminate(protocol, 0);
    ok(hres == S_OK, "Terminate failed: %08x\n", hres);
    hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == 2, "cb=%u, expected 2\n", cb);
    hres = IInternetProtocol_UnlockRequest(protocol);
    ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);
    hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == 2, "cb=%u, expected 2\n", cb);
    hres = IInternetProtocol_Terminate(protocol, 0);
    ok(hres == S_OK, "Terminate failed: %08x\n", hres);
    hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
    ok(hres == S_OK, "Read failed: %08x\n", hres);
    ok(cb == 2, "cb=%u expected 2\n", cb);
    ref = IInternetProtocol_Release(protocol);
    ok(!ref, "protocol ref=%d\n", ref);

    hres = IClassFactory_CreateInstance(factory, NULL, &IID_IInternetProtocol, (void**)&read_protocol);
    ok(hres == S_OK, "Could not get IInternetProtocol: %08x\n", hres);
    if(FAILED(hres))
        return;

    protocol_start(read_protocol, url, expect_mime);
    ref = IInternetProtocol_Release(read_protocol);
    ok(!ref, "protocol ref=%d\n", ref);
    read_protocol = NULL;
}