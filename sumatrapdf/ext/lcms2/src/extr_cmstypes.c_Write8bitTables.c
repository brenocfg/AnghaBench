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
typedef  scalar_t__ cmsUInt8Number ;
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {TYPE_1__** TheCurves; } ;
typedef  TYPE_2__ _cmsStageToneCurvesData ;
struct TYPE_4__ {int nEntries; int* Table16; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FROM_16_TO_8 (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsWriteUInt8Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cmsERROR_RANGE ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
cmsBool Write8bitTables(cmsContext ContextID, cmsIOHANDLER* io, cmsUInt32Number n, _cmsStageToneCurvesData* Tables)
{
    int j;
    cmsUInt32Number i;
    cmsUInt8Number val;

    for (i=0; i < n; i++) {

        if (Tables) {

            // Usual case of identity curves
            if ((Tables ->TheCurves[i]->nEntries == 2) &&
                (Tables->TheCurves[i]->Table16[0] == 0) &&
                (Tables->TheCurves[i]->Table16[1] == 65535)) {

                    for (j=0; j < 256; j++) {
                        if (!_cmsWriteUInt8Number(ContextID, io, (cmsUInt8Number) j)) return FALSE;
                    }
            }
            else
                if (Tables ->TheCurves[i]->nEntries != 256) {
                    cmsSignalError(ContextID, cmsERROR_RANGE, "LUT8 needs 256 entries on prelinearization");
                    return FALSE;
                }
                else
                    for (j=0; j < 256; j++) {

                        val = (cmsUInt8Number) FROM_16_TO_8(Tables->TheCurves[i]->Table16[j]);

                        if (!_cmsWriteUInt8Number(ContextID, io, val)) return FALSE;
                    }
        }
    }
    return TRUE;
}