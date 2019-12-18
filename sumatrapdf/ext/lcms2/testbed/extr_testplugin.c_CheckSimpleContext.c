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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  DebugMemDontCheckThis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DupContext (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Fail (char*) ; 
 int /*<<< orphan*/  WatchDogContext (int*) ; 
 int /*<<< orphan*/  cmsCreateContext (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  cmsDeleteContext (int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetContextUserData (int /*<<< orphan*/ ) ; 

cmsInt32Number CheckSimpleContext(void)
{
    int a = 1;
    int b = 32;
    cmsInt32Number rc = 0;

    cmsContext c1, c2, c3;

    // This function creates a context with a special
    // memory manager that check allocation
    c1 = WatchDogContext(&a);
    cmsDeleteContext(c1);

    c1 = WatchDogContext(&a);

    // Let's check duplication
    c2 = DupContext(c1, NULL);
    c3 = DupContext(c2, NULL);

    // User data should have been propagated
    rc = (*(int*) cmsGetContextUserData(c3)) == 1 ;

    // Free resources
    cmsDeleteContext(c1);
    cmsDeleteContext(c2);
    cmsDeleteContext(c3);

    if (!rc) {
        Fail("Creation of user data failed");
        return 0;
    }

    // Back to create 3 levels of inherance
    c1 = cmsCreateContext(NULL, &a);
    DebugMemDontCheckThis(c1);

    c2 = DupContext(c1, NULL);
    c3 = DupContext(c2, &b);

    rc = (*(int*) cmsGetContextUserData(c3)) == 32 ;

    cmsDeleteContext(c1);
    cmsDeleteContext(c2);
    cmsDeleteContext(c3);

    if (!rc) {
        Fail("Modification of user data failed");
        return 0;
    }

    // All seems ok
    return rc;
}