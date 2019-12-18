#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  size_t cmsUInt32Number ;
struct TYPE_8__ {size_t (* Tell ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_9__ {size_t* Offsets; size_t* Sizes; } ;
typedef  TYPE_2__ _cmsDICelem ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsWriteWCharArray (int /*<<< orphan*/ ,TYPE_1__*,size_t,int /*<<< orphan*/  const*) ; 
 size_t mywcslen (int /*<<< orphan*/  const*) ; 
 size_t stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
cmsBool WriteOneWChar(cmsContext ContextID, cmsIOHANDLER* io,  _cmsDICelem* e, cmsUInt32Number i, const wchar_t * wcstr, cmsUInt32Number BaseOffset)
{
    cmsUInt32Number Before = io ->Tell(ContextID, io);
    cmsUInt32Number n;

    e ->Offsets[i] = Before - BaseOffset;

    if (wcstr == NULL) {
        e ->Sizes[i] = 0;
        e ->Offsets[i] = 0;
        return TRUE;
    }

    n = mywcslen(wcstr);
    if (!_cmsWriteWCharArray(ContextID, io,  n, wcstr)) return FALSE;

    e ->Sizes[i] = io ->Tell(ContextID, io) - Before;
    return TRUE;
}