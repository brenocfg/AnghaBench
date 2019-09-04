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
struct TYPE_5__ {TYPE_1__* first; } ;
struct TYPE_4__ {int /*<<< orphan*/  line; struct TYPE_4__* next; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__* LineListPtr ;
typedef  int /*<<< orphan*/  FileInfoListPtr ;

/* Variables and functions */
 scalar_t__ ConcatFileToFileInfoList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitFileInfoList (int /*<<< orphan*/ ) ; 

int
LineListToFileInfoList(LineListPtr src, FileInfoListPtr dst)
{
	LinePtr lp, lp2;

	InitFileInfoList(dst);
	for (lp = src->first; lp != NULL; lp = lp2) {
		lp2 = lp->next;
		if (ConcatFileToFileInfoList(dst, lp->line) < 0)
			return (-1);
	}
	return (0);
}