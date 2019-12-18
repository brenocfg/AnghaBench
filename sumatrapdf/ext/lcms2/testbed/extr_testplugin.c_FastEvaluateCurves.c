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
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */

__attribute__((used)) static
void FastEvaluateCurves(cmsContext ContextID, register const cmsUInt16Number In[],
                                     register cmsUInt16Number Out[],
                                     register const void* Data)
{
    Out[0] = In[0];
}