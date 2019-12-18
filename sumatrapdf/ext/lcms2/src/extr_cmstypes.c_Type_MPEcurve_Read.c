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
struct _cms_typehandler_struct {int dummy; } ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  scalar_t__ cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  void cmsStage ;
struct TYPE_6__ {scalar_t__ (* Tell ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  _cmsTagBase ;

/* Variables and functions */
 int /*<<< orphan*/  ReadMPECurve ; 
 scalar_t__ ReadPositionTable (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _cmsReadUInt16Number (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cmsStageAllocToneCurves (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
void *Type_MPEcurve_Read(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number* nItems, cmsUInt32Number SizeOfTag)
{
    cmsStage* mpe = NULL;
    cmsUInt16Number InputChans, OutputChans;
    cmsUInt32Number i, BaseOffset;
    cmsToneCurve** GammaTables;

    *nItems = 0;

    // Get actual position as a basis for element offsets
    BaseOffset = io ->Tell(ContextID, io) - sizeof(_cmsTagBase);

    if (!_cmsReadUInt16Number(ContextID, io, &InputChans)) return NULL;
    if (!_cmsReadUInt16Number(ContextID, io, &OutputChans)) return NULL;

    if (InputChans != OutputChans) return NULL;

    GammaTables = (cmsToneCurve**) _cmsCalloc(ContextID, InputChans, sizeof(cmsToneCurve*));
    if (GammaTables == NULL) return NULL;

    if (ReadPositionTable(ContextID, self, io, InputChans, BaseOffset, GammaTables, ReadMPECurve)) {

        mpe = cmsStageAllocToneCurves(ContextID, InputChans, GammaTables);
    }
    else {
        mpe = NULL;
    }

    for (i=0; i < InputChans; i++) {
        if (GammaTables[i]) cmsFreeToneCurve(ContextID, GammaTables[i]);
    }

    _cmsFree(ContextID, GammaTables);
    *nItems = (mpe != NULL) ? 1U : 0;
    return mpe;

    cmsUNUSED_PARAMETER(SizeOfTag);
}