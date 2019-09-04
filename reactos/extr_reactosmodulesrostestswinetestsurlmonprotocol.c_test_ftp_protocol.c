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
typedef  float WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IInternetProtocolInfo ;
typedef  int /*<<< orphan*/  IInternetProtocolEx ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int BINDF_ASYNCHRONOUS ; 
 int BINDF_ASYNCSTORAGE ; 
 int BINDF_FROMURLMON ; 
 int BINDF_NOWRITECACHE ; 
 int BINDF_PULLDATA ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FtpProtocol ; 
 scalar_t__ CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ E_PENDING ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FTP_TEST ; 
 int /*<<< orphan*/  GetBindInfo ; 
 scalar_t__ IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 int /*<<< orphan*/  IID_IInternetProtocolEx ; 
 int /*<<< orphan*/  IID_IInternetProtocolInfo ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IInternetProtocolEx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetProtocol_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IInternetProtocol_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ IInternetProtocol_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetProtocol_Start (int /*<<< orphan*/ ,float const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportProgress_CONNECTING ; 
 int /*<<< orphan*/  ReportProgress_FINDINGRESOURCE ; 
 int /*<<< orphan*/  ReportProgress_SENDINGREQUEST ; 
 int /*<<< orphan*/  ReportResult ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_STARTDOWNLOADING ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  Switch ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  async_protocol ; 
 int /*<<< orphan*/  bind_info ; 
 int bindf ; 
 int /*<<< orphan*/  event_complete ; 
 scalar_t__ expect_hrResult ; 
 int /*<<< orphan*/  init_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCreateUri ; 
 int /*<<< orphan*/  protocol_sink ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  test_early_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_priority (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_protocol_terminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_ftp_protocol(void)
{
    IInternetProtocolInfo *protocol_info;
    IClassFactory *factory;
    IUnknown *unk;
    BYTE buf[4096];
    ULONG ref;
    DWORD cb;
    HRESULT hres;

    static const WCHAR ftp_urlW[] = {'f','t','p',':','/','/','f','t','p','.','w','i','n','e','h','q','.','o','r','g',
    '/','p','u','b','/','o','t','h','e','r','/',
    'w','i','n','e','l','o','g','o','.','x','c','f','.','t','a','r','.','b','z','2',0};

    trace("Testing ftp protocol...\n");

    init_test(FTP_TEST, 0);

    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON | BINDF_NOWRITECACHE;
    state = STATE_STARTDOWNLOADING;
    expect_hrResult = E_PENDING;

    hres = CoGetClassObject(&CLSID_FtpProtocol, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "CoGetClassObject failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IUnknown_QueryInterface(unk, &IID_IInternetProtocolInfo, (void**)&protocol_info);
    ok(hres == E_NOINTERFACE, "Could not get IInternetProtocolInfo interface: %08x, expected E_NOINTERFACE\n", hres);

    hres = IUnknown_QueryInterface(unk, &IID_IClassFactory, (void**)&factory);
    ok(hres == S_OK, "Could not get IClassFactory interface\n");
    IUnknown_Release(unk);
    if(FAILED(hres))
        return;

    hres = IClassFactory_CreateInstance(factory, NULL, &IID_IInternetProtocol,
                                        (void**)&async_protocol);
    IClassFactory_Release(factory);
    ok(hres == S_OK, "Could not get IInternetProtocol: %08x\n", hres);

    test_priority(async_protocol);

    SET_EXPECT(GetBindInfo);
    SET_EXPECT(ReportProgress_FINDINGRESOURCE);
    SET_EXPECT(ReportProgress_CONNECTING);
    SET_EXPECT(ReportProgress_SENDINGREQUEST);
    SET_EXPECT(Switch);

    hres = IInternetProtocol_Start(async_protocol, ftp_urlW, &protocol_sink, &bind_info, 0, 0);
    ok(hres == S_OK, "Start failed: %08x\n", hres);
    CHECK_CALLED(GetBindInfo);

    SET_EXPECT(ReportResult);

    hres = IInternetProtocol_Read(async_protocol, buf, 1, &cb);
    ok((hres == E_PENDING && cb==0) ||
       (hres == S_OK && cb==1), "Read failed: %08x (%d bytes)\n", hres, cb);

    ok( WaitForSingleObject(event_complete, 90000) == WAIT_OBJECT_0, "wait timed out\n" );

    while(1) {
        hres = IInternetProtocol_Read(async_protocol, buf, sizeof(buf), &cb);
        if(hres == E_PENDING)
        {
            DWORD ret = WaitForSingleObject(event_complete, 90000);
            ok( ret == WAIT_OBJECT_0, "wait timed out\n" );
            if (ret != WAIT_OBJECT_0) break;
        }
        else
            if(cb == 0) break;
    }

    ok(hres == S_FALSE, "Read failed: %08x\n", hres);
    CHECK_CALLED(ReportResult);
    CHECK_CALLED(Switch);

    test_protocol_terminate(async_protocol);

    if(pCreateUri) {
        IInternetProtocolEx *protocolex;

        hres = IInternetProtocol_QueryInterface(async_protocol, &IID_IInternetProtocolEx, (void**)&protocolex);
        ok(hres == S_OK, "Could not get IInternetProtocolEx iface: %08x\n", hres);
        IInternetProtocolEx_Release(protocolex);
    }

    ref = IInternetProtocol_Release(async_protocol);
    ok(!ref, "ref=%d\n", ref);

    test_early_abort(&CLSID_FtpProtocol);
}