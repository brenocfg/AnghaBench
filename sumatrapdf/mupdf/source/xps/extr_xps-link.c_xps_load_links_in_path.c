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
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_link ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_bound_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_xml_find_down (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xps_add_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xps_parse_abbreviated_geometry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/ * xps_parse_path_geometry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xps_parse_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xps_resolve_resource_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xps_load_links_in_path(fz_context *ctx, xps_document *doc, fz_matrix ctm,
		char *base_uri, xps_resource *dict, fz_xml *root, fz_link **link)
{
	char *navigate_uri_att = fz_xml_att(root, "FixedPage.NavigateUri");
	if (navigate_uri_att)
	{
		char *transform_att = fz_xml_att(root, "RenderTransform");
		fz_xml *transform_tag = fz_xml_down(fz_xml_find_down(root, "Path.RenderTransform"));

		char *data_att = fz_xml_att(root, "Data");
		fz_xml *data_tag = fz_xml_down(fz_xml_find_down(root, "Path.Data"));

		fz_path *path = NULL;
		int fill_rule;
		fz_rect area;

		xps_resolve_resource_reference(ctx, doc, dict, &data_att, &data_tag, NULL);
		xps_resolve_resource_reference(ctx, doc, dict, &transform_att, &transform_tag, NULL);

		ctm = xps_parse_transform(ctx, doc, transform_att, transform_tag, ctm);

		if (data_att)
			path = xps_parse_abbreviated_geometry(ctx, doc, data_att, &fill_rule);
		else if (data_tag)
			path = xps_parse_path_geometry(ctx, doc, dict, data_tag, 0, &fill_rule);
		if (path)
		{
			area = fz_bound_path(ctx, path, NULL, ctm);
			fz_drop_path(ctx, path);
			xps_add_link(ctx, doc, area, base_uri, navigate_uri_att, link);
		}
	}
}