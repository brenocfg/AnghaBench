#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
struct TYPE_6__ {int /*<<< orphan*/  Table16; } ;
typedef  TYPE_1__ cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  Tables ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsReadUInt16Array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsAT_END ; 
 TYPE_1__* cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsStageAllocToneCurves (int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
cmsBool  Read16bitTables(cmsContext ContextID, cmsIOHANDLER* io, cmsPipeline* lut,
                                    cmsUInt32Number nChannels, cmsUInt32Number nEntries)
{
    cmsUInt32Number i;
    cmsToneCurve* Tables[cmsMAXCHANNELS];

    // Maybe an empty table? (this is a lcms extension)
    if (nEntries <= 0) return TRUE;

    // Check for malicious profiles
    if (nEntries < 2) return FALSE;
    if (nChannels > cmsMAXCHANNELS) return FALSE;

    // Init table to zero
    memset(Tables, 0, sizeof(Tables));

    for (i=0; i < nChannels; i++) {

        Tables[i] = cmsBuildTabulatedToneCurve16(ContextID, nEntries, NULL);
        if (Tables[i] == NULL) goto Error;

        if (!_cmsReadUInt16Array(ContextID, io, nEntries, Tables[i]->Table16)) goto Error;
    }


    // Add the table (which may certainly be an identity, but this is up to the optimizer, not the reading code)
    if (!cmsPipelineInsertStage(ContextID, lut, cmsAT_END, cmsStageAllocToneCurves(ContextID, nChannels, Tables)))
        goto Error;

    for (i=0; i < nChannels; i++)
        cmsFreeToneCurve(ContextID, Tables[i]);

    return TRUE;

Error:
    for (i=0; i < nChannels; i++) {
        if (Tables[i]) cmsFreeToneCurve(ContextID, Tables[i]);
    }

    return FALSE;
}