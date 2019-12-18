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
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_2__ {int /*<<< orphan*/  Pointer; } ;
typedef  TYPE_1__ FILEMEM ;

/* Variables and functions */
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsUInt32Number MemoryTell(cmsContext ContextID, struct _cms_io_handler* iohandler)
{
    FILEMEM* ResData = (FILEMEM*) iohandler ->stream;
    cmsUNUSED_PARAMETER(ContextID);

    if (ResData == NULL) return 0;
    return ResData -> Pointer;
}