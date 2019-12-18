#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ use_depth; int /*<<< orphan*/  transform; int /*<<< orphan*/  fontsize; int /*<<< orphan*/  viewbox_h; int /*<<< orphan*/  viewbox_w; } ;
typedef  TYPE_1__ svg_state ;
struct TYPE_12__ {int /*<<< orphan*/  idmap; } ;
typedef  TYPE_2__ svg_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ MAX_USE_DEPTH ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_translate (float,float) ; 
 int /*<<< orphan*/ * fz_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svg_parse_common (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 float svg_parse_length (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_run_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  svg_run_use_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
svg_run_use(fz_context *ctx, fz_device *dev, svg_document *doc, fz_xml *root, const svg_state *inherit_state)
{
	svg_state local_state = *inherit_state;

	char *xlink_href_att = fz_xml_att(root, "xlink:href");
	char *x_att = fz_xml_att(root, "x");
	char *y_att = fz_xml_att(root, "y");

	float x = 0;
	float y = 0;

	if (++local_state.use_depth > MAX_USE_DEPTH)
	{
		fz_warn(ctx, "svg: too much recursion");
		return;
	}

	svg_parse_common(ctx, doc, root, &local_state);
	if (x_att) x = svg_parse_length(x_att, local_state.viewbox_w, local_state.fontsize);
	if (y_att) y = svg_parse_length(y_att, local_state.viewbox_h, local_state.fontsize);

	local_state.transform = fz_concat(fz_translate(x, y), local_state.transform);

	if (xlink_href_att && xlink_href_att[0] == '#')
	{
		fz_xml *linked = fz_tree_lookup(ctx, doc->idmap, xlink_href_att + 1);
		if (linked)
		{
			if (fz_xml_is_tag(linked, "symbol"))
				svg_run_use_symbol(ctx, dev, doc, root, linked, &local_state);
			else
				svg_run_element(ctx, dev, doc, linked, &local_state);
			return;
		}
	}

	fz_warn(ctx, "svg: cannot find linked symbol");
}