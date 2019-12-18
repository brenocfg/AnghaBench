#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt8Number ;
typedef  int cmsUInt32Number ;
struct TYPE_15__ {scalar_t__ Data; } ;
typedef  TYPE_2__ cmsStage ;
struct TYPE_16__ {int (* Read ) (int /*<<< orphan*/ ,TYPE_3__*,int*,int,int) ;int /*<<< orphan*/  (* Seek ) (int /*<<< orphan*/ ,TYPE_3__*,int) ;} ;
typedef  TYPE_3__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_14__ {int /*<<< orphan*/ * T; } ;
struct TYPE_17__ {int nEntries; TYPE_1__ Tab; } ;
typedef  TYPE_4__ _cmsStageCLutData ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_8_TO_16 (int) ; 
 int /*<<< orphan*/  _cmsReadUInt16Array (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadUInt8Number (int /*<<< orphan*/ ,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  cmsERROR_UNKNOWN_EXTENSION ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* cmsStageAllocCLut16bitGranular (int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageFree (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_3__*,int*,int,int) ; 
 int stub3 (int /*<<< orphan*/ ,TYPE_3__*,int*,int,int) ; 

__attribute__((used)) static
cmsStage* ReadCLUT(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io,
                   cmsUInt32Number Offset, cmsUInt32Number InputChannels, cmsUInt32Number OutputChannels)
{
    cmsUInt8Number  gridPoints8[cmsMAXCHANNELS]; // Number of grid points in each dimension.
    cmsUInt32Number GridPoints[cmsMAXCHANNELS], i;
    cmsUInt8Number  Precision;
    cmsStage* CLUT;
    _cmsStageCLutData* Data;
    cmsUNUSED_PARAMETER(self);

    if (!io -> Seek(ContextID, io, Offset)) return NULL;
    if (io -> Read(ContextID, io, gridPoints8, cmsMAXCHANNELS, 1) != 1) return NULL;


    for (i=0; i < cmsMAXCHANNELS; i++) {

        if (gridPoints8[i] == 1) return NULL; // Impossible value, 0 for no CLUT and then 2 at least
        GridPoints[i] = gridPoints8[i];
    }

    if (!_cmsReadUInt8Number(ContextID, io, &Precision)) return NULL;

    if (!_cmsReadUInt8Number(ContextID, io, NULL)) return NULL;
    if (!_cmsReadUInt8Number(ContextID, io, NULL)) return NULL;
    if (!_cmsReadUInt8Number(ContextID, io, NULL)) return NULL;

    CLUT = cmsStageAllocCLut16bitGranular(ContextID, GridPoints, InputChannels, OutputChannels, NULL);
    if (CLUT == NULL) return NULL;

    Data = (_cmsStageCLutData*) CLUT ->Data;

    // Precision can be 1 or 2 bytes
    if (Precision == 1) {

        cmsUInt8Number  v;

        for (i=0; i < Data ->nEntries; i++) {

            if (io ->Read(ContextID, io, &v, sizeof(cmsUInt8Number), 1) != 1) {
                cmsStageFree(ContextID, CLUT);
                return NULL;
            }
            Data ->Tab.T[i] = FROM_8_TO_16(v);
        }

    }
    else
        if (Precision == 2) {

            if (!_cmsReadUInt16Array(ContextID, io, Data->nEntries, Data ->Tab.T)) {
                cmsStageFree(ContextID, CLUT);
                return NULL;
            }
        }
        else {
            cmsStageFree(ContextID, CLUT);
            cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "Unknown precision of '%d'", Precision);
            return NULL;
        }

    return CLUT;
}