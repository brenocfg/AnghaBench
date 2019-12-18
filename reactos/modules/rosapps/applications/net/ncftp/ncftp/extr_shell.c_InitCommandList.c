#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  qsort_proc_t ;
typedef  int /*<<< orphan*/  Command ;

/* Variables and functions */
 scalar_t__ CommandSortCmp ; 
 int /*<<< orphan*/  gCommands ; 
 int /*<<< orphan*/  gNumCommands ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
InitCommandList(void)
{
	qsort(gCommands, gNumCommands, sizeof(Command), (qsort_proc_t) CommandSortCmp);
}