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
typedef  scalar_t__ wchar_t ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsAssert (int) ; 
 int /*<<< orphan*/  _cmsWriteUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsBool _cmsWriteWCharArray(cmsContext ContextID, cmsIOHANDLER* io, cmsUInt32Number n, const wchar_t* Array)
{
    cmsUInt32Number i;

    _cmsAssert(io != NULL);
    _cmsAssert(!(Array == NULL && n > 0));

    for (i=0; i < n; i++) {
        if (!_cmsWriteUInt16Number(ContextID, io, (cmsUInt16Number) Array[i])) return FALSE;
    }

    return TRUE;
}