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
struct TYPE_3__ {int /*<<< orphan*/  line; } ;
typedef  TYPE_1__* LinePtr ;
typedef  int /*<<< orphan*/  FileInfoListPtr ;

/* Variables and functions */
 scalar_t__ ConcatFileToFileInfoList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitFileInfoList (int /*<<< orphan*/ ) ; 

int
LineToFileInfoList(LinePtr lp, FileInfoListPtr dst)
{
	InitFileInfoList(dst);
	if (ConcatFileToFileInfoList(dst, lp->line) < 0)
		return (-1);
	return (0);
}