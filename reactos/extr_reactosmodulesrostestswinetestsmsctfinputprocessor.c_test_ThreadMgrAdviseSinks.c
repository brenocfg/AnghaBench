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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITfSource ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_ITfKeyTraceEventSink ; 
 int /*<<< orphan*/  IID_ITfSource ; 
 int /*<<< orphan*/  IID_ITfThreadMgrEventSink ; 
 scalar_t__ ITfSource_AdviseSink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITfSource_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITfThreadMgr_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TfKeyTraceEventSink ; 
 scalar_t__ ThreadMgrEventSink_Constructor (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_tm ; 
 scalar_t__ key_trace_sink_cookie ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ tmSinkCookie ; 
 int tmSinkRefCount ; 

__attribute__((used)) static void test_ThreadMgrAdviseSinks(void)
{
    ITfSource *source = NULL;
    HRESULT hr;
    IUnknown *sink;

    hr = ITfThreadMgr_QueryInterface(g_tm, &IID_ITfSource, (LPVOID*)&source);
    ok(SUCCEEDED(hr),"Failed to get IID_ITfSource for ThreadMgr\n");
    if (!source)
        return;

    hr = ThreadMgrEventSink_Constructor(&sink);
    ok(hr == S_OK, "got %08x\n", hr);
    if(FAILED(hr)) return;

    tmSinkRefCount = 1;
    tmSinkCookie = 0;
    hr = ITfSource_AdviseSink(source,&IID_ITfThreadMgrEventSink, sink, &tmSinkCookie);
    ok(hr == S_OK, "Failed to Advise Sink\n");
    ok(tmSinkCookie!=0,"Failed to get sink cookie\n");

    /* Advising the sink adds a ref, Releasing here lets the object be deleted
       when unadvised */
    tmSinkRefCount = 2;
    IUnknown_Release(sink);

    hr = ITfSource_AdviseSink(source, &IID_ITfKeyTraceEventSink, (IUnknown*)&TfKeyTraceEventSink,
                              &key_trace_sink_cookie);
    ok(hr == S_OK, "Failed to Advise Sink\n");

    ITfSource_Release(source);
}