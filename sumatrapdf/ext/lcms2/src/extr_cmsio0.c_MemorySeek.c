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
struct _cms_io_handler {scalar_t__ stream; } ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_2__ {scalar_t__ Size; scalar_t__ Pointer; } ;
typedef  TYPE_1__ FILEMEM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsERROR_SEEK ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
cmsBool  MemorySeek(cmsContext ContextID, struct _cms_io_handler* iohandler, cmsUInt32Number offset)
{
    FILEMEM* ResData = (FILEMEM*) iohandler ->stream;

    if (offset > ResData ->Size) {
        cmsSignalError(ContextID, cmsERROR_SEEK,  "Too few data; probably corrupted profile");
        return FALSE;
    }

    ResData ->Pointer = offset;
    return TRUE;
}