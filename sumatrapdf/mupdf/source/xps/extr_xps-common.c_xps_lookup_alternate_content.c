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
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_strlcpy (char*,scalar_t__,int) ; 
 char* fz_strsep (char**,char*) ; 
 scalar_t__ fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

fz_xml *
xps_lookup_alternate_content(fz_context *ctx, xps_document *doc, fz_xml *node)
{
	for (node = fz_xml_down(node); node; node = fz_xml_next(node))
	{
		if (fz_xml_is_tag(node, "Choice") && fz_xml_att(node, "Requires"))
		{
			char list[64];
			char *next = list, *item;
			fz_strlcpy(list, fz_xml_att(node, "Requires"), sizeof(list));
			while ((item = fz_strsep(&next, " \t\r\n")) != NULL && (!*item || !strcmp(item, "xps")));
			if (!item)
				return fz_xml_down(node);
		}
		else if (fz_xml_is_tag(node, "Fallback"))
			return fz_xml_down(node);
	}
	return NULL;
}