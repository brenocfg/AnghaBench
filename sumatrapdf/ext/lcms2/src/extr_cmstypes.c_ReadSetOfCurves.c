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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsStage ;
struct TYPE_6__ {int /*<<< orphan*/  (* Seek ) (int /*<<< orphan*/ ,TYPE_1__*,int) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/ * FALSE ; 
 int /*<<< orphan*/ * ReadEmbeddedCurve (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_1__*) ; 
 int /*<<< orphan*/  _cmsReadAlignment (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/ * cmsStageAllocToneCurves (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static
cmsStage* ReadSetOfCurves(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number Offset, cmsUInt32Number nCurves)
{
    cmsToneCurve* Curves[cmsMAXCHANNELS];
    cmsUInt32Number i;
    cmsStage* Lin = NULL;

    if (nCurves > cmsMAXCHANNELS) return FALSE;

    if (!io -> Seek(ContextID, io, Offset)) return FALSE;

    for (i=0; i < nCurves; i++)
        Curves[i] = NULL;

    for (i=0; i < nCurves; i++) {

        Curves[i] = ReadEmbeddedCurve(ContextID, self, io);
        if (Curves[i] == NULL) goto Error;
        if (!_cmsReadAlignment(ContextID, io)) goto Error;

    }

    Lin = cmsStageAllocToneCurves(ContextID, nCurves, Curves);

Error:
    for (i=0; i < nCurves; i++)
        cmsFreeToneCurve(ContextID, Curves[i]);

    return Lin;
}