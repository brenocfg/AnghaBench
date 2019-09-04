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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IInternetProtocolInfo ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_JSProtocol ; 
 int /*<<< orphan*/  CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IInternetProtocolInfo ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IInternetProtocolInfo_CombineUrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_CompareUrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_ParseUrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_QueryInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INET_E_DEFAULT_ACTION ; 
 int /*<<< orphan*/  INET_E_USE_DEFAULT_PROTOCOLHANDLER ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int PARSE_CANONICALIZE ; 
 int PARSE_DOMAIN ; 
 int PARSE_SECURITY_URL ; 
 int PARSE_UNESCAPE ; 
#define  QUERY_IS_SECURE 129 
#define  QUERY_USES_NETWORK 128 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  javascript_test_url ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_javascript_protocol(void)
{
    IInternetProtocolInfo *protocol_info;
    IUnknown *unk;
    IClassFactory *factory;
    HRESULT hres;

    hres = CoGetClassObject(&CLSID_JSProtocol, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "CoGetClassObject failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IUnknown_QueryInterface(unk, &IID_IInternetProtocolInfo, (void**)&protocol_info);
    ok(hres == S_OK, "Could not get IInternetProtocolInfo interface: %08x\n", hres);
    if(SUCCEEDED(hres)) {
        WCHAR buf[128];
        DWORD size;
        int i;

        for(i = PARSE_CANONICALIZE; i <= PARSE_UNESCAPE; i++) {
            if(i != PARSE_SECURITY_URL && i != PARSE_DOMAIN) {
                hres = IInternetProtocolInfo_ParseUrl(protocol_info, javascript_test_url, i, 0, buf,
                        sizeof(buf)/sizeof(buf[0]), &size, 0);
                ok(hres == INET_E_DEFAULT_ACTION,
                        "[%d] failed: %08x, expected INET_E_DEFAULT_ACTION\n", i, hres);
            }
        }

        hres = IInternetProtocolInfo_ParseUrl(protocol_info, javascript_test_url, PARSE_UNESCAPE+1, 0, buf,
                sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == INET_E_DEFAULT_ACTION,
                "ParseUrl failed: %08x, expected INET_E_DEFAULT_ACTION\n", hres);

        size = 0xdeadbeef;
        hres = IInternetProtocolInfo_CombineUrl(protocol_info, javascript_test_url, javascript_test_url,
                0, buf, sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER, "CombineUrl failed: %08x\n", hres);
        ok(size == 0xdeadbeef, "size=%d\n", size);

        hres = IInternetProtocolInfo_CompareUrl(protocol_info, javascript_test_url, javascript_test_url, 0);
        ok(hres == E_NOTIMPL, "CompareUrl failed: %08x\n", hres);

        for(i=0; i<30; i++) {
            switch(i) {
            case QUERY_USES_NETWORK:
            case QUERY_IS_SECURE:
                break;
            default:
                hres = IInternetProtocolInfo_QueryInfo(protocol_info, javascript_test_url, i, 0,
                                                       buf, sizeof(buf), &size, 0);
                ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER,
                   "QueryInfo(%d) returned: %08x, expected INET_E_USE_DEFAULT_PROTOCOLHANDLER\n", i, hres);
            }
        }


        memset(buf, '?', sizeof(buf));
        hres = IInternetProtocolInfo_QueryInfo(protocol_info, javascript_test_url, QUERY_USES_NETWORK, 0,
                                               buf, sizeof(buf), &size, 0);
        ok(hres == S_OK, "QueryInfo(QUERY_USES_NETWORK) failed: %08x\n", hres);
        ok(size == sizeof(DWORD), "size=%d\n", size);
        ok(!*(DWORD*)buf, "buf=%d\n", *(DWORD*)buf);

        memset(buf, '?', sizeof(buf));
        hres = IInternetProtocolInfo_QueryInfo(protocol_info, javascript_test_url, QUERY_USES_NETWORK, 0,
                                               buf, sizeof(buf), NULL, 0);
        ok(hres == S_OK, "QueryInfo(QUERY_USES_NETWORK) failed: %08x\n", hres);
        ok(!*(DWORD*)buf, "buf=%d\n", *(DWORD*)buf);

        hres = IInternetProtocolInfo_QueryInfo(protocol_info, javascript_test_url, QUERY_USES_NETWORK, 0,
                                               buf, 3, &size, 0);
        ok(hres == E_FAIL, "QueryInfo(QUERY_USES_NETWORK) failed: %08x, expected E_FAIL\n", hres);

        hres = IInternetProtocolInfo_QueryInfo(protocol_info, javascript_test_url, QUERY_USES_NETWORK, 0,
                                               NULL, sizeof(buf), &size, 0);
        ok(hres == E_FAIL, "QueryInfo(QUERY_USES_NETWORK) failed: %08x, expected E_FAIL\n", hres);

        hres = IInternetProtocolInfo_QueryInfo(protocol_info, javascript_test_url, 60, 0,
                                               NULL, sizeof(buf), &size, 0);
        ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER,
           "QueryInfo failed: %08x, expected INET_E_USE_DEFAULT_PROTOCOLHANDLER\n", hres);

        /* FIXME: test QUERY_IS_SECURE */

        IInternetProtocolInfo_Release(protocol_info);
    }

    hres = IUnknown_QueryInterface(unk, &IID_IClassFactory, (void**)&factory);
    ok(hres == S_OK, "Could not get IClassFactory interface\n");
    if(SUCCEEDED(hres))
        IClassFactory_Release(factory);

    IUnknown_Release(unk);
}