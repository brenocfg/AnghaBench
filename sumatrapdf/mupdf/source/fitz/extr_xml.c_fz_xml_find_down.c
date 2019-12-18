#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_xml ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_find (int /*<<< orphan*/ *,char const*) ; 

fz_xml *fz_xml_find_down(fz_xml *item, const char *tag)
{
	if (item)
		item = fz_xml_down(item);
	return fz_xml_find(item, tag);
}