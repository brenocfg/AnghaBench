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
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsDoubleTo15Fixed16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsBool  SaveOneChromaticity(cmsContext ContextID, cmsFloat64Number x, cmsFloat64Number y, cmsIOHANDLER* io)
{
    if (!_cmsWriteUInt32Number(ContextID, io, (cmsUInt32Number) _cmsDoubleTo15Fixed16(ContextID, x))) return FALSE;
    if (!_cmsWriteUInt32Number(ContextID, io, (cmsUInt32Number) _cmsDoubleTo15Fixed16(ContextID, y))) return FALSE;

    return TRUE;
}