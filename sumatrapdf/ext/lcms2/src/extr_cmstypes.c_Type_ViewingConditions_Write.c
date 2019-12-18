#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  struct _cms_typehandler_struct* cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
struct TYPE_2__ {int /*<<< orphan*/  IlluminantType; int /*<<< orphan*/  SurroundXYZ; int /*<<< orphan*/  IlluminantXYZ; } ;
typedef  TYPE_1__ cmsICCViewingConditions ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteXYZNumber (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (struct _cms_typehandler_struct*) ; 

__attribute__((used)) static
cmsBool Type_ViewingConditions_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsICCViewingConditions* sc = (cmsICCViewingConditions* ) Ptr;

    if (!_cmsWriteXYZNumber(ContextID, io, &sc ->IlluminantXYZ)) return FALSE;
    if (!_cmsWriteXYZNumber(ContextID, io, &sc ->SurroundXYZ)) return FALSE;
    if (!_cmsWriteUInt32Number(ContextID, io, sc ->IlluminantType)) return FALSE;

    return TRUE;

    cmsUNUSED_PARAMETER(nItems);
    cmsUNUSED_PARAMETER(self);
}