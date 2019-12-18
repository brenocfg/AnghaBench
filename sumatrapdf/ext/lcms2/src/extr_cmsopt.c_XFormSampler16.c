#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t cmsUInt32Number ;
typedef  double cmsUInt16Number ;
struct TYPE_3__ {int InputChannels; int OutputChannels; } ;
typedef  TYPE_1__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsInt32Number ;
typedef  double cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsAssert (int) ; 
 double _cmsQuickSaturateWord (double) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsPipelineEvalFloat (int /*<<< orphan*/ ,double*,double*,TYPE_1__*) ; 

__attribute__((used)) static
cmsInt32Number XFormSampler16(cmsContext ContextID, register const cmsUInt16Number In[], register cmsUInt16Number Out[], register void* Cargo)
{
    cmsPipeline* Lut = (cmsPipeline*) Cargo;
    cmsFloat32Number InFloat[cmsMAXCHANNELS], OutFloat[cmsMAXCHANNELS];
    cmsUInt32Number i;

    _cmsAssert(Lut -> InputChannels < cmsMAXCHANNELS);
    _cmsAssert(Lut -> OutputChannels < cmsMAXCHANNELS);

    // From 16 bit to floating point
    for (i=0; i < Lut ->InputChannels; i++)
        InFloat[i] = (cmsFloat32Number) (In[i] / 65535.0);

    // Evaluate in floating point
    cmsPipelineEvalFloat(ContextID, InFloat, OutFloat, Lut);

    // Back to 16 bits representation
    for (i=0; i < Lut ->OutputChannels; i++)
        Out[i] = _cmsQuickSaturateWord(OutFloat[i] * 65535.0);

    // Always succeed
    return TRUE;
}