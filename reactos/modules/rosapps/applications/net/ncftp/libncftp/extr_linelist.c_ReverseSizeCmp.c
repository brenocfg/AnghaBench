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
struct TYPE_2__ {scalar_t__ size; } ;
typedef  TYPE_1__* FileInfoPtr ;

/* Variables and functions */

__attribute__((used)) static int
ReverseSizeCmp(const void *a, const void *b)
{
	FileInfoPtr *fipa, *fipb;

	fipa = (FileInfoPtr *) a;
	fipb = (FileInfoPtr *) b;
	if ((**fipa).size == (**fipb).size)
		return (0);
	else if ((**fipa).size < (**fipb).size)
		return (-1);
	return (1);
}