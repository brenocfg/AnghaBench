#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* down; } ;
typedef  TYPE_1__ fz_xml ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_TEXT_ITEM (TYPE_1__*) ; 

fz_xml *fz_xml_down(fz_xml *item)
{
	return item && !FZ_TEXT_ITEM(item) ? item->down : NULL;
}