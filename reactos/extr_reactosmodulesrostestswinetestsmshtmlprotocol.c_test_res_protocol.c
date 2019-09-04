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
typedef  int /*<<< orphan*/  wrong_url1 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  blank_url ;
typedef  char WCHAR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IInternetProtocolInfo ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  int /*<<< orphan*/  IInternetPriority ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ResProtocol ; 
 int CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ERROR_RESOURCE_TYPE_NOT_FOUND ; 
 int E_FAIL ; 
 int E_INVALIDARG ; 
 int E_NOINTERFACE ; 
 int E_NOTIMPL ; 
 int E_POINTER ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IInternetPriority ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 int /*<<< orphan*/  IID_IInternetProtocolInfo ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int IInternetProtocolInfo_CombineUrl (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ) ; 
 int IInternetProtocolInfo_CompareUrl (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int IInternetProtocolInfo_ParseUrl (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ) ; 
 int IInternetProtocolInfo_QueryInfo (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_Release (int /*<<< orphan*/ *) ; 
 int IInternetProtocol_LockRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IInternetProtocol_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IInternetProtocol_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  IInternetProtocol_Release (int /*<<< orphan*/ *) ; 
 int IInternetProtocol_Terminate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IInternetProtocol_UnlockRequest (int /*<<< orphan*/ *) ; 
 int INET_E_DEFAULT_ACTION ; 
 int INET_E_USE_DEFAULT_PROTOCOLHANDLER ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int MK_E_SYNTAX ; 
 int PARSE_CANONICALIZE ; 
 int PARSE_DOMAIN ; 
 int PARSE_SECURITY_URL ; 
 int PARSE_UNESCAPE ; 
 int QUERY_IS_SAFE ; 
 int QUERY_IS_SECURE ; 
 int QUERY_USES_NETWORK ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  URL_FILE_USE_PATHURL ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  protocol_start (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  res_sec_url_cmp (char*,int,char const*) ; 
 int /*<<< orphan*/  test_protocol_fail (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_res_url (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_res_protocol(void)
{
    IInternetProtocolInfo *protocol_info;
    IUnknown *unk;
    IClassFactory *factory;
    HRESULT hres;

    static const WCHAR blank_url[] =
        {'r','e','s',':','/','/','m','s','h','t','m','l','.','d','l','l','/','b','l','a','n','k','.','h','t','m',0};
    static const WCHAR test_part_url[] = {'r','e','s',':','/','/','C','S','S','/','t','e','s','t',0};
    static const WCHAR wrong_url1[] =
        {'m','s','h','t','m','l','.','d','l','l','/','b','l','a','n','k','.','m','t','h',0};
    static const WCHAR wrong_url2[] =
        {'r','e','s',':','/','/','m','s','h','t','m','l','.','d','l','l',0};
    static const WCHAR wrong_url3[] =
        {'r','e','s',':','/','/','m','s','h','t','m','l','.','d','l','l','/','x','x','.','h','t','m',0};
    static const WCHAR wrong_url4[] =
        {'r','e','s',':','/','/','x','x','.','d','l','l','/','b','l','a','n','k','.','h','t','m',0};
    static const WCHAR wrong_url5[] =
        {'r','e','s',':','/','/','s','h','t','m','l','.','d','l','l','/','b','l','a','n','k','.','h','t','m',0};
    static const WCHAR wrong_url6[] =
        {'r','e','s',':','/','/','c',':','\\','d','i','r','\\','f','i','l','e','.','d','l','l','/','b','l','a','n','k','.','h','t','m',0};
    static const WCHAR mshtml_dllW[] = {'m','s','h','t','m','l','.','d','l','l',0};

    hres = CoGetClassObject(&CLSID_ResProtocol, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "CoGetClassObject failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IUnknown_QueryInterface(unk, &IID_IInternetProtocolInfo, (void**)&protocol_info);
    ok(hres == S_OK, "Could not get IInternetProtocolInfo interface: %08x\n", hres);
    if(SUCCEEDED(hres)) {
        WCHAR buf[128];
        DWORD size, expected_size;
        int i;

        for(i = PARSE_CANONICALIZE; i <= PARSE_UNESCAPE; i++) {
            if(i != PARSE_SECURITY_URL && i != PARSE_DOMAIN) {
                hres = IInternetProtocolInfo_ParseUrl(protocol_info, blank_url, i, 0, buf,
                        sizeof(buf)/sizeof(buf[0]), &size, 0);
                ok(hres == INET_E_DEFAULT_ACTION,
                        "[%d] failed: %08x, expected INET_E_DEFAULT_ACTION\n", i, hres);
            }
        }

        hres = IInternetProtocolInfo_ParseUrl(protocol_info, blank_url, PARSE_SECURITY_URL, 0, buf,
                sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == S_OK, "ParseUrl failed: %08x\n", hres);
        res_sec_url_cmp(buf, size, mshtml_dllW);
        ok(size == lstrlenW(buf)+1, "size = %d\n", size);
        expected_size = size;

        hres = IInternetProtocolInfo_ParseUrl(protocol_info, blank_url, PARSE_SECURITY_URL, 0, buf,
                expected_size, &size, 0);
        ok(hres == S_OK, "ParseUrl failed: %08x\n", hres);
        res_sec_url_cmp(buf, size, mshtml_dllW);
        ok(size == expected_size, "size = %d\n", size);

        size = 0;
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, blank_url, PARSE_SECURITY_URL, 0, buf,
                3, &size, 0);
        ok(hres == S_FALSE, "ParseUrl failed: %08x, expected S_FALSE\n", hres);
        ok(size == expected_size, "size = %d\n", size);

        hres = IInternetProtocolInfo_ParseUrl(protocol_info, wrong_url1, PARSE_SECURITY_URL, 0, buf,
                sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == MK_E_SYNTAX || hres == E_INVALIDARG,
           "ParseUrl failed: %08x, expected MK_E_SYNTAX\n", hres);

        hres = IInternetProtocolInfo_ParseUrl(protocol_info, wrong_url5, PARSE_SECURITY_URL, 0, buf,
                sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == MK_E_SYNTAX, "ParseUrl failed: %08x, expected MK_E_SYNTAX\n", hres);

        hres = IInternetProtocolInfo_ParseUrl(protocol_info, wrong_url6, PARSE_SECURITY_URL, 0, buf,
                sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == MK_E_SYNTAX, "ParseUrl failed: %08x, expected MK_E_SYNTAX\n", hres);

        size = 0xdeadbeef;
        buf[0] = '?';
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, blank_url, PARSE_DOMAIN, 0, buf,
                sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == S_OK || hres == E_FAIL, "ParseUrl failed: %08x\n", hres);
        ok(buf[0] == '?', "buf changed\n");
        ok(size == sizeof(blank_url)/sizeof(WCHAR) ||
           size == sizeof(buf)/sizeof(buf[0]), /* IE8 */
           "size=%d\n", size);

        size = 0xdeadbeef;
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, wrong_url1, PARSE_DOMAIN, 0, buf,
                sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == S_OK || hres == E_FAIL, "ParseUrl failed: %08x\n", hres);
        ok(buf[0] == '?', "buf changed\n");
        ok(size == sizeof(wrong_url1)/sizeof(WCHAR) ||
           size == sizeof(buf)/sizeof(buf[0]), /* IE8 */
           "size=%d\n", size);

        if (0)
        {
        /* Crashes on windows */
        size = 0xdeadbeef;
        buf[0] = '?';
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, NULL, PARSE_DOMAIN, 0, buf,
                sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == E_FAIL, "ParseUrl failed: %08x\n", hres);
        ok(buf[0] == '?', "buf changed\n");
        ok(size == 1, "size=%u, expected 1\n", size);

        buf[0] = '?';
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, blank_url, PARSE_DOMAIN, 0, buf,
                sizeof(buf)/sizeof(buf[0]), NULL, 0);
        ok(hres == E_POINTER, "ParseUrl failed: %08x\n", hres);
        ok(buf[0] == '?', "buf changed\n");

        buf[0] = '?';
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, NULL, PARSE_DOMAIN, 0, buf,
                sizeof(buf)/sizeof(buf[0]), NULL, 0);
        ok(hres == E_POINTER, "ParseUrl failed: %08x\n", hres);
        ok(buf[0] == '?', "buf changed\n");
        }

        buf[0] = '?';
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, blank_url, PARSE_UNESCAPE+1, 0, buf,
                sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == INET_E_DEFAULT_ACTION,
                "ParseUrl failed: %08x, expected INET_E_DEFAULT_ACTION\n", hres);
        ok(buf[0] == '?', "buf changed\n");

        size = 0xdeadbeef;
        hres = IInternetProtocolInfo_CombineUrl(protocol_info, blank_url, test_part_url,
                0, buf, sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER, "CombineUrl failed: %08x\n", hres);
        ok(size == 0xdeadbeef, "size=%d\n", size);

        size = 0xdeadbeef;
        hres = IInternetProtocolInfo_CombineUrl(protocol_info, blank_url, test_part_url,
                URL_FILE_USE_PATHURL, buf, sizeof(buf)/sizeof(buf[0]), &size, 0);
        ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER, "CombineUrl failed: %08x\n", hres);
        ok(size == 0xdeadbeef, "size=%d\n", size);

        size = 0xdeadbeef;
        hres = IInternetProtocolInfo_CombineUrl(protocol_info, NULL, NULL,
                URL_FILE_USE_PATHURL, NULL, 0xdeadbeef, NULL, 0);
        ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER, "CombineUrl failed: %08x\n", hres);
        ok(size == 0xdeadbeef, "size=%d\n", size);

        hres = IInternetProtocolInfo_CompareUrl(protocol_info, blank_url, blank_url, 0);
        ok(hres == E_NOTIMPL, "CompareUrl failed: %08x\n", hres);

        hres = IInternetProtocolInfo_CompareUrl(protocol_info, NULL, NULL, 0xdeadbeef);
        ok(hres == E_NOTIMPL, "CompareUrl failed: %08x\n", hres);

        for(i=0; i<30; i++) {
            if(i == QUERY_USES_NETWORK || i == QUERY_IS_SECURE || i == QUERY_IS_SAFE)
                continue;

            hres = IInternetProtocolInfo_QueryInfo(protocol_info, blank_url, i, 0,
                                                   buf, sizeof(buf), &size, 0);
            ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER,
               "QueryInfo(%d) returned: %08x, expected INET_E_USE_DEFAULT_PROTOCOLHANDLER\n", i, hres);
        }

        size = 0xdeadbeef;
        memset(buf, '?', sizeof(buf));
        hres = IInternetProtocolInfo_QueryInfo(protocol_info, blank_url, QUERY_USES_NETWORK, 0,
                                               buf, sizeof(buf), &size, 0);
        ok(hres == S_OK, "QueryInfo(QUERY_USES_NETWORK) failed: %08x\n", hres);
        ok(size == sizeof(DWORD), "size=%d\n", size);
        ok(!*(DWORD*)buf, "buf=%d\n", *(DWORD*)buf);

        memset(buf, '?', sizeof(buf));
        hres = IInternetProtocolInfo_QueryInfo(protocol_info, blank_url, QUERY_USES_NETWORK, 0,
                                               buf, sizeof(buf), NULL, 0);
        ok(hres == S_OK, "QueryInfo(QUERY_USES_NETWORK) failed: %08x\n", hres);
        ok(!*(DWORD*)buf, "buf=%d\n", *(DWORD*)buf);

        hres = IInternetProtocolInfo_QueryInfo(protocol_info, blank_url, QUERY_USES_NETWORK, 0,
                                               buf, 3, &size, 0);
        ok(hres == E_FAIL, "QueryInfo(QUERY_USES_NETWORK) failed: %08x, expected E_FAIL\n", hres);

        size = 0xdeadbeef;
        memset(buf, '?', sizeof(buf));
        hres = IInternetProtocolInfo_QueryInfo(protocol_info, NULL, QUERY_USES_NETWORK, 0,
                                               buf, sizeof(buf), &size, 0);
        ok(hres == S_OK, "QueryInfo(QUERY_USES_NETWORK) failed: %08x\n", hres);
        ok(size == sizeof(DWORD), "size=%d\n", size);
        ok(!*(DWORD*)buf, "buf=%d\n", *(DWORD*)buf);

        hres = IInternetProtocolInfo_QueryInfo(protocol_info, blank_url, QUERY_USES_NETWORK, 0,
                                               NULL, sizeof(buf), &size, 0);
        ok(hres == E_FAIL, "QueryInfo(QUERY_USES_NETWORK) failed: %08x, expected E_FAIL\n", hres);

        hres = IInternetProtocolInfo_QueryInfo(protocol_info, blank_url, 60, 0,
                                               NULL, sizeof(buf), &size, 0);
        ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER,
           "QueryInfo failed: %08x, expected INET_E_USE_DEFAULT_PROTOCOLHANDLER\n", hres);

        IInternetProtocolInfo_Release(protocol_info);
    }

    hres = IUnknown_QueryInterface(unk, &IID_IClassFactory, (void**)&factory);
    ok(hres == S_OK, "Could not get IClassFactory interface\n");
    if(SUCCEEDED(hres)) {
        IInternetProtocol *protocol;
        BYTE buf[512];
        ULONG cb;
        hres = IClassFactory_CreateInstance(factory, NULL, &IID_IInternetProtocol, (void**)&protocol);
        ok(hres == S_OK, "Could not get IInternetProtocol: %08x\n", hres);

        if(SUCCEEDED(hres)) {
            IInternetPriority *priority;

            hres = IInternetProtocol_QueryInterface(protocol, &IID_IInternetPriority, (void**)&priority);
            ok(hres == E_NOINTERFACE,
               "QueryInterface(IInternetPriority) returned %08x, expected E_NOINTEFACE\n", hres);

            test_protocol_fail(protocol, wrong_url1, E_INVALIDARG, FALSE);
            test_protocol_fail(protocol, wrong_url2,
                               HRESULT_FROM_WIN32(ERROR_RESOURCE_TYPE_NOT_FOUND), FALSE);
            test_protocol_fail(protocol, wrong_url3, E_FAIL, TRUE);
            test_protocol_fail(protocol, wrong_url4, E_FAIL, TRUE);

            cb = 0xdeadbeef;
            hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
            ok(hres == E_FAIL, "Read returned %08x expected E_FAIL\n", hres);
            ok(cb == 0xdeadbeef, "cb=%u expected 0xdeadbeef\n", cb);
    
            protocol_start(protocol, blank_url);
            hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
            ok(hres == S_OK, "Read failed: %08x\n", hres);
            ok(cb == 2, "cb=%u expected 2\n", cb);
            hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
            ok(hres == S_OK, "Read failed: %08x\n", hres);
            hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
            ok(hres == S_FALSE, "Read failed: %08x expected S_FALSE\n", hres);
            ok(cb == 0, "cb=%u expected 0\n", cb);
            hres = IInternetProtocol_UnlockRequest(protocol);
            ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);

            protocol_start(protocol, blank_url);
            hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
            ok(hres == S_OK, "Read failed: %08x\n", hres);
            hres = IInternetProtocol_LockRequest(protocol, 0);
            ok(hres == S_OK, "LockRequest failed: %08x\n", hres);
            hres = IInternetProtocol_UnlockRequest(protocol);
            ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);
            hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
            ok(hres == S_OK, "Read failed: %08x\n", hres);

            protocol_start(protocol, blank_url);
            hres = IInternetProtocol_LockRequest(protocol, 0);
            ok(hres == S_OK, "LockRequest failed: %08x\n", hres);
            hres = IInternetProtocol_Terminate(protocol, 0);
            ok(hres == S_OK, "Terminate failed: %08x\n", hres);
            hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
            ok(hres == S_OK, "Read failed: %08x\n\n", hres);
            hres = IInternetProtocol_UnlockRequest(protocol);
            ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);
            hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
            ok(hres == S_OK, "Read failed: %08x\n", hres);
            hres = IInternetProtocol_Terminate(protocol, 0);
            ok(hres == S_OK, "Terminate failed: %08x\n", hres);
            hres = IInternetProtocol_Read(protocol, buf, 2, &cb);
            ok(hres == S_OK, "Read failed: %08x\n", hres);
            ok(cb == 2, "cb=%u expected 2\n", cb);

            protocol_start(protocol, blank_url);
            hres = IInternetProtocol_LockRequest(protocol, 0);
            ok(hres == S_OK, "LockRequest failed: %08x\n", hres);
            hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
            ok(hres == S_OK, "Read failed: %08x\n", hres);
            protocol_start(protocol, blank_url);
            hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &cb);
            ok(hres == S_OK, "Read failed: %08x\n", hres);
            hres = IInternetProtocol_Terminate(protocol, 0);
            ok(hres == S_OK, "Terminate failed: %08x\n", hres);

            IInternetProtocol_Release(protocol);
        }

        IClassFactory_Release(factory);
    }

    IUnknown_Release(unk);

    test_res_url("/jstest.html");
    test_res_url("/Test/res.html");
    test_res_url("/test/dir/dir2/res.html");

    if(GetProcAddress(LoadLibraryA("urlmon.dll"), "CreateUri")) {
        test_res_url("/test/dir/dir2/res.html?query_part");
        test_res_url("/test/dir/dir2/res.html#hash_part");
        test_res_url("/#123");
        test_res_url("/#23/#123");
        test_res_url("/#123#456");
    }else {
        win_skip("IUri not supported\n");
    }
}