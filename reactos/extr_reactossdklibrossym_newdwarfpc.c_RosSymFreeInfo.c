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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {TYPE_1__* Parameters; int /*<<< orphan*/ * FunctionName; int /*<<< orphan*/ * FileName; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ValueName; } ;
typedef  TYPE_2__* PROSSYM_LINEINFO ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

VOID RosSymFreeInfo(PROSSYM_LINEINFO LineInfo)
{
    int i;
	free(LineInfo->FileName);
	LineInfo->FileName = NULL;
	free(LineInfo->FunctionName);
	LineInfo->FunctionName = NULL;
    for (i = 0; i < sizeof(LineInfo->Parameters)/sizeof(LineInfo->Parameters[0]); i++)
        free(LineInfo->Parameters[i].ValueName);
}