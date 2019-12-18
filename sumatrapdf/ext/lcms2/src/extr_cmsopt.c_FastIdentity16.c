#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
struct TYPE_2__ {size_t InputChannels; } ;
typedef  TYPE_1__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void FastIdentity16(cmsContext ContextID, register const cmsUInt16Number In[],
                    register cmsUInt16Number Out[],
                    register const void* D)
{
    cmsPipeline* Lut = (cmsPipeline*) D;
    cmsUInt32Number i;
    cmsUNUSED_PARAMETER(ContextID);

    for (i=0; i < Lut ->InputChannels; i++) {
         Out[i] = In[i];
    }
}