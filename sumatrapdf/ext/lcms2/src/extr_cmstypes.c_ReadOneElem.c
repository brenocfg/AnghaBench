#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_3__ {scalar_t__* Offsets; scalar_t__* Sizes; } ;
typedef  TYPE_1__ _cmsDICelem ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsReadUInt32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static
cmsBool ReadOneElem(cmsContext ContextID, cmsIOHANDLER* io,  _cmsDICelem* e, cmsUInt32Number i, cmsUInt32Number BaseOffset)
{
    if (!_cmsReadUInt32Number(ContextID, io, &e->Offsets[i])) return FALSE;
    if (!_cmsReadUInt32Number(ContextID, io, &e ->Sizes[i])) return FALSE;

    // An offset of zero has special meaning and shal be preserved
    if (e ->Offsets[i] > 0)
        e ->Offsets[i] += BaseOffset;
    return TRUE;
}