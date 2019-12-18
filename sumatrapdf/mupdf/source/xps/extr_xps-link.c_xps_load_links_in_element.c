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
typedef  int /*<<< orphan*/  xps_resource ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_link ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xps_load_links_in_canvas (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xps_load_links_in_glyphs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xps_load_links_in_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xps_lookup_alternate_content (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xps_load_links_in_element(fz_context *ctx, xps_document *doc, fz_matrix ctm, char *base_uri, xps_resource *dict, fz_xml *node, fz_link **link)
{
	if (fz_xml_is_tag(node, "Path"))
		xps_load_links_in_path(ctx, doc, ctm, base_uri, dict, node, link);
	else if (fz_xml_is_tag(node, "Glyphs"))
		xps_load_links_in_glyphs(ctx, doc, ctm, base_uri, dict, node, link);
	else if (fz_xml_is_tag(node, "Canvas"))
		xps_load_links_in_canvas(ctx, doc, ctm, base_uri, dict, node, link);
	else if (fz_xml_is_tag(node, "AlternateContent"))
	{
		node = xps_lookup_alternate_content(ctx, doc, node);
		if (node)
			xps_load_links_in_element(ctx, doc, ctm, base_uri, dict, node, link);
	}
}