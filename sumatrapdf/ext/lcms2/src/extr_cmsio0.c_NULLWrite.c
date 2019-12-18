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
typedef  scalar_t__ cmsUInt32Number ;
struct TYPE_4__ {scalar_t__ UsedSpace; scalar_t__ stream; } ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  void const* cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {scalar_t__ Pointer; } ;
typedef  TYPE_2__ FILENULL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (void const*) ; 

__attribute__((used)) static
cmsBool  NULLWrite(cmsContext ContextID, cmsIOHANDLER* iohandler, cmsUInt32Number size, const void *Ptr)
{
    FILENULL* ResData = (FILENULL*) iohandler ->stream;
    cmsUNUSED_PARAMETER(ContextID);

    ResData ->Pointer += size;
    if (ResData ->Pointer > iohandler->UsedSpace)
        iohandler->UsedSpace = ResData ->Pointer;

    return TRUE;

    cmsUNUSED_PARAMETER(Ptr);
}