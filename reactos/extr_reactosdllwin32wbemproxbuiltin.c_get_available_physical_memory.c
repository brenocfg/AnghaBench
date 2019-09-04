#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  status ;
typedef  int UINT64 ;
struct TYPE_3__ {int dwLength; int ullAvailPhys; } ;
typedef  TYPE_1__ MEMORYSTATUSEX ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalMemoryStatusEx (TYPE_1__*) ; 

__attribute__((used)) static UINT64 get_available_physical_memory(void)
{
    MEMORYSTATUSEX status;

    status.dwLength = sizeof(status);
    if (!GlobalMemoryStatusEx( &status )) return 1024 * 1024 * 1024;
    return status.ullAvailPhys;
}