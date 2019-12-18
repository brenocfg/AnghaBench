#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  int cmsUInt8Number ;
typedef  size_t cmsUInt32Number ;
struct TYPE_5__ {int /*<<< orphan*/  (* Write ) (int /*<<< orphan*/ ,TYPE_1__*,size_t,int*) ;} ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 
 size_t cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,size_t,int*) ; 

__attribute__((used)) static
cmsBool Type_ColorantOrderType_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsUInt8Number*  ColorantOrder = (cmsUInt8Number*) Ptr;
    cmsUInt32Number i, sz, Count;

    // Get the length
    for (Count=i=0; i < cmsMAXCHANNELS; i++) {
        if (ColorantOrder[i] != 0xFF) Count++;
    }

    if (!_cmsWriteUInt32Number(ContextID, io, Count)) return FALSE;

    sz = Count * sizeof(cmsUInt8Number);
    if (!io -> Write(ContextID, io, sz, ColorantOrder)) return FALSE;

    return TRUE;

    cmsUNUSED_PARAMETER(nItems);
    cmsUNUSED_PARAMETER(self);
}