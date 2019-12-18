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
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt8Number ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int cmsUInt16Number ;
typedef  void cmsPipeline ;
typedef  int /*<<< orphan*/  cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  Read16bitTables (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,int) ; 
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  _cmsMAT3isIdentity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsRead15Fixed16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadUInt16Array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int*) ; 
 int /*<<< orphan*/  _cmsReadUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _cmsReadUInt8Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int cmsMAXCHANNELS ; 
 void* cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsStageAllocCLut16bit (int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  cmsStageAllocMatrix (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 scalar_t__ uipow (int,int,int) ; 

__attribute__((used)) static
void *Type_LUT16_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsUInt8Number InputChannels, OutputChannels, CLUTpoints;
    cmsPipeline* NewLUT = NULL;
    cmsUInt32Number nTabSize;
    cmsFloat64Number Matrix[3*3];
    cmsUInt16Number InputEntries, OutputEntries;
    cmsUNUSED_PARAMETER(self);

    *nItems = 0;

    if (!_cmsReadUInt8Number(ContextID, io, &InputChannels)) return NULL;
    if (!_cmsReadUInt8Number(ContextID, io, &OutputChannels)) return NULL;
    if (!_cmsReadUInt8Number(ContextID, io, &CLUTpoints)) return NULL;   // 255 maximum

    // Padding
    if (!_cmsReadUInt8Number(ContextID, io, NULL)) return NULL;

    // Do some checking
    if (InputChannels == 0 || InputChannels > cmsMAXCHANNELS)  goto Error;
    if (OutputChannels == 0 || OutputChannels > cmsMAXCHANNELS) goto Error;

    // Allocates an empty LUT
    NewLUT = cmsPipelineAlloc(ContextID, InputChannels, OutputChannels);
    if (NewLUT == NULL) goto Error;

    // Read the Matrix
    if (!_cmsRead15Fixed16Number(ContextID, io,  &Matrix[0])) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io,  &Matrix[1])) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io,  &Matrix[2])) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io,  &Matrix[3])) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io,  &Matrix[4])) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io,  &Matrix[5])) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io,  &Matrix[6])) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io,  &Matrix[7])) goto Error;
    if (!_cmsRead15Fixed16Number(ContextID, io,  &Matrix[8])) goto Error;


    // Only operates on 3 channels
    if ((InputChannels == 3) && !_cmsMAT3isIdentity(ContextID, (cmsMAT3*) Matrix)) {

        if (!cmsPipelineInsertStage(ContextID, NewLUT, cmsAT_END, cmsStageAllocMatrix(ContextID, 3, 3, Matrix, NULL)))
            goto Error;
    }

    if (!_cmsReadUInt16Number(ContextID, io, &InputEntries)) goto Error;
    if (!_cmsReadUInt16Number(ContextID, io, &OutputEntries)) goto Error;

    if (InputEntries > 0x7FFF || OutputEntries > 0x7FFF) goto Error;
    if (CLUTpoints == 1) goto Error; // Impossible value, 0 for no CLUT and then 2 at least

    // Get input tables
    if (!Read16bitTables(ContextID, io,  NewLUT, InputChannels, InputEntries)) goto Error;

    // Get 3D CLUT
    nTabSize = uipow(OutputChannels, CLUTpoints, InputChannels);
    if (nTabSize == (cmsUInt32Number) -1) goto Error;
    if (nTabSize > 0) {

        cmsUInt16Number *T;

        T  = (cmsUInt16Number*) _cmsCalloc(ContextID, nTabSize, sizeof(cmsUInt16Number));
        if (T  == NULL) goto Error;

        if (!_cmsReadUInt16Array(ContextID, io, nTabSize, T)) {
            _cmsFree(ContextID, T);
            goto Error;
        }

        if (!cmsPipelineInsertStage(ContextID, NewLUT, cmsAT_END, cmsStageAllocCLut16bit(ContextID, CLUTpoints, InputChannels, OutputChannels, T))) {
            _cmsFree(ContextID, T);
            goto Error;
        }
        _cmsFree(ContextID, T);
    }


    // Get output tables
    if (!Read16bitTables(ContextID, io,  NewLUT, OutputChannels, OutputEntries)) goto Error;

    *nItems = 1;
    return NewLUT;

Error:
    if (NewLUT != NULL) cmsPipelineFree(ContextID, NewLUT);
    return NULL;

    cmsUNUSED_PARAMETER(SizeOfTag);
}