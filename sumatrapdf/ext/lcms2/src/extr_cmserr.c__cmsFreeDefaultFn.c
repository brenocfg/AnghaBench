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
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static
void _cmsFreeDefaultFn(cmsContext ContextID, void *Ptr)
{
    // free(NULL) is defined a no-op by C99, therefore it is safe to
    // avoid the check, but it is here just in case...

    if (Ptr) free(Ptr);

    cmsUNUSED_PARAMETER(ContextID);
}