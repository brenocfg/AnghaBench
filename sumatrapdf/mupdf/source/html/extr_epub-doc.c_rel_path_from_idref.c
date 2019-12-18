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
 char const* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_find_down (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_find_next (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static const char *
rel_path_from_idref(fz_xml *manifest, const char *idref)
{
	fz_xml *item;
	if (!idref)
		return NULL;
	item = fz_xml_find_down(manifest, "item");
	while (item)
	{
		const char *id = fz_xml_att(item, "id");
		if (id && !strcmp(id, idref))
			return fz_xml_att(item, "href");
		item = fz_xml_find_next(item, "item");
	}
	return NULL;
}