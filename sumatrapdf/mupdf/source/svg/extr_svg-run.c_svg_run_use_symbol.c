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
typedef  int /*<<< orphan*/  svg_state ;
typedef  int /*<<< orphan*/  svg_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_parse_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_parse_viewbox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_parse_viewport (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_run_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
svg_run_use_symbol(fz_context *ctx, fz_device *dev, svg_document *doc, fz_xml *use, fz_xml *symbol, const svg_state *inherit_state)
{
	svg_state local_state = *inherit_state;
	fz_xml *node;

	svg_parse_viewport(ctx, doc, use, &local_state);
	svg_parse_viewbox(ctx, doc, use, &local_state);
	svg_parse_common(ctx, doc, use, &local_state);

	for (node = fz_xml_down(symbol); node; node = fz_xml_next(node))
		svg_run_element(ctx, dev, doc, node, &local_state);
}