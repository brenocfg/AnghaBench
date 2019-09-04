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
typedef  int TIMELINE_MAJOR_TYPE ;
typedef  int /*<<< orphan*/  IAMTimelineObj ;
typedef  int /*<<< orphan*/  IAMTimeline ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_AMTimeline ; 
 int /*<<< orphan*/ * CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/ * E_NOINTERFACE ; 
 int /*<<< orphan*/ * E_POINTER ; 
 int /*<<< orphan*/ * IAMTimelineObj_GetTimelineNoRef (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IAMTimelineObj_GetTimelineType (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * IAMTimelineObj_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAMTimelineObj_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IAMTimelineObj_SetTimelineType (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * IAMTimeline_CreateEmptyNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * IAMTimeline_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAMTimeline_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAMTimeline ; 
 int /*<<< orphan*/  IID_IAMTimelineObj ; 
 int /*<<< orphan*/ * REGDB_E_CLASSNOTREG ; 
 int /*<<< orphan*/ * S_OK ; 
#define  TIMELINE_MAJOR_TYPE_COMPOSITE 133 
#define  TIMELINE_MAJOR_TYPE_EFFECT 132 
#define  TIMELINE_MAJOR_TYPE_GROUP 131 
#define  TIMELINE_MAJOR_TYPE_SOURCE 130 
#define  TIMELINE_MAJOR_TYPE_TRACK 129 
#define  TIMELINE_MAJOR_TYPE_TRANSITION 128 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_timeline(void)
{
    HRESULT hr;
    IAMTimeline *timeline = NULL;
    IAMTimeline *timeline2 = (IAMTimeline *)0xdeadbeef;
    IAMTimelineObj *obj = (IAMTimelineObj *)0xdeadbeef;
    IAMTimelineObj obj_iface;
    TIMELINE_MAJOR_TYPE type;

    hr = CoCreateInstance(&CLSID_AMTimeline, NULL, CLSCTX_INPROC_SERVER, &IID_IAMTimeline, (void **)&timeline);
    ok(hr == S_OK || broken(hr == REGDB_E_CLASSNOTREG), "CoCreateInstance failed: %08x\n", hr);
    if (!timeline) return;

    hr = IAMTimeline_QueryInterface(timeline, &IID_IAMTimelineObj, NULL);
    ok(hr == E_POINTER, "Expected E_POINTER got %08x\n", hr);

    hr = IAMTimeline_QueryInterface(timeline, &IID_IAMTimelineObj, (void **)&obj);
    ok(hr == E_NOINTERFACE, "Expected E_NOINTERFACE got %08x\n", hr);
    ok(!obj, "Expected NULL got %p\n", obj);

    hr = IAMTimeline_CreateEmptyNode(timeline, NULL, 0);
    ok(hr == E_POINTER, "Expected E_POINTER got %08x\n", hr);

    hr = IAMTimeline_CreateEmptyNode(timeline, NULL, TIMELINE_MAJOR_TYPE_COMPOSITE);
    ok(hr == E_POINTER, "Expected E_POINTER got %08x\n", hr);

    for (type = 0; type < 256; type++)
    {
        obj = &obj_iface;
        hr = IAMTimeline_CreateEmptyNode(timeline, &obj, type);
        switch (type)
        {
            case TIMELINE_MAJOR_TYPE_COMPOSITE:
            case TIMELINE_MAJOR_TYPE_TRACK:
            case TIMELINE_MAJOR_TYPE_SOURCE:
            case TIMELINE_MAJOR_TYPE_TRANSITION:
            case TIMELINE_MAJOR_TYPE_EFFECT:
            case TIMELINE_MAJOR_TYPE_GROUP:
                ok(hr == S_OK, "CreateEmptyNode failed: %08x\n", hr);
                if (obj != &obj_iface) IAMTimelineObj_Release(obj);
                break;
            default:
                ok(hr == E_INVALIDARG, "Expected E_INVALIDARG got %08x\n", hr);
                ok(obj == &obj_iface, "Expected %p got %p\n", &obj_iface, obj);
        }
    }

    obj = NULL;
    hr = IAMTimeline_CreateEmptyNode(timeline, &obj, TIMELINE_MAJOR_TYPE_COMPOSITE);
    ok(hr == S_OK, "CreateEmptyNode failed: %08x\n", hr);
    if (!obj) return;

    hr = IAMTimelineObj_QueryInterface(obj, &IID_IAMTimeline, NULL);
    ok(hr == E_POINTER, "Expected E_POINTER got %08x\n", hr);

    hr = IAMTimelineObj_QueryInterface(obj, &IID_IAMTimeline, (void **)&timeline2);
    ok(hr == E_NOINTERFACE, "Expected E_NOINTERFACE got %08x\n", hr);
    ok(!timeline2, "Expected NULL got %p\n", timeline2);

    hr = IAMTimelineObj_GetTimelineType(obj, NULL);
    ok(hr == E_POINTER, "Expected E_POINTER got %08x\n", hr);

    hr = IAMTimelineObj_GetTimelineType(obj, &type);
    ok(hr == S_OK, "GetTimelineType failed: %08x\n", hr);
    ok(type == TIMELINE_MAJOR_TYPE_COMPOSITE, "Expected TIMELINE_MAJOR_TYPE_COMPOSITE got %d\n", type);

    for (type = 0; type < 256; type++)
    {
        hr = IAMTimelineObj_SetTimelineType(obj, type);
        if (type == TIMELINE_MAJOR_TYPE_COMPOSITE)
            ok(hr == S_OK, "SetTimelineType failed: %08x\n", hr);
        else
            ok(hr == E_INVALIDARG, "Expected E_INVALIDARG got %08x\n", hr);
    }

    hr = IAMTimelineObj_GetTimelineNoRef(obj, NULL);
    ok(hr == E_POINTER, "Expected E_POINTER got %08x\n", hr);

    timeline2 = (IAMTimeline *)0xdeadbeef;
    hr = IAMTimelineObj_GetTimelineNoRef(obj, &timeline2);
    ok(hr == E_NOINTERFACE, "Expected E_NOINTERFACE got %08x\n", hr);
    ok(!timeline2, "Expected NULL got %p\n", timeline2);

    IAMTimelineObj_Release(obj);
    IAMTimeline_Release(timeline);
}