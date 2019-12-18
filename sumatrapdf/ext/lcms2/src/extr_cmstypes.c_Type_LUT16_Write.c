#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int cmsUInt16Number ;
struct TYPE_15__ {scalar_t__ Type; struct TYPE_15__* Next; scalar_t__ Data; } ;
typedef  TYPE_4__ cmsStage ;
struct TYPE_16__ {TYPE_4__* Elements; } ;
typedef  TYPE_5__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_17__ {TYPE_2__** TheCurves; } ;
typedef  TYPE_6__ _cmsStageToneCurvesData ;
struct TYPE_18__ {int* Double; } ;
typedef  TYPE_7__ _cmsStageMatrixData ;
struct TYPE_14__ {int /*<<< orphan*/  T; } ;
struct TYPE_19__ {TYPE_3__ Tab; TYPE_1__* Params; } ;
typedef  TYPE_8__ _cmsStageCLutData ;
struct TYPE_13__ {scalar_t__ nEntries; } ;
struct TYPE_12__ {scalar_t__* nSamples; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Write16bitTables (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  _cmsWrite15Fixed16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _cmsWriteUInt16Array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _cmsWriteUInt8Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsERROR_UNKNOWN_EXTENSION ; 
 scalar_t__ cmsPipelineInputChannels (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ cmsPipelineOutputChannels (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ cmsSigCLutElemType ; 
 scalar_t__ cmsSigCurveSetElemType ; 
 scalar_t__ cmsSigMatrixElemType ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 scalar_t__ uipow (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static
cmsBool  Type_LUT16_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsUInt32Number nTabSize;
    cmsPipeline* NewLUT = (cmsPipeline*) Ptr;
    cmsStage* mpe;
    _cmsStageToneCurvesData* PreMPE = NULL, *PostMPE = NULL;
    _cmsStageMatrixData* MatMPE = NULL;
    _cmsStageCLutData* clut = NULL;
    cmsUInt32Number i, InputChannels, OutputChannels, clutPoints;
    cmsUNUSED_PARAMETER(self);

    // Disassemble the LUT into components.
    mpe = NewLUT -> Elements;
    if (mpe != NULL && mpe ->Type == cmsSigMatrixElemType) {

        MatMPE = (_cmsStageMatrixData*) mpe ->Data;
        mpe = mpe -> Next;
    }


    if (mpe != NULL && mpe ->Type == cmsSigCurveSetElemType) {
        PreMPE = (_cmsStageToneCurvesData*) mpe ->Data;
        mpe = mpe -> Next;
    }

    if (mpe != NULL && mpe ->Type == cmsSigCLutElemType) {
        clut  = (_cmsStageCLutData*) mpe -> Data;
        mpe = mpe ->Next;
    }

    if (mpe != NULL && mpe ->Type == cmsSigCurveSetElemType) {
        PostMPE = (_cmsStageToneCurvesData*) mpe ->Data;
        mpe = mpe -> Next;
    }

    // That should be all
    if (mpe != NULL) {
        cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "LUT is not suitable to be saved as LUT16");
        return FALSE;
    }

    InputChannels  = cmsPipelineInputChannels(ContextID, NewLUT);
    OutputChannels = cmsPipelineOutputChannels(ContextID, NewLUT);

    if (clut == NULL)
        clutPoints = 0;
    else
        clutPoints    = clut->Params->nSamples[0];

    if (!_cmsWriteUInt8Number(ContextID, io, (cmsUInt8Number) InputChannels)) return FALSE;
    if (!_cmsWriteUInt8Number(ContextID, io, (cmsUInt8Number) OutputChannels)) return FALSE;
    if (!_cmsWriteUInt8Number(ContextID, io, (cmsUInt8Number) clutPoints)) return FALSE;
    if (!_cmsWriteUInt8Number(ContextID, io, 0)) return FALSE; // Padding


    if (MatMPE != NULL) {

        if (!_cmsWrite15Fixed16Number(ContextID, io, MatMPE -> Double[0])) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, MatMPE -> Double[1])) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, MatMPE -> Double[2])) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, MatMPE -> Double[3])) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, MatMPE -> Double[4])) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, MatMPE -> Double[5])) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, MatMPE -> Double[6])) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, MatMPE -> Double[7])) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, MatMPE -> Double[8])) return FALSE;
    }
    else {

        if (!_cmsWrite15Fixed16Number(ContextID, io, 1)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 0)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 0)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 0)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 1)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 0)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 0)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 0)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 1)) return FALSE;
    }


    if (PreMPE != NULL) {
        if (!_cmsWriteUInt16Number(ContextID, io, (cmsUInt16Number) PreMPE ->TheCurves[0]->nEntries)) return FALSE;
    } else {
            if (!_cmsWriteUInt16Number(ContextID, io, 2)) return FALSE;
    }

    if (PostMPE != NULL) {
        if (!_cmsWriteUInt16Number(ContextID, io, (cmsUInt16Number) PostMPE ->TheCurves[0]->nEntries)) return FALSE;
    } else {
        if (!_cmsWriteUInt16Number(ContextID, io, 2)) return FALSE;

    }

    // The prelinearization table

    if (PreMPE != NULL) {
        if (!Write16bitTables(ContextID, io, PreMPE)) return FALSE;
    }
    else {
        for (i=0; i < InputChannels; i++) {

            if (!_cmsWriteUInt16Number(ContextID, io, 0)) return FALSE;
            if (!_cmsWriteUInt16Number(ContextID, io, 0xffff)) return FALSE;
        }
    }

    nTabSize = uipow(OutputChannels, clutPoints, InputChannels);
    if (nTabSize == (cmsUInt32Number) -1) return FALSE;
    if (nTabSize > 0) {
        // The 3D CLUT.
        if (clut != NULL) {
            if (!_cmsWriteUInt16Array(ContextID, io, nTabSize, clut->Tab.T)) return FALSE;
        }
    }

    // The postlinearization table
    if (PostMPE != NULL) {
        if (!Write16bitTables(ContextID, io, PostMPE)) return FALSE;
    }
    else {
        for (i=0; i < OutputChannels; i++) {

            if (!_cmsWriteUInt16Number(ContextID, io, 0)) return FALSE;
            if (!_cmsWriteUInt16Number(ContextID, io, 0xffff)) return FALSE;
        }
    }

    return TRUE;

    cmsUNUSED_PARAMETER(nItems);
}