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
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_outline ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * xps_parse_document_outline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fz_outline *
xps_parse_document_structure(fz_context *ctx, xps_document *doc, fz_xml *root)
{
	fz_xml *node;
	if (fz_xml_is_tag(root, "DocumentStructure"))
	{
		node = fz_xml_down(root);
		if (node && fz_xml_is_tag(node, "DocumentStructure.Outline"))
		{
			node = fz_xml_down(node);
			if (node && fz_xml_is_tag(node, "DocumentOutline"))
				return xps_parse_document_outline(ctx, doc, node);
		}
	}
	return NULL;
}