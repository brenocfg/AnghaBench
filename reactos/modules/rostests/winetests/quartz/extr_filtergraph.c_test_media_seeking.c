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
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  IMediaSeeking ;
typedef  int /*<<< orphan*/  IMediaFilter ;
typedef  int /*<<< orphan*/  IFilterGraph2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  AM_SEEKING_AbsolutePositioning ; 
 int /*<<< orphan*/  AM_SEEKING_NoPositioning ; 
 int /*<<< orphan*/  AM_SEEKING_ReturnTime ; 
 int /*<<< orphan*/  GUID_NULL ; 
 scalar_t__ IFilterGraph2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IFilterGraph2_SetDefaultSyncSource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IMediaFilter ; 
 int /*<<< orphan*/  IID_IMediaSeeking ; 
 int /*<<< orphan*/  IMediaFilter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaFilter_SetSyncSource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaSeeking_ConvertTimeFormat (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaSeeking_GetCurrentPosition (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ IMediaSeeking_GetDuration (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ IMediaSeeking_GetStopPosition (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ IMediaSeeking_GetTimeFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaSeeking_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaSeeking_SetPositions (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TIME_FORMAT_MEDIA_TIME ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/ *) ; 
 scalar_t__ wine_dbgstr_longlong (int) ; 

__attribute__((used)) static void test_media_seeking(IFilterGraph2 *graph)
{
    IMediaSeeking *seeking;
    IMediaFilter *filter;
    LONGLONG pos, stop, duration;
    GUID format;
    HRESULT hr;

    IFilterGraph2_SetDefaultSyncSource(graph);
    hr = IFilterGraph2_QueryInterface(graph, &IID_IMediaSeeking, (void **)&seeking);
    ok(hr == S_OK, "QueryInterface(IMediaControl) failed: %08x\n", hr);

    hr = IFilterGraph2_QueryInterface(graph, &IID_IMediaFilter, (void **)&filter);
    ok(hr == S_OK, "QueryInterface(IMediaFilter) failed: %08x\n", hr);

    format = GUID_NULL;
    hr = IMediaSeeking_GetTimeFormat(seeking, &format);
    ok(hr == S_OK, "GetTimeFormat failed: %#x\n", hr);
    ok(IsEqualGUID(&format, &TIME_FORMAT_MEDIA_TIME), "got %s\n", wine_dbgstr_guid(&format));

    pos = 0xdeadbeef;
    hr = IMediaSeeking_ConvertTimeFormat(seeking, &pos, NULL, 0x123456789a, NULL);
    ok(hr == S_OK, "ConvertTimeFormat failed: %#x\n", hr);
    ok(pos == 0x123456789a, "got %s\n", wine_dbgstr_longlong(pos));

    pos = 0xdeadbeef;
    hr = IMediaSeeking_ConvertTimeFormat(seeking, &pos, &TIME_FORMAT_MEDIA_TIME, 0x123456789a, NULL);
    ok(hr == S_OK, "ConvertTimeFormat failed: %#x\n", hr);
    ok(pos == 0x123456789a, "got %s\n", wine_dbgstr_longlong(pos));

    pos = 0xdeadbeef;
    hr = IMediaSeeking_ConvertTimeFormat(seeking, &pos, NULL, 0x123456789a, &TIME_FORMAT_MEDIA_TIME);
    ok(hr == S_OK, "ConvertTimeFormat failed: %#x\n", hr);
    ok(pos == 0x123456789a, "got %s\n", wine_dbgstr_longlong(pos));

    hr = IMediaSeeking_GetCurrentPosition(seeking, &pos);
    ok(hr == S_OK, "GetCurrentPosition failed: %#x\n", hr);
    ok(pos == 0, "got %s\n", wine_dbgstr_longlong(pos));

    hr = IMediaSeeking_GetDuration(seeking, &duration);
    ok(hr == S_OK, "GetDuration failed: %#x\n", hr);
    ok(duration > 0, "got %s\n", wine_dbgstr_longlong(duration));

    hr = IMediaSeeking_GetStopPosition(seeking, &stop);
    ok(hr == S_OK, "GetCurrentPosition failed: %08x\n", hr);
    ok(stop == duration || stop == duration + 1, "expected %s, got %s\n",
        wine_dbgstr_longlong(duration), wine_dbgstr_longlong(stop));

    hr = IMediaSeeking_SetPositions(seeking, NULL, AM_SEEKING_ReturnTime, NULL, AM_SEEKING_NoPositioning);
    ok(hr == S_OK, "SetPositions failed: %#x\n", hr);
    hr = IMediaSeeking_SetPositions(seeking, NULL, AM_SEEKING_NoPositioning, NULL, AM_SEEKING_ReturnTime);
    ok(hr == S_OK, "SetPositions failed: %#x\n", hr);

    pos = 0;
    hr = IMediaSeeking_SetPositions(seeking, &pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    ok(hr == S_OK, "SetPositions failed: %08x\n", hr);

    IMediaFilter_SetSyncSource(filter, NULL);
    pos = 0xdeadbeef;
    hr = IMediaSeeking_GetCurrentPosition(seeking, &pos);
    ok(hr == S_OK, "GetCurrentPosition failed: %08x\n", hr);
    ok(pos == 0, "Position != 0 (%s)\n", wine_dbgstr_longlong(pos));
    IFilterGraph2_SetDefaultSyncSource(graph);

    IMediaSeeking_Release(seeking);
    IMediaFilter_Release(filter);
}