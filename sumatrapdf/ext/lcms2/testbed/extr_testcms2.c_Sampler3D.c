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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  Fn8D1 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Fn8D2 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Fn8D3 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (void*) ; 

__attribute__((used)) static
cmsInt32Number Sampler3D(cmsContext ContextID, register const cmsUInt16Number In[],
               register cmsUInt16Number Out[],
               register void * Cargo)
{

    Out[0] = Fn8D1(In[0], In[1], In[2], 0, 0, 0, 0, 0, 3);
    Out[1] = Fn8D2(In[0], In[1], In[2], 0, 0, 0, 0, 0, 3);
    Out[2] = Fn8D3(In[0], In[1], In[2], 0, 0, 0, 0, 0, 3);

    return 1;

    cmsUNUSED_PARAMETER(Cargo);

}