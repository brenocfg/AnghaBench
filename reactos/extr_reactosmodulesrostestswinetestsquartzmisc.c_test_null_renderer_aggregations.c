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
 int /*<<< orphan*/  CLSID_NullRenderer ; 
 int /*<<< orphan*/  CLSID_SystemClock ; 
 int /*<<< orphan*/  const IID_IBaseFilter ; 
 int /*<<< orphan*/  const IID_IMediaFilter ; 
 int /*<<< orphan*/  IID_IReferenceClock ; 
 int /*<<< orphan*/  test_aggregation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void test_null_renderer_aggregations(void)
{
    const IID * iids[] = {
        &IID_IMediaFilter, &IID_IBaseFilter
    };
    int i;

    for (i = 0; i < sizeof(iids) / sizeof(iids[0]); i++)
    {
        test_aggregation(CLSID_SystemClock, CLSID_NullRenderer, IID_IReferenceClock, *iids[i]);
    }
}