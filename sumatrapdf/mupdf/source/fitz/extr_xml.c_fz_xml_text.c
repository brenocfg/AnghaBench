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
struct TYPE_5__ {char* text; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ fz_xml ;

/* Variables and functions */
 scalar_t__ FZ_TEXT_ITEM (TYPE_2__*) ; 

char *fz_xml_text(fz_xml *item)
{
	return (item && FZ_TEXT_ITEM(item)) ? item->u.text : NULL;
}