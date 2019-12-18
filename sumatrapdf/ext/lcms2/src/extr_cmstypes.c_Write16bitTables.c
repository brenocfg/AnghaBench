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
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {size_t nCurves; TYPE_1__** TheCurves; } ;
typedef  TYPE_2__ _cmsStageToneCurvesData ;
struct TYPE_4__ {size_t nEntries; int /*<<< orphan*/ * Table16; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsBool Write16bitTables(cmsContext ContextID, cmsIOHANDLER* io, _cmsStageToneCurvesData* Tables)
{
    cmsUInt32Number j;
    cmsUInt32Number i;
    cmsUInt16Number val;
    cmsUInt32Number nEntries;

    _cmsAssert(Tables != NULL);

    nEntries = Tables->TheCurves[0]->nEntries;

    for (i=0; i < Tables ->nCurves; i++) {

        for (j=0; j < nEntries; j++) {

            val = Tables->TheCurves[i]->Table16[j];
            if (!_cmsWriteUInt16Number(ContextID, io, val)) return FALSE;
        }
    }
    return TRUE;
}