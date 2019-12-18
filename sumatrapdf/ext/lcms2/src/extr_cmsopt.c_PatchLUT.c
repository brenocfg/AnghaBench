#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
typedef  scalar_t__ cmsUInt16Number ;
struct TYPE_7__ {scalar_t__ Type; scalar_t__ Data; } ;
typedef  TYPE_2__ cmsStage ;
struct TYPE_8__ {double* Domain; scalar_t__* opta; } ;
typedef  TYPE_3__ cmsInterpParams ;
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_6__ {scalar_t__* T; } ;
struct TYPE_9__ {TYPE_1__ Tab; TYPE_3__* Params; } ;
typedef  TYPE_4__ _cmsStageCLutData ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsERROR_INTERNAL ; 
 scalar_t__ cmsSigCLutElemType ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ floor (double) ; 

__attribute__((used)) static
cmsBool  PatchLUT(cmsContext ContextID, cmsStage* CLUT, cmsUInt16Number At[], cmsUInt16Number Value[],
                  cmsUInt32Number nChannelsOut, cmsUInt32Number nChannelsIn)
{
    _cmsStageCLutData* Grid = (_cmsStageCLutData*) CLUT ->Data;
    cmsInterpParams* p16  = Grid ->Params;
    cmsFloat64Number px, py, pz, pw;
    int        x0, y0, z0, w0;
    int        i, index;

    if (CLUT -> Type != cmsSigCLutElemType) {
        cmsSignalError(ContextID, cmsERROR_INTERNAL, "(internal) Attempt to PatchLUT on non-lut stage");
        return FALSE;
    }

    if (nChannelsIn == 4) {

        px = ((cmsFloat64Number) At[0] * (p16->Domain[0])) / 65535.0;
        py = ((cmsFloat64Number) At[1] * (p16->Domain[1])) / 65535.0;
        pz = ((cmsFloat64Number) At[2] * (p16->Domain[2])) / 65535.0;
        pw = ((cmsFloat64Number) At[3] * (p16->Domain[3])) / 65535.0;

        x0 = (int) floor(px);
        y0 = (int) floor(py);
        z0 = (int) floor(pz);
        w0 = (int) floor(pw);

        if (((px - x0) != 0) ||
            ((py - y0) != 0) ||
            ((pz - z0) != 0) ||
            ((pw - w0) != 0)) return FALSE; // Not on exact node

        index = (int) p16 -> opta[3] * x0 +
                (int) p16 -> opta[2] * y0 +
                (int) p16 -> opta[1] * z0 +
                (int) p16 -> opta[0] * w0;
    }
    else
        if (nChannelsIn == 3) {

            px = ((cmsFloat64Number) At[0] * (p16->Domain[0])) / 65535.0;
            py = ((cmsFloat64Number) At[1] * (p16->Domain[1])) / 65535.0;
            pz = ((cmsFloat64Number) At[2] * (p16->Domain[2])) / 65535.0;

            x0 = (int) floor(px);
            y0 = (int) floor(py);
            z0 = (int) floor(pz);

            if (((px - x0) != 0) ||
                ((py - y0) != 0) ||
                ((pz - z0) != 0)) return FALSE;  // Not on exact node

            index = (int) p16 -> opta[2] * x0 +
                    (int) p16 -> opta[1] * y0 +
                    (int) p16 -> opta[0] * z0;
        }
        else
            if (nChannelsIn == 1) {

                px = ((cmsFloat64Number) At[0] * (p16->Domain[0])) / 65535.0;

                x0 = (int) floor(px);

                if (((px - x0) != 0)) return FALSE; // Not on exact node

                index = (int) p16 -> opta[0] * x0;
            }
            else {
                cmsSignalError(ContextID, cmsERROR_INTERNAL, "(internal) %d Channels are not supported on PatchLUT", nChannelsIn);
                return FALSE;
            }

    for (i = 0; i < (int) nChannelsOut; i++)
        Grid->Tab.T[index + i] = Value[i];

    return TRUE;
}