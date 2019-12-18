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
typedef  int /*<<< orphan*/  ITfSource ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IID_ITfSource ; 
 int /*<<< orphan*/  ITfSource_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITfSource_UnadviseSink (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ITfThreadMgr_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  g_tm ; 
 int /*<<< orphan*/  key_trace_sink_cookie ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  profile_activation_sink_cookie ; 
 int /*<<< orphan*/  tmSinkCookie ; 
 int tmSinkRefCount ; 
 int /*<<< orphan*/  ui_element_sink_cookie ; 

__attribute__((used)) static void test_ThreadMgrUnadviseSinks(void)
{
    ITfSource *source = NULL;
    HRESULT hr;

    hr = ITfThreadMgr_QueryInterface(g_tm, &IID_ITfSource, (LPVOID*)&source);
    ok(SUCCEEDED(hr),"Failed to get IID_ITfSource for ThreadMgr\n");
    if (!source)
        return;

    tmSinkRefCount = 1;
    hr = ITfSource_UnadviseSink(source, tmSinkCookie);
    ok(hr == S_OK, "Failed to unadvise ITfThreadMgrEventSink\n");

    hr = ITfSource_UnadviseSink(source, key_trace_sink_cookie);
    ok(hr == S_OK, "Failed to unadvise ITfKeyTraceEventSink\n");

    hr = ITfSource_UnadviseSink(source, ui_element_sink_cookie);
    ok(hr == S_OK, "Failed to unadvise ITfUIElementSink\n");

    hr = ITfSource_UnadviseSink(source, profile_activation_sink_cookie);
    ok(hr == S_OK, "Failed to unadvise ITfInputProcessorProfileActivationSink\n");

    ITfSource_Release(source);
}