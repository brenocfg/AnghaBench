#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xps_resource ;
struct TYPE_9__ {TYPE_1__* cookie; } ;
typedef  TYPE_2__ xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {scalar_t__ abort; } ;

/* Variables and functions */
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * xps_lookup_alternate_content (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_parse_canvas (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_parse_glyphs (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_parse_path (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
xps_parse_element(fz_context *ctx, xps_document *doc, fz_matrix ctm, fz_rect area, char *base_uri, xps_resource *dict, fz_xml *node)
{
	if (doc->cookie && doc->cookie->abort)
		return;
	if (fz_xml_is_tag(node, "Path"))
		xps_parse_path(ctx, doc, ctm, base_uri, dict, node);
	if (fz_xml_is_tag(node, "Glyphs"))
		xps_parse_glyphs(ctx, doc, ctm, base_uri, dict, node);
	if (fz_xml_is_tag(node, "Canvas"))
		xps_parse_canvas(ctx, doc, ctm, area, base_uri, dict, node);
	if (fz_xml_is_tag(node, "AlternateContent"))
	{
		node = xps_lookup_alternate_content(ctx, doc, node);
		if (node)
			xps_parse_element(ctx, doc, ctm, area, base_uri, dict, node);
	}
	/* skip unknown tags (like Foo.Resources and similar) */
}