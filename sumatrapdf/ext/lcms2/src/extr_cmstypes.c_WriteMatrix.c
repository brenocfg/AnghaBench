#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
struct TYPE_4__ {scalar_t__ Data; } ;
typedef  TYPE_1__ cmsStage ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {int /*<<< orphan*/ * Offset; int /*<<< orphan*/ * Double; } ;
typedef  TYPE_2__ _cmsStageMatrixData ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsWrite15Fixed16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 

__attribute__((used)) static
cmsBool  WriteMatrix(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, cmsStage* mpe)
{
    _cmsStageMatrixData* m = (_cmsStageMatrixData*) mpe -> Data;

    // Write the Matrix
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Double[0])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Double[1])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Double[2])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Double[3])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Double[4])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Double[5])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Double[6])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Double[7])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Double[8])) return FALSE;

    if (m ->Offset != NULL) {

    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Offset[0])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Offset[1])) return FALSE;
    if (!_cmsWrite15Fixed16Number(ContextID, io, m -> Offset[2])) return FALSE;
    }
    else {
        if (!_cmsWrite15Fixed16Number(ContextID, io, 0)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 0)) return FALSE;
        if (!_cmsWrite15Fixed16Number(ContextID, io, 0)) return FALSE;

    }


    return TRUE;

    cmsUNUSED_PARAMETER(self);
}