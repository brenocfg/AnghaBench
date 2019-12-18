#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__ d; } ;
struct TYPE_8__ {struct TYPE_8__* next; TYPE_2__ u; } ;
typedef  TYPE_3__ fz_xml ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

fz_xml *fz_xml_find(fz_xml *item, const char *tag)
{
	while (item)
	{
		if (!strcmp(item->u.d.name, tag))
			return item;
		item = item->next;
	}
	return NULL;
}