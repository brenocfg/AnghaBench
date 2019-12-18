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
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_identity ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xps_parse_render_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static fz_matrix
xps_parse_matrix_transform(fz_context *ctx, xps_document *doc, fz_xml *root)
{
	if (fz_xml_is_tag(root, "MatrixTransform"))
	{
		char *transform = fz_xml_att(root, "Matrix");
		if (transform)
			return xps_parse_render_transform(ctx, doc, transform);
	}
	return fz_identity;
}