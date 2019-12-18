#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  size_t cmsUInt32Number ;
struct TYPE_7__ {int nSegments; TYPE_1__* Segments; } ;
typedef  TYPE_2__ cmsToneCurve ;
typedef  int cmsTagTypeSignature ;
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_6__ {scalar_t__ Type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Type_Curve_Write (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Type_ParametricCurve_Write (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 TYPE_2__** _cmsStageGetPtrToCurveSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsTagSignature2String (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteAlignment (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsWriteTypeBase (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmsERROR_UNKNOWN_EXTENSION ; 
#define  cmsSigCurveType 129 
#define  cmsSigParametricCurveType 128 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 size_t cmsStageOutputChannels (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool WriteSetOfCurves(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsTagTypeSignature Type, cmsStage* mpe)
{
    cmsUInt32Number i, n;
    cmsTagTypeSignature CurrentType;
    cmsToneCurve** Curves;


    n      = cmsStageOutputChannels(ContextID, mpe);
    Curves = _cmsStageGetPtrToCurveSet(mpe);

    for (i=0; i < n; i++) {

        // If this is a table-based curve, use curve type even on V4
        CurrentType = Type;

        if ((Curves[i] ->nSegments == 0)||
            ((Curves[i]->nSegments == 2) && (Curves[i] ->Segments[1].Type == 0)) )
            CurrentType = cmsSigCurveType;
        else
        if (Curves[i] ->Segments[0].Type < 0)
            CurrentType = cmsSigCurveType;

        if (!_cmsWriteTypeBase(ContextID, io, CurrentType)) return FALSE;

        switch (CurrentType) {

            case cmsSigCurveType:
                if (!Type_Curve_Write(ContextID, self, io, Curves[i], 1)) return FALSE;
                break;

            case cmsSigParametricCurveType:
                if (!Type_ParametricCurve_Write(ContextID, self, io, Curves[i], 1)) return FALSE;
                break;

            default:
                {
                    char String[5];

                    _cmsTagSignature2String(String, (cmsTagSignature) Type);
                    cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "Unknown curve type '%s'", String);
                }
                return FALSE;
        }

        if (!_cmsWriteAlignment(ContextID, io)) return FALSE;
    }


    return TRUE;
}