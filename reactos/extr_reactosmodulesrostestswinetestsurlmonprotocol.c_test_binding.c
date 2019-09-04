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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IInternetSession ;
typedef  int /*<<< orphan*/  IInternetProtocolEx ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  Abort ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClassFactory ; 
 int /*<<< orphan*/  Continue ; 
 int /*<<< orphan*/  CreateInstance ; 
 int /*<<< orphan*/  E_ABORT ; 
 int HTTPS_TEST ; 
 int HTTP_TEST ; 
 int /*<<< orphan*/  IID_IInternetBindInfo ; 
 int /*<<< orphan*/  IID_IInternetProtocolEx ; 
 int /*<<< orphan*/  IID_IInternetProtocolSink ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  IInternetBindInfo_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolEx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetProtocolEx_StartEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolSink_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetProtocol_Abort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocol_Continue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetProtocol_LockRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetProtocol_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IInternetProtocol_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetProtocol_Start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetProtocol_Terminate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetProtocol_UnlockRequest (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetSession_CreateBinding (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetSession_RegisterNameSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetSession_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetSession_UnregisterNameSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockRequest ; 
 int /*<<< orphan*/  MimeFilter_LockRequest ; 
 int /*<<< orphan*/  MimeFilter_Terminate ; 
 int /*<<< orphan*/  MimeFilter_UnlockRequest ; 
 int /*<<< orphan*/  Protocol_destructor ; 
 int /*<<< orphan*/  QueryService_InternetProtocol ; 
 int /*<<< orphan*/  ReportData ; 
 int /*<<< orphan*/  ReportProgress_PROTOCOLCLASSID ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPriority ; 
 int /*<<< orphan*/  Start ; 
 int /*<<< orphan*/  StartEx ; 
 int TEST_BINDING ; 
 int TEST_EMULATEPROT ; 
 int TEST_USEIURI ; 
 int /*<<< orphan*/  Terminate ; 
 int /*<<< orphan*/  UnlockRequest ; 
 int /*<<< orphan*/  Uri_CREATE_FILE_USE_DOS_PATH ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bind_info ; 
 int /*<<< orphan*/ * binding_protocol ; 
 int /*<<< orphan*/  binding_sink ; 
 int /*<<< orphan*/ * binding_urls ; 
 scalar_t__ direct_read ; 
 int /*<<< orphan*/  event_complete ; 
 int /*<<< orphan*/  event_complete2 ; 
 scalar_t__ ex_priority ; 
 scalar_t__ expect_hrResult ; 
 int /*<<< orphan*/ * filtered_protocol ; 
 scalar_t__ impl_protex ; 
 int /*<<< orphan*/  init_test (int,int) ; 
 scalar_t__ mimefilter_test ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCoInternetGetSession (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ pCreateUri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pdata ; 
 int pi ; 
 int /*<<< orphan*/  prot_bind_info ; 
 int prot_state ; 
 int /*<<< orphan*/ * protocol_names ; 
 int /*<<< orphan*/  protocol_sink ; 
 scalar_t__ test_abort ; 

__attribute__((used)) static void test_binding(int prot, DWORD grf_pi, DWORD test_flags)
{
    IInternetProtocolEx *protocolex = NULL;
    IInternetProtocol *protocol;
    IInternetSession *session;
    IUri *uri = NULL;
    ULONG ref;
    HRESULT hres;

    pi = grf_pi;

    init_test(prot, test_flags|TEST_BINDING);

    hres = pCoInternetGetSession(0, &session, 0);
    ok(hres == S_OK, "CoInternetGetSession failed: %08x\n", hres);

    if(test_flags & TEST_EMULATEPROT) {
        hres = IInternetSession_RegisterNameSpace(session, &ClassFactory, &IID_NULL, protocol_names[prot], 0, NULL, 0);
        ok(hres == S_OK, "RegisterNameSpace failed: %08x\n", hres);
    }

    hres = IInternetSession_CreateBinding(session, NULL, binding_urls[prot], NULL, NULL, &protocol, 0);
    binding_protocol = protocol;
    ok(hres == S_OK, "CreateBinding failed: %08x\n", hres);
    ok(protocol != NULL, "protocol == NULL\n");

    hres = IInternetProtocol_QueryInterface(protocol, &IID_IInternetBindInfo, (void**)&prot_bind_info);
    ok(hres == S_OK, "QueryInterface(IID_IInternetBindInfo) failed: %08x\n", hres);

    hres = IInternetProtocol_QueryInterface(protocol, &IID_IInternetProtocolSink, (void**)&binding_sink);
    ok(hres == S_OK, "QueryInterface(IID_IInternetProtocolSink) failed: %08x\n", hres);

    if(test_flags & TEST_USEIURI) {
        hres = IInternetProtocol_QueryInterface(protocol, &IID_IInternetProtocolEx, (void**)&protocolex);
        ok(hres == S_OK, "Could not get IInternetProtocolEx iface: %08x\n", hres);

        hres = pCreateUri(binding_urls[prot], Uri_CREATE_FILE_USE_DOS_PATH, 0, &uri);
        ok(hres == S_OK, "CreateUri failed: %08x\n", hres);
    }

    ex_priority = 0;
    SET_EXPECT(QueryService_InternetProtocol);
    SET_EXPECT(CreateInstance);
    SET_EXPECT(ReportProgress_PROTOCOLCLASSID);
    SET_EXPECT(SetPriority);
    if(impl_protex)
        SET_EXPECT(StartEx);
    else
        SET_EXPECT(Start);

    expect_hrResult = S_OK;

    if(protocolex) {
        hres = IInternetProtocolEx_StartEx(protocolex, uri, &protocol_sink, &bind_info, pi, 0);
        ok(hres == S_OK, "StartEx failed: %08x\n", hres);
    }else {
        hres = IInternetProtocol_Start(protocol, binding_urls[prot], &protocol_sink, &bind_info, pi, 0);
        ok(hres == S_OK, "Start failed: %08x\n", hres);
    }

    CHECK_CALLED(QueryService_InternetProtocol);
    CHECK_CALLED(CreateInstance);
    CHECK_CALLED(ReportProgress_PROTOCOLCLASSID);
    CLEAR_CALLED(SetPriority); /* IE11 does not call it. */
    if(impl_protex)
        CHECK_CALLED(StartEx);
    else
        CHECK_CALLED(Start);

    if(protocolex)
        IInternetProtocolEx_Release(protocolex);
    if(uri)
        IUri_Release(uri);

    if(prot == HTTP_TEST || prot == HTTPS_TEST) {
        while(prot_state < 4) {
            ok( WaitForSingleObject(event_complete, 90000) == WAIT_OBJECT_0, "wait timed out\n" );
            if(mimefilter_test && filtered_protocol) {
                SET_EXPECT(Continue);
                IInternetProtocol_Continue(filtered_protocol, pdata);
                CHECK_CALLED(Continue);
            }else {
                SET_EXPECT(Continue);
                IInternetProtocol_Continue(protocol, pdata);
                CHECK_CALLED(Continue);
            }
            if(test_abort && prot_state == 2) {
                SET_EXPECT(Abort);
                hres = IInternetProtocol_Abort(protocol, E_ABORT, 0);
                ok(hres == S_OK, "Abort failed: %08x\n", hres);
                CHECK_CALLED(Abort);

                hres = IInternetProtocol_Abort(protocol, E_ABORT, 0);
                ok(hres == S_OK, "Abort failed: %08x\n", hres);
                SetEvent(event_complete2);
                break;
            }
            SetEvent(event_complete2);
        }
        if(direct_read)
            CHECK_CALLED(ReportData); /* Set in ReportResult */
        ok( WaitForSingleObject(event_complete, 90000) == WAIT_OBJECT_0, "wait timed out\n" );
    }else {
        if(mimefilter_test)
            SET_EXPECT(MimeFilter_LockRequest);
        else
            SET_EXPECT(LockRequest);
        hres = IInternetProtocol_LockRequest(protocol, 0);
        ok(hres == S_OK, "LockRequest failed: %08x\n", hres);
        if(mimefilter_test)
            CHECK_CALLED(MimeFilter_LockRequest);
        else
            CHECK_CALLED(LockRequest);

        if(mimefilter_test)
            SET_EXPECT(MimeFilter_UnlockRequest);
        else
            SET_EXPECT(UnlockRequest);
        hres = IInternetProtocol_UnlockRequest(protocol);
        ok(hres == S_OK, "UnlockRequest failed: %08x\n", hres);
        if(mimefilter_test)
            CHECK_CALLED(MimeFilter_UnlockRequest);
        else
            CHECK_CALLED(UnlockRequest);
    }

    if(mimefilter_test)
        SET_EXPECT(MimeFilter_Terminate);
    else
        SET_EXPECT(Terminate);
    hres = IInternetProtocol_Terminate(protocol, 0);
    ok(hres == S_OK, "Terminate failed: %08x\n", hres);
    if(mimefilter_test)
        CLEAR_CALLED(MimeFilter_Terminate);
    else
        CHECK_CALLED(Terminate);

    if(filtered_protocol)
        IInternetProtocol_Release(filtered_protocol);
    IInternetBindInfo_Release(prot_bind_info);
    IInternetProtocolSink_Release(binding_sink);

    SET_EXPECT(Protocol_destructor);
    ref = IInternetProtocol_Release(protocol);
    ok(!ref, "ref=%u, expected 0\n", ref);
    CHECK_CALLED(Protocol_destructor);

    if(test_flags & TEST_EMULATEPROT) {
        hres = IInternetSession_UnregisterNameSpace(session, &ClassFactory, protocol_names[prot]);
        ok(hres == S_OK, "UnregisterNameSpace failed: %08x\n", hres);
    }

    IInternetSession_Release(session);
}