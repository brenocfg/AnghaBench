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
typedef  int /*<<< orphan*/  IAMTimelineObj ;
typedef  int /*<<< orphan*/  IAMTimelineGroup ;
typedef  int /*<<< orphan*/  IAMTimeline ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_AMTimeline ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IAMTimelineGroup_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAMTimelineGroup_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IAMTimelineObj_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAMTimelineObj_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IAMTimeline_CreateEmptyNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAMTimeline_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAMTimeline ; 
 int /*<<< orphan*/  IID_IAMTimelineGroup ; 
 int /*<<< orphan*/  IID_IAMTimelineObj ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TIMELINE_MAJOR_TYPE_GROUP ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_timelineobj_interfaces(void)
{
    HRESULT hr;
    IAMTimeline *timeline = NULL;
    IAMTimelineObj *obj;

    hr = CoCreateInstance(&CLSID_AMTimeline, NULL, CLSCTX_INPROC_SERVER, &IID_IAMTimeline, (void **)&timeline);
    ok(hr == S_OK || broken(hr == REGDB_E_CLASSNOTREG), "CoCreateInstance failed: %08x\n", hr);
    if (!timeline)
        return;

    hr = IAMTimeline_CreateEmptyNode(timeline, &obj, TIMELINE_MAJOR_TYPE_GROUP);
    ok(hr == S_OK, "CreateEmptyNode failed: %08x\n", hr);
    if(hr == S_OK)
    {
        IAMTimelineGroup *group;
        IAMTimelineObj *obj2;

        hr = IAMTimelineObj_QueryInterface(obj, &IID_IAMTimelineGroup, (void **)&group);
        ok(hr == S_OK, "got %08x\n", hr);

        hr = IAMTimelineGroup_QueryInterface(group, &IID_IAMTimelineObj, (void **)&obj2);
        ok(hr == S_OK, "got %08x\n", hr);
        ok(obj == obj2, "Different pointers\n");
        IAMTimelineObj_Release(obj2);

        IAMTimelineGroup_Release(group);

        IAMTimelineObj_Release(obj);
    }

    IAMTimeline_Release(timeline);
}