#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ fz_xml ;

/* Variables and functions */
 TYPE_1__* fz_xml_find (TYPE_1__*,char const*) ; 

fz_xml *fz_xml_find_next(fz_xml *item, const char *tag)
{
	if (item)
		item = item->next;
	return fz_xml_find(item, tag);
}