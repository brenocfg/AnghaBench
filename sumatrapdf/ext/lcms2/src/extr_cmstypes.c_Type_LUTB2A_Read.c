#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  scalar_t__ cmsUInt8Number ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  void cmsPipeline ;
struct TYPE_10__ {scalar_t__ (* Tell ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  _cmsTagBase ;

/* Variables and functions */
 int /*<<< orphan*/  ReadCLUT (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ReadMatrix (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ReadSetOfCurves (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _cmsReadUInt16Number (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  _cmsReadUInt8Number (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  cmsAT_END ; 
 scalar_t__ cmsMAXCHANNELS ; 
 void* cmsPipelineAlloc (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
void* Type_LUTB2A_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsUInt8Number       inputChan;      // Number of input channels
    cmsUInt8Number       outputChan;     // Number of output channels
    cmsUInt32Number      BaseOffset;     // Actual position in file
    cmsUInt32Number      offsetB;        // Offset to first "B" curve
    cmsUInt32Number      offsetMat;      // Offset to matrix
    cmsUInt32Number      offsetM;        // Offset to first "M" curve
    cmsUInt32Number      offsetC;        // Offset to CLUT
    cmsUInt32Number      offsetA;        // Offset to first "A" curve
    cmsPipeline* NewLUT = NULL;


    BaseOffset = io ->Tell(ContextID, io) - sizeof(_cmsTagBase);

    if (!_cmsReadUInt8Number(ContextID, io, &inputChan)) return NULL;
    if (!_cmsReadUInt8Number(ContextID, io, &outputChan)) return NULL;

    if (inputChan == 0 || inputChan >= cmsMAXCHANNELS) return NULL;
    if (outputChan == 0 || outputChan >= cmsMAXCHANNELS) return NULL;

    // Padding
    if (!_cmsReadUInt16Number(ContextID, io, NULL)) return NULL;

    if (!_cmsReadUInt32Number(ContextID, io, &offsetB)) return NULL;
    if (!_cmsReadUInt32Number(ContextID, io, &offsetMat)) return NULL;
    if (!_cmsReadUInt32Number(ContextID, io, &offsetM)) return NULL;
    if (!_cmsReadUInt32Number(ContextID, io, &offsetC)) return NULL;
    if (!_cmsReadUInt32Number(ContextID, io, &offsetA)) return NULL;

    // Allocates an empty LUT
    NewLUT = cmsPipelineAlloc(ContextID, inputChan, outputChan);
    if (NewLUT == NULL) return NULL;

    if (offsetB != 0) {
        if (!cmsPipelineInsertStage(ContextID, NewLUT, cmsAT_END, ReadSetOfCurves(ContextID, self, io, BaseOffset + offsetB, inputChan)))
            goto Error;
    }

    if (offsetMat != 0) {
        if (!cmsPipelineInsertStage(ContextID, NewLUT, cmsAT_END, ReadMatrix(ContextID, self, io, BaseOffset + offsetMat)))
            goto Error;
    }

    if (offsetM != 0) {
        if (!cmsPipelineInsertStage(ContextID, NewLUT, cmsAT_END, ReadSetOfCurves(ContextID, self, io, BaseOffset + offsetM, inputChan)))
            goto Error;
    }

    if (offsetC != 0) {
        if (!cmsPipelineInsertStage(ContextID, NewLUT, cmsAT_END, ReadCLUT(ContextID, self, io, BaseOffset + offsetC, inputChan, outputChan)))
            goto Error;
    }

    if (offsetA!= 0) {
        if (!cmsPipelineInsertStage(ContextID, NewLUT, cmsAT_END, ReadSetOfCurves(ContextID, self, io, BaseOffset + offsetA, outputChan)))
            goto Error;
    }

    *nItems = 1;
    return NewLUT;
Error:
    cmsPipelineFree(ContextID, NewLUT);
    return NULL;

    cmsUNUSED_PARAMETER(SizeOfTag);
}