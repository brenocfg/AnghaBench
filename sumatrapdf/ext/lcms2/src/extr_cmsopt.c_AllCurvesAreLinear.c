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
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ ** _cmsStageGetPtrToCurveSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsIsToneCurveLinear (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t cmsStageOutputChannels (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool AllCurvesAreLinear(cmsContext ContextID, cmsStage* mpe)
{
    cmsToneCurve** Curves;
    cmsUInt32Number i, n;

    Curves = _cmsStageGetPtrToCurveSet(mpe);
    if (Curves == NULL) return FALSE;

    n = cmsStageOutputChannels(ContextID, mpe);

    for (i=0; i < n; i++) {
        if (!cmsIsToneCurveLinear(ContextID, Curves[i])) return FALSE;
    }

    return TRUE;
}