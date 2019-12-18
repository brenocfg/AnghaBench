#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int cmsUInt32Number ;
typedef  scalar_t__ cmsUInt16Number ;
struct TYPE_9__ {scalar_t__* Table16; } ;
typedef  TYPE_1__ cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsPipeline ;
struct TYPE_10__ {int (* Read ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int,int) ;} ;
typedef  TYPE_2__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  Tables ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FROM_8_TO_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _cmsMalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsAT_END ; 
 TYPE_1__* cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsStageAllocToneCurves (int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static
cmsBool  Read8bitTables(cmsContext ContextID, cmsIOHANDLER* io, cmsPipeline* lut, cmsUInt32Number nChannels)
{
    cmsUInt8Number* Temp = NULL;
    cmsUInt32Number i, j;
    cmsToneCurve* Tables[cmsMAXCHANNELS];

    if (nChannels > cmsMAXCHANNELS) return FALSE;
    if (nChannels <= 0) return FALSE;

    memset(Tables, 0, sizeof(Tables));

    Temp = (cmsUInt8Number*) _cmsMalloc(ContextID, 256);
    if (Temp == NULL) return FALSE;

    for (i=0; i < nChannels; i++) {
        Tables[i] = cmsBuildTabulatedToneCurve16(ContextID, 256, NULL);
        if (Tables[i] == NULL) goto Error;
    }

    for (i=0; i < nChannels; i++) {

        if (io ->Read(ContextID, io, Temp, 256, 1) != 1) goto Error;

        for (j=0; j < 256; j++)
            Tables[i]->Table16[j] = (cmsUInt16Number) FROM_8_TO_16(Temp[j]);
    }

    _cmsFree(ContextID, Temp);
    Temp = NULL;

    if (!cmsPipelineInsertStage(ContextID, lut, cmsAT_END, cmsStageAllocToneCurves(ContextID, nChannels, Tables)))
        goto Error;

    for (i=0; i < nChannels; i++)
        cmsFreeToneCurve(ContextID, Tables[i]);

    return TRUE;

Error:
    for (i=0; i < nChannels; i++) {
        if (Tables[i]) cmsFreeToneCurve(ContextID, Tables[i]);
    }

    if (Temp) _cmsFree(ContextID, Temp);
    return FALSE;
}