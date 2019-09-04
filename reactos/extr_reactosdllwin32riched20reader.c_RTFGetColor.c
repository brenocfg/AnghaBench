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
struct TYPE_6__ {int rtfCNum; struct TYPE_6__* rtfNextColor; } ;
struct TYPE_5__ {TYPE_2__* colorList; } ;
typedef  TYPE_1__ RTF_Info ;
typedef  TYPE_2__ RTFColor ;

/* Variables and functions */

RTFColor *RTFGetColor(const RTF_Info *info, int num)
{
	RTFColor	*c;

	if (num == -1)
		return (info->colorList);
	for (c = info->colorList; c != NULL; c = c->rtfNextColor)
	{
		if (c->rtfCNum == num)
			break;
	}
	return (c);		/* NULL if not found */
}