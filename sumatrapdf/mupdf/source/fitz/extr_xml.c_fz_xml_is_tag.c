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
struct TYPE_8__ {TYPE_2__ u; } ;
typedef  TYPE_3__ fz_xml ;

/* Variables and functions */
 scalar_t__ FZ_TEXT_ITEM (TYPE_3__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int fz_xml_is_tag(fz_xml *item, const char *name)
{
	if (!item || FZ_TEXT_ITEM(item))
		return 0;
	return !strcmp(item->u.d.name, name);
}