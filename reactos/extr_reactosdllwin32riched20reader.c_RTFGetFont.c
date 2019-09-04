#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int rtfFNum; struct TYPE_6__* rtfNextFont; } ;
struct TYPE_5__ {TYPE_2__* fontList; } ;
typedef  TYPE_1__ RTF_Info ;
typedef  TYPE_2__ RTFFont ;

/* Variables and functions */

RTFFont *RTFGetFont(const RTF_Info *info, int num)
{
	RTFFont	*f;

	if (num == -1)
		return (info->fontList);
	for (f = info->fontList; f != NULL; f = f->rtfNextFont)
	{
		if (f->rtfFNum == num)
			break;
	}
	return (f);		/* NULL if not found */
}