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
typedef  scalar_t__ cmsUInt32Number ;
typedef  scalar_t__ cmsUInt16Number ;
typedef  void cmsStage ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadFloat32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ cmsMAXCHANNELS ; 
 void* cmsStageAllocMatrix (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 

__attribute__((used)) static
void *Type_MPEmatrix_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsStage* mpe;
    cmsUInt16Number   InputChans, OutputChans;
    cmsUInt32Number   nElems, i;
    cmsFloat64Number* Matrix;
    cmsFloat64Number* Offsets;
    cmsUNUSED_PARAMETER(self);

    if (!_cmsReadUInt16Number(ContextID, io, &InputChans)) return NULL;
    if (!_cmsReadUInt16Number(ContextID, io, &OutputChans)) return NULL;


    // Input and output chans may be ANY (up to 0xffff),
    // but we choose to limit to 16 channels for now
    if (InputChans >= cmsMAXCHANNELS) return NULL;
    if (OutputChans >= cmsMAXCHANNELS) return NULL;

    nElems = (cmsUInt32Number) InputChans * OutputChans;

    Matrix = (cmsFloat64Number*) _cmsCalloc(ContextID, nElems, sizeof(cmsFloat64Number));
    if (Matrix == NULL) return NULL;

    Offsets = (cmsFloat64Number*) _cmsCalloc(ContextID, OutputChans, sizeof(cmsFloat64Number));
    if (Offsets == NULL) {

        _cmsFree(ContextID, Matrix);
        return NULL;
    }

    for (i=0; i < nElems; i++) {

        cmsFloat32Number v;

        if (!_cmsReadFloat32Number(ContextID, io, &v)) {
            _cmsFree(ContextID, Matrix);
            _cmsFree(ContextID, Offsets);
            return NULL;
        }
        Matrix[i] = v;
    }


    for (i=0; i < OutputChans; i++) {

        cmsFloat32Number v;

        if (!_cmsReadFloat32Number(ContextID, io, &v)) {
            _cmsFree(ContextID, Matrix);
            _cmsFree(ContextID, Offsets);
            return NULL;
        }
        Offsets[i] = v;
    }


    mpe = cmsStageAllocMatrix(ContextID, OutputChans, InputChans, Matrix, Offsets);
    _cmsFree(ContextID, Matrix);
    _cmsFree(ContextID, Offsets);

    *nItems = 1;

    return mpe;

    cmsUNUSED_PARAMETER(SizeOfTag);
}