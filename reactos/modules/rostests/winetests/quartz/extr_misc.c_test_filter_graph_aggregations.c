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
typedef  int /*<<< orphan*/  iids ;
typedef  int /*<<< orphan*/  IID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_FilterGraph ; 
 int /*<<< orphan*/  CLSID_SystemClock ; 
 int /*<<< orphan*/  const IID_IBasicAudio ; 
 int /*<<< orphan*/  const IID_IBasicVideo ; 
 int /*<<< orphan*/  const IID_IFilterGraph ; 
 int /*<<< orphan*/  const IID_IFilterGraph2 ; 
 int /*<<< orphan*/  const IID_IGraphBuilder ; 
 int /*<<< orphan*/  const IID_IGraphConfig ; 
 int /*<<< orphan*/  const IID_IMediaControl ; 
 int /*<<< orphan*/  const IID_IMediaEventEx ; 
 int /*<<< orphan*/  const IID_IMediaEventSink ; 
 int /*<<< orphan*/  const IID_IMediaFilter ; 
 int /*<<< orphan*/  const IID_IMediaPosition ; 
 int /*<<< orphan*/  const IID_IMediaSeeking ; 
 int /*<<< orphan*/  IID_IReferenceClock ; 
 int /*<<< orphan*/  const IID_IVideoWindow ; 
 int /*<<< orphan*/  test_aggregation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void test_filter_graph_aggregations(void)
{
    const IID * iids[] = {
        &IID_IFilterGraph2, &IID_IMediaControl, &IID_IGraphBuilder,
        &IID_IFilterGraph, &IID_IMediaSeeking, &IID_IBasicAudio, &IID_IBasicVideo,
        &IID_IVideoWindow, &IID_IMediaEventEx, &IID_IMediaFilter,
        &IID_IMediaEventSink, &IID_IGraphConfig, &IID_IMediaPosition
    };
    int i;

    for (i = 0; i < sizeof(iids) / sizeof(iids[0]); i++)
    {
        test_aggregation(CLSID_SystemClock, CLSID_FilterGraph,
                         IID_IReferenceClock, *iids[i]);
    }
}