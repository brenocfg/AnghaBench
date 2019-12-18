#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt8Number ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int cmsUInt16Number ;
typedef  void cmsPipeline ;
typedef  int /*<<< orphan*/  cmsMAT3 ;
struct TYPE_7__ {int (* Read ) (int /*<<< orphan*/ ,TYPE_1__*,int*,scalar_t__,int) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_8_TO_16 (int) ; 
 int /*<<< orphan*/  Read8bitTables (int /*<<< orphan*/ ,TYPE_1__*,void*,int) ; 
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  _cmsMAT3isIdentity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _cmsMalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _cmsRead15Fixed16Number (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadUInt8Number (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int cmsMAXCHANNELS ; 
 void* cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsStageAllocCLut16bit (int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  cmsStageAllocMatrix (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*,int*,scalar_t__,int) ; 
 scalar_t__ uipow (int,int,int) ; 

__attribute__((used)) static
void *Type_LUT8_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsUInt8Number InputChannels, OutputChannels, CLUTpoints;
    cmsUInt8Number* Temp = NULL;
    cmsPipeline* NewLUT = NULL;
    cmsUInt32Number nTabSize, i;
    cmsFloat64Number Matrix[3*3];
    cmsUNUSED_PARAMETER(self);

    *nItems = 0;

    if (!_cmsReadUInt8Number(ContextID, io, &InputChannels)) goto Error;
    if (!_cmsReadUInt8Number(ContextID, io, &OutputChannels)) goto Error;
    if (!_cmsReadUInt8Number(ContextID, io, &CLUTpoints)) goto Error;

     if (CLUTpoints == 1) goto Error; // Impossible value, 0 for no CLUT and then 2 at least

    // Padding
    if (!_cmsReadUInt8Number(ContextID, io, NULL)) goto Error;

    // Do some checking
    if (InputChannels == 0 || InputChannels > cmsMAXCHANNELS)  goto Error;
    if (OutputChannels == 0 || OutputChannels > cmsMAXCHANNELS) goto Error;

   // Allocates an empty Pipeline
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


    // Only operates if not identity...
    if ((InputChannels == 3) && !_cmsMAT3isIdentity(ContextID, (cmsMAT3*) Matrix)) {

        if (!cmsPipelineInsertStage(ContextID, NewLUT, cmsAT_BEGIN, cmsStageAllocMatrix(ContextID, 3, 3, Matrix, NULL)))
            goto Error;
    }

    // Get input tables
    if (!Read8bitTables(ContextID, io,  NewLUT, InputChannels)) goto Error;

    // Get 3D CLUT. Check the overflow....
    nTabSize = uipow(OutputChannels, CLUTpoints, InputChannels);
    if (nTabSize == (cmsUInt32Number) -1) goto Error;
    if (nTabSize > 0) {

        cmsUInt16Number *PtrW, *T;

        PtrW = T  = (cmsUInt16Number*) _cmsCalloc(ContextID, nTabSize, sizeof(cmsUInt16Number));
        if (T  == NULL) goto Error;

        Temp = (cmsUInt8Number*) _cmsMalloc(ContextID, nTabSize);
        if (Temp == NULL) {
            _cmsFree(ContextID, T);
            goto Error;
        }

        if (io ->Read(ContextID, io, Temp, nTabSize, 1) != 1) {
            _cmsFree(ContextID, T);
            _cmsFree(ContextID, Temp);
            goto Error;
        }

        for (i = 0; i < nTabSize; i++) {

            *PtrW++ = FROM_8_TO_16(Temp[i]);
        }
        _cmsFree(ContextID, Temp);
        Temp = NULL;

        if (!cmsPipelineInsertStage(ContextID, NewLUT, cmsAT_END, cmsStageAllocCLut16bit(ContextID, CLUTpoints, InputChannels, OutputChannels, T))) {
            _cmsFree(ContextID, T);
            goto Error;
        }
        _cmsFree(ContextID, T);
    }


    // Get output tables
    if (!Read8bitTables(ContextID, io,  NewLUT, OutputChannels)) goto Error;

    *nItems = 1;
    return NewLUT;

Error:
    if (NewLUT != NULL) cmsPipelineFree(ContextID, NewLUT);
    return NULL;

    cmsUNUSED_PARAMETER(SizeOfTag);
}