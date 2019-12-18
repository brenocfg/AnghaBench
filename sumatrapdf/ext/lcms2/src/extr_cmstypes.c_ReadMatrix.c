#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsStage ;
struct TYPE_5__ {int /*<<< orphan*/  (* Seek ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsRead15Fixed16Number (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsStageAllocMatrix (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsStage* ReadMatrix(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsUInt32Number Offset)
{
    cmsFloat64Number dMat[3*3];
    cmsFloat64Number dOff[3];
    cmsStage* Mat;
    cmsUNUSED_PARAMETER(self);

    // Go to address
    if (!io -> Seek(ContextID, io, Offset)) return NULL;

    // Read the Matrix
    if (!_cmsRead15Fixed16Number(ContextID, io, &dMat[0])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dMat[1])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dMat[2])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dMat[3])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dMat[4])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dMat[5])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dMat[6])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dMat[7])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dMat[8])) return NULL;

    if (!_cmsRead15Fixed16Number(ContextID, io, &dOff[0])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dOff[1])) return NULL;
    if (!_cmsRead15Fixed16Number(ContextID, io, &dOff[2])) return NULL;

    Mat = cmsStageAllocMatrix(ContextID, 3, 3, dMat, dOff);

     return Mat;
}