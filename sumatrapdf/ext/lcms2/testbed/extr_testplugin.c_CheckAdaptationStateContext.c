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
typedef  int /*<<< orphan*/  cmsInt32Number ;
typedef  scalar_t__ cmsFloat64Number ;
typedef  int /*<<< orphan*/ * cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/ * DupContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Fail (char*) ; 
 int /*<<< orphan*/  IsGoodVal (char*,scalar_t__,double,double) ; 
 int /*<<< orphan*/ * WatchDogContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDeleteContext (int /*<<< orphan*/ *) ; 
 scalar_t__ cmsSetAdaptationState (int /*<<< orphan*/ *,int) ; 

cmsInt32Number CheckAdaptationStateContext(void)
{
    cmsInt32Number rc = 0;
    cmsContext c1, c2, c3;
    cmsFloat64Number old1, old2;

    old1 =  cmsSetAdaptationState(NULL, -1);

    c1 = WatchDogContext(NULL);

    cmsSetAdaptationState(c1, 0.7);

    c2 = DupContext(c1, NULL);
    c3 = DupContext(c2, NULL);

    rc = IsGoodVal("Adaptation state", cmsSetAdaptationState(c3, -1), 0.7, 0.001);

    cmsDeleteContext(c1);
    cmsDeleteContext(c2);
    cmsDeleteContext(c3);

    old2 =  cmsSetAdaptationState(NULL, -1);

    if (old1 != old2) {
        Fail("Adaptation state has changed");
        return 0;
    }

    return rc;
}