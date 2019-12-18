#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  scalar_t__ cmsUInt8Number ;
typedef  scalar_t__ cmsUInt32Number ;
struct TYPE_9__ {scalar_t__ Type; struct TYPE_9__* Next; scalar_t__ Data; } ;
typedef  TYPE_3__ cmsStage ;
struct TYPE_10__ {scalar_t__ OutputChannels; scalar_t__ InputChannels; TYPE_3__* Elements; } ;
typedef  TYPE_4__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  _cmsStageToneCurvesData ;
struct TYPE_11__ {int* Double; } ;
typedef  TYPE_5__ _cmsStageMatrixData ;
struct TYPE_8__ {int /*<<< orphan*/ * T; } ;
struct TYPE_12__ {TYPE_2__ Tab; TYPE_1__* Params; } ;
typedef  TYPE_6__ _cmsStageCLutData ;
struct TYPE_7__ {scalar_t__* nSamples; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FROM_16_TO_8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Write8bitTables (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsWrite15Fixed16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _cmsWriteUInt8Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cmsERROR_UNKNOWN_EXTENSION ; 
 scalar_t__ cmsSigCLutElemType ; 
 scalar_t__ cmsSigCurveSetElemType ; 
 scalar_t__ cmsSigMatrixElemType ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 scalar_t__ uipow (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static
cmsBool  Type_LUT8_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsUInt32Number j, nTabSize;
    cmsUInt8Number  val;
    cmsPipeline* NewLUT = (cmsPipeline*) Ptr;
    cmsStage* mpe;
    _cmsStageToneCurvesData* PreMPE = NULL, *PostMPE = NULL;
    _cmsStageMatrixData* MatMPE = NULL;
    _cmsStageCLutData* clut = NULL;
    cmsUInt32Number clutPoints;
    cmsUNUSED_PARAMETER(self);

    // Disassemble the LUT into components.
    mpe = NewLUT -> Elements;
    if (mpe ->Type == cmsSigMatrixElemType) {

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
        cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "LUT is not suitable to be saved as LUT8");
        return FALSE;
    }


    if (clut == NULL)
        clutPoints = 0;
    else
        clutPoints    = clut->Params->nSamples[0];

    if (!_cmsWriteUInt8Number(ContextID, io, (cmsUInt8Number) NewLUT ->InputChannels)) return FALSE;
    if (!_cmsWriteUInt8Number(ContextID, io, (cmsUInt8Number) NewLUT ->OutputChannels)) return FALSE;
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

    // The prelinearization table
    if (!Write8bitTables(ContextID, io, NewLUT ->InputChannels, PreMPE)) return FALSE;

    nTabSize = uipow(NewLUT->OutputChannels, clutPoints, NewLUT ->InputChannels);
    if (nTabSize == (cmsUInt32Number) -1) return FALSE;
    if (nTabSize > 0) {

        // The 3D CLUT.
        if (clut != NULL) {

            for (j=0; j < nTabSize; j++) {

                val = (cmsUInt8Number) FROM_16_TO_8(clut ->Tab.T[j]);
                if (!_cmsWriteUInt8Number(ContextID, io, val)) return FALSE;
            }
        }
    }

    // The postlinearization table
    if (!Write8bitTables(ContextID, io, NewLUT ->OutputChannels, PostMPE)) return FALSE;

    return TRUE;

    cmsUNUSED_PARAMETER(nItems);
}