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
typedef  char WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IInternetProtocolInfo ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int BINDF_FROMURLMON ; 
 int BINDF_NEEDFILE ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ITSProtocol ; 
 scalar_t__ CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 int /*<<< orphan*/  IID_IInternetProtocolInfo ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IInternetProtocol_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetProtocol_Start (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INET_E_USE_DEFAULT_PROTOCOLHANDLER ; 
 int /*<<< orphan*/  ITS_PROTOCOL ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 int /*<<< orphan*/  STG_E_FILENOTFOUND ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bind_info ; 
 int bindf ; 
 int /*<<< orphan*/  blank_url1 ; 
 int /*<<< orphan*/  blank_url2 ; 
 int /*<<< orphan*/  blank_url3 ; 
 int /*<<< orphan*/  blank_url4 ; 
 int /*<<< orphan*/  blank_url5 ; 
 int /*<<< orphan*/  blank_url6 ; 
 int /*<<< orphan*/  blank_url8 ; 
 int /*<<< orphan*/  blank_url9 ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  protocol_sink ; 
 int /*<<< orphan*/  test_its_protocol_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_protocol ; 
 int /*<<< orphan*/  test_protocol_fail (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_protocol_url (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_its_protocol(void)
{
    IInternetProtocolInfo *info;
    IClassFactory *factory;
    IUnknown *unk;
    ULONG ref;
    HRESULT hres;

    static const WCHAR wrong_url1[] =
        {'i','t','s',':','t','e','s','t','.','c','h','m',':',':','/','b','l','a','n','.','h','t','m','l',0};
    static const WCHAR wrong_url2[] =
        {'i','t','s',':','t','e','s','.','c','h','m',':',':','b','/','l','a','n','k','.','h','t','m','l',0};
    static const WCHAR wrong_url3[] =
        {'i','t','s',':','t','e','s','t','.','c','h','m','/','b','l','a','n','k','.','h','t','m','l',0};
    static const WCHAR wrong_url4[] = {'m','k',':','@','M','S','I','T','S','t','o','r',':',
         't','e','s','t','.','c','h','m',':',':','/','b','l','a','n','k','.','h','t','m','l',0};
    static const WCHAR wrong_url5[] = {'f','i','l','e',':',
        't','e','s','.','c','h','m',':',':','/','b','l','a','n','k','.','h','t','m','l',0};

    test_protocol = ITS_PROTOCOL;

    hres = CoGetClassObject(&CLSID_ITSProtocol, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK ||
       broken(hres == REGDB_E_CLASSNOTREG), /* Some W95 and NT4 */
       "CoGetClassObject failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IUnknown_QueryInterface(unk, &IID_IInternetProtocolInfo, (void**)&info);
    ok(hres == E_NOINTERFACE, "Could not get IInternetProtocolInfo: %08x\n", hres);

    hres = IUnknown_QueryInterface(unk, &IID_IClassFactory, (void**)&factory);
    ok(hres == S_OK, "Could not get IClassFactory interface\n");
    if(SUCCEEDED(hres)) {
        IInternetProtocol *protocol;

        hres = IClassFactory_CreateInstance(factory, NULL, &IID_IInternetProtocol, (void**)&protocol);
        ok(hres == S_OK, "Could not get IInternetProtocol: %08x\n", hres);
        if(SUCCEEDED(hres)) {
            test_its_protocol_info(protocol);

            test_protocol_fail(protocol, wrong_url1, STG_E_FILENOTFOUND);
            test_protocol_fail(protocol, wrong_url2, STG_E_FILENOTFOUND);
            test_protocol_fail(protocol, wrong_url3, STG_E_FILENOTFOUND);

            hres = IInternetProtocol_Start(protocol, wrong_url4, &protocol_sink, &bind_info, 0, 0);
            ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER,
               "Start failed: %08x, expected INET_E_USE_DEFAULT_PROTOCOLHANDLER\n", hres);

            hres = IInternetProtocol_Start(protocol, wrong_url5, &protocol_sink, &bind_info, 0, 0);
            ok(hres == INET_E_USE_DEFAULT_PROTOCOLHANDLER,
               "Start failed: %08x, expected INET_E_USE_DEFAULT_PROTOCOLHANDLER\n", hres);

            ref = IInternetProtocol_Release(protocol);
            ok(!ref, "protocol ref=%d\n", ref);

            test_protocol_url(factory, blank_url1, TRUE);
            test_protocol_url(factory, blank_url2, TRUE);
            test_protocol_url(factory, blank_url3, TRUE);
            test_protocol_url(factory, blank_url4, TRUE);
            test_protocol_url(factory, blank_url5, TRUE);
            test_protocol_url(factory, blank_url6, TRUE);
            test_protocol_url(factory, blank_url8, TRUE);
            test_protocol_url(factory, blank_url9, TRUE);
            bindf = BINDF_FROMURLMON | BINDF_NEEDFILE;
            test_protocol_url(factory, blank_url1, TRUE);
        }

        IClassFactory_Release(factory);
    }

    IUnknown_Release(unk);
}