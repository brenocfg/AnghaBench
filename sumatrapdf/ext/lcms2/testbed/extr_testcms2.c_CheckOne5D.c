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
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IsGoodWordPrec (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Sampler5D (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsPipelineEval16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool CheckOne5D(cmsPipeline* lut, cmsUInt16Number a1, cmsUInt16Number a2,
                                     cmsUInt16Number a3, cmsUInt16Number a4, cmsUInt16Number a5)
{
    cmsUInt16Number In[5], Out1[3], Out2[3];

    In[0] = a1; In[1] = a2; In[2] = a3; In[3] = a4; In[4] = a5;

    // This is the interpolated value
    cmsPipelineEval16(DbgThread(), In, Out1, lut);

    // This is the real value
    Sampler5D(DbgThread(), In, Out2, NULL);

    // Let's see the difference

    if (!IsGoodWordPrec("Channel 1", Out1[0], Out2[0], 2)) return FALSE;
    if (!IsGoodWordPrec("Channel 2", Out1[1], Out2[1], 2)) return FALSE;
    if (!IsGoodWordPrec("Channel 3", Out1[2], Out2[2], 2)) return FALSE;

    return TRUE;
}