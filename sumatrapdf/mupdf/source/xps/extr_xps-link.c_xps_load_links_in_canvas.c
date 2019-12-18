#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* parent; } ;
typedef  TYPE_1__ xps_resource ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_link ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_find_down (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_drop_resource_dictionary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xps_load_links_in_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_1__* xps_parse_resource_dictionary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_parse_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xps_resolve_resource_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xps_load_links_in_canvas(fz_context *ctx, xps_document *doc, fz_matrix ctm,
		char *base_uri, xps_resource *dict, fz_xml *root, fz_link **link)
{
	xps_resource *new_dict = NULL;
	fz_xml *node;

	char *navigate_uri_att = fz_xml_att(root, "FixedPage.NavigateUri");
	char *transform_att = fz_xml_att(root, "RenderTransform");
	fz_xml *transform_tag = fz_xml_down(fz_xml_find_down(root, "Canvas.RenderTransform"));
	fz_xml *resource_tag = fz_xml_down(fz_xml_find_down(root, "Canvas.Resources"));

	if (resource_tag)
	{
		new_dict = xps_parse_resource_dictionary(ctx, doc, base_uri, resource_tag);
		if (new_dict)
		{
			new_dict->parent = dict;
			dict = new_dict;
		}
	}

	xps_resolve_resource_reference(ctx, doc, dict, &transform_att, &transform_tag, NULL);

	ctm = xps_parse_transform(ctx, doc, transform_att, transform_tag, ctm);

	if (navigate_uri_att)
		fz_warn(ctx, "FixedPage.NavigateUri attribute on Canvas element");

	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
		xps_load_links_in_element(ctx, doc, ctm, base_uri, dict, node, link);

	if (new_dict)
		xps_drop_resource_dictionary(ctx, doc, new_dict);
}