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
struct _cms_io_handler {scalar_t__ UsedSpace; scalar_t__ stream; } ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_2__ {scalar_t__ Pointer; scalar_t__ Size; scalar_t__ Block; } ;
typedef  TYPE_1__ FILEMEM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,void const*,scalar_t__) ; 

__attribute__((used)) static
cmsBool MemoryWrite(cmsContext ContextID, struct _cms_io_handler* iohandler, cmsUInt32Number size, const void *Ptr)
{
    FILEMEM* ResData = (FILEMEM*) iohandler ->stream;
    cmsUNUSED_PARAMETER(ContextID);

    if (ResData == NULL) return FALSE; // Housekeeping

    // Check for available space. Clip.
    if (ResData->Pointer + size > ResData->Size) {
        size = ResData ->Size - ResData->Pointer;
    }

    if (size == 0) return TRUE;     // Write zero bytes is ok, but does nothing

    memmove(ResData ->Block + ResData ->Pointer, Ptr, size);
    ResData ->Pointer += size;

    if (ResData ->Pointer > iohandler->UsedSpace)
        iohandler->UsedSpace = ResData ->Pointer;

    return TRUE;
}