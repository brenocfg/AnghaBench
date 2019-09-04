#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_5__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_7__ {int /*<<< orphan*/  DeletePending; TYPE_2__ EndOfFile; TYPE_1__ AllocationSize; int /*<<< orphan*/  NumberOfLinks; scalar_t__ Directory; } ;
typedef  TYPE_3__* PFILE_STANDARD_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  DbgP (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void print_std_info(int on, PFILE_STANDARD_INFORMATION info)
{
    if (!on) return;
    DbgP("STD_INFO: Type=%s #Links=%d Alloc=%lx EOF=%lx Delete=%d\n",
        info->Directory?"DIR":"FILE", info->NumberOfLinks, 
        info->AllocationSize.QuadPart, info->EndOfFile.QuadPart, 
        info->DeletePending);
}