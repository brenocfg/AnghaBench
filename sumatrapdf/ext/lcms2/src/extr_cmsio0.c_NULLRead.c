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
typedef  int cmsUInt32Number ;
struct TYPE_4__ {scalar_t__ stream; } ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  void* cmsContext ;
struct TYPE_5__ {int /*<<< orphan*/  Pointer; } ;
typedef  TYPE_2__ FILENULL ;

/* Variables and functions */
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (void*) ; 

__attribute__((used)) static
cmsUInt32Number NULLRead(cmsContext ContextID, cmsIOHANDLER* iohandler, void *Buffer, cmsUInt32Number size, cmsUInt32Number count)
{
    FILENULL* ResData = (FILENULL*) iohandler ->stream;
    cmsUInt32Number len = size * count;
    cmsUNUSED_PARAMETER(ContextID);

    ResData -> Pointer += len;
    return count;

    cmsUNUSED_PARAMETER(Buffer);
}