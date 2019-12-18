#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xps_resource ;
struct TYPE_5__ {TYPE_1__* fix; int /*<<< orphan*/  xml; } ;
typedef  TYPE_2__ xps_page ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_link ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_find_down (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_root (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  xps_drop_resource_dictionary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_load_links_in_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xps_parse_resource_dictionary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xps_load_links_in_fixed_page(fz_context *ctx, xps_document *doc, fz_matrix ctm, xps_page *page, fz_link **link)
{
	fz_xml *root, *node, *resource_tag;
	xps_resource *dict = NULL;
	char base_uri[1024];
	char *s;

	root = fz_xml_root(page->xml);

	if (!root)
		return;

	fz_strlcpy(base_uri, page->fix->name, sizeof base_uri);
	s = strrchr(base_uri, '/');
	if (s)
		s[1] = 0;

	resource_tag = fz_xml_down(fz_xml_find_down(root, "FixedPage.Resources"));
	if (resource_tag)
		dict = xps_parse_resource_dictionary(ctx, doc, base_uri, resource_tag);

	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
		xps_load_links_in_element(ctx, doc, ctm, base_uri, dict, node, link);

	if (dict)
		xps_drop_resource_dictionary(ctx, doc, dict);
}