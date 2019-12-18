#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  struct _cms_typehandler_struct* cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
struct TYPE_4__ {int nSegments; int nEntries; int /*<<< orphan*/  Table16; TYPE_1__* Segments; } ;
typedef  TYPE_2__ cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_3__ {int Type; int /*<<< orphan*/ * Params; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsDoubleTo8Fixed8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt16Array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 

__attribute__((used)) static
cmsBool  Type_Curve_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsToneCurve* Curve = (cmsToneCurve*) Ptr;

    if (Curve ->nSegments == 1 && Curve ->Segments[0].Type == 1) {

            // Single gamma, preserve number
            cmsUInt16Number SingleGammaFixed = _cmsDoubleTo8Fixed8(ContextID, Curve ->Segments[0].Params[0]);

            if (!_cmsWriteUInt32Number(ContextID, io, 1)) return FALSE;
            if (!_cmsWriteUInt16Number(ContextID, io, SingleGammaFixed)) return FALSE;
            return TRUE;

    }

    if (!_cmsWriteUInt32Number(ContextID, io, Curve ->nEntries)) return FALSE;
    return _cmsWriteUInt16Array(ContextID, io, Curve ->nEntries, Curve ->Table16);

    cmsUNUSED_PARAMETER(nItems);
    cmsUNUSED_PARAMETER(self);
}