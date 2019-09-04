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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  ITfTextEditSink ;
typedef  int /*<<< orphan*/  ITfSource ;
typedef  int /*<<< orphan*/  ITfEditSession ;
typedef  int /*<<< orphan*/  ITfDocumentMgr ;
typedef  int /*<<< orphan*/  ITfContext ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACPSink ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  EditSession_Constructor (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_ITfSource ; 
 int /*<<< orphan*/  IID_ITfTextEditSink ; 
 int /*<<< orphan*/  ITextStoreACPSink_OnStatusChange (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ITfContext_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfContext_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITfContext_RequestEditSession (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  ITfDocumentMgr_GetTop (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITfDocumentMgr_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfEditSession_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITfSource_AdviseSink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ITfSource_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITfSource_UnadviseSink (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ITfTextEditSink_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfThreadMgr_GetFocus (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SINK_EXPECTED ; 
 int SUCCEEDED (scalar_t__) ; 
 int TF_ES_READWRITE ; 
 int TF_ES_SYNC ; 
 scalar_t__ TS_E_READONLY ; 
 scalar_t__ TS_SD_READONLY ; 
 int /*<<< orphan*/  TextEditSink_Constructor (int /*<<< orphan*/ **) ; 
 scalar_t__ documentStatus ; 
 int /*<<< orphan*/  g_tm ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sink_check_ok (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_ACP_GetStatus ; 
 int /*<<< orphan*/  test_ACP_RequestLock ; 
 int /*<<< orphan*/  test_DoEditSession ; 
 int /*<<< orphan*/  test_OnEndEdit ; 
 int /*<<< orphan*/  tid ; 

__attribute__((used)) static void test_TStoApplicationText(void)
{
    HRESULT hr, hrSession;
    ITfEditSession *es;
    ITfContext *cxt;
    ITfDocumentMgr *dm;
    ITfTextEditSink *sink;
    ITfSource *source = NULL;
    DWORD editSinkCookie = -1;

    ITfThreadMgr_GetFocus(g_tm, &dm);
    EditSession_Constructor(&es);
    ITfDocumentMgr_GetTop(dm,&cxt);

    TextEditSink_Constructor(&sink);
    hr = ITfContext_QueryInterface(cxt,&IID_ITfSource,(LPVOID*)&source);
    ok(SUCCEEDED(hr),"Failed to get IID_ITfSource for Context\n");
    if (source)
    {
        hr = ITfSource_AdviseSink(source, &IID_ITfTextEditSink, (LPVOID)sink, &editSinkCookie);
        ok(SUCCEEDED(hr),"Failed to advise Sink\n");
        ok(editSinkCookie != -1,"Failed to get sink cookie\n");
    }

    hrSession = 0xfeedface;
    /* Test no permissions flags */
    hr = ITfContext_RequestEditSession(cxt, tid, es, TF_ES_SYNC, &hrSession);
    ok(hr == E_INVALIDARG,"RequestEditSession should have failed with %x not %x\n",E_INVALIDARG,hr);
    ok(hrSession == E_FAIL,"hrSession should be %x not %x\n",E_FAIL,hrSession);

    documentStatus = TS_SD_READONLY;
    hrSession = 0xfeedface;
    test_ACP_GetStatus = SINK_EXPECTED;
    hr = ITfContext_RequestEditSession(cxt, tid, es, TF_ES_SYNC|TF_ES_READWRITE, &hrSession);
    ok(SUCCEEDED(hr),"ITfContext_RequestEditSession failed\n");
    ok(hrSession == TS_E_READONLY,"Unexpected hrSession (%x)\n",hrSession);
    sink_check_ok(&test_ACP_GetStatus,"GetStatus");

    /* signal a change to allow readwrite sessions */
    documentStatus = 0;
    test_ACP_RequestLock = SINK_EXPECTED;
    ITextStoreACPSink_OnStatusChange(ACPSink,documentStatus);
    sink_check_ok(&test_ACP_RequestLock,"RequestLock");

    test_ACP_GetStatus = SINK_EXPECTED;
    test_ACP_RequestLock = SINK_EXPECTED;
    test_DoEditSession = SINK_EXPECTED;
    hrSession = 0xfeedface;
    test_OnEndEdit = SINK_EXPECTED;
    hr = ITfContext_RequestEditSession(cxt, tid, es, TF_ES_SYNC|TF_ES_READWRITE, &hrSession);
    ok(SUCCEEDED(hr),"ITfContext_RequestEditSession failed\n");
    sink_check_ok(&test_OnEndEdit,"OnEndEdit");
    sink_check_ok(&test_DoEditSession,"DoEditSession");
    sink_check_ok(&test_ACP_GetStatus,"GetStatus");
    ok(hrSession == 0xdeadcafe,"Unexpected hrSession (%x)\n",hrSession);

    if (source)
    {
        hr = ITfSource_UnadviseSink(source, editSinkCookie);
        ok(SUCCEEDED(hr),"Failed to unadvise Sink\n");
        ITfSource_Release(source);
    }
    ITfTextEditSink_Release(sink);
    ITfContext_Release(cxt);
    ITfDocumentMgr_Release(dm);
    ITfEditSession_Release(es);
}