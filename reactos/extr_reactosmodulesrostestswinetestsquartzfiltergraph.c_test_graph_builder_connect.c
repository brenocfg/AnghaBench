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
typedef  int /*<<< orphan*/  IVideoWindow ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IFilterGraph2 ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_VideoRenderer ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IBaseFilter_FindPin (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IFilterGraph2_AddFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IFilterGraph2_AddSourceFilter (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IFilterGraph2_Connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFilterGraph2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBaseFilter ; 
 int /*<<< orphan*/  IID_IVideoWindow ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IVideoWindow_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IVideoWindow_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_graph () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  rungraph (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT test_graph_builder_connect(WCHAR *filename)
{
    static const WCHAR outputW[] = {'O','u','t','p','u','t',0};
    static const WCHAR inW[] = {'I','n',0};
    IBaseFilter *source_filter, *video_filter;
    IPin *pin_in, *pin_out;
    IFilterGraph2 *graph;
    IVideoWindow *window;
    HRESULT hr;

    graph = create_graph();

    hr = CoCreateInstance(&CLSID_VideoRenderer, NULL, CLSCTX_INPROC_SERVER, &IID_IVideoWindow, (void **)&window);
    ok(hr == S_OK, "Failed to create VideoRenderer: %#x\n", hr);

    hr = IFilterGraph2_AddSourceFilter(graph, filename, NULL, &source_filter);
    ok(hr == S_OK, "AddSourceFilter failed: %#x\n", hr);

    hr = IVideoWindow_QueryInterface(window, &IID_IBaseFilter, (void **)&video_filter);
    ok(hr == S_OK, "QueryInterface(IBaseFilter) failed: %#x\n", hr);
    hr = IFilterGraph2_AddFilter(graph, video_filter, NULL);
    ok(hr == S_OK, "AddFilter failed: %#x\n", hr);

    hr = IBaseFilter_FindPin(source_filter, outputW, &pin_out);
    ok(hr == S_OK, "FindPin failed: %#x\n", hr);
    hr = IBaseFilter_FindPin(video_filter, inW, &pin_in);
    ok(hr == S_OK, "FindPin failed: %#x\n", hr);
    hr = IFilterGraph2_Connect(graph, pin_out, pin_in);

    if (SUCCEEDED(hr))
        rungraph(graph);

    IPin_Release(pin_in);
    IPin_Release(pin_out);
    IBaseFilter_Release(source_filter);
    IBaseFilter_Release(video_filter);
    IVideoWindow_Release(window);
    IFilterGraph2_Release(graph);

    return hr;
}