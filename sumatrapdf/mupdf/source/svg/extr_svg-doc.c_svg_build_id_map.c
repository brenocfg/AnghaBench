#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  idmap; } ;
typedef  TYPE_1__ svg_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
svg_build_id_map(fz_context *ctx, svg_document *doc, fz_xml *root)
{
	fz_xml *node;

	char *id_att = fz_xml_att(root, "id");
	if (id_att)
		doc->idmap = fz_tree_insert(ctx, doc->idmap, id_att, root);

	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
		svg_build_id_map(ctx, doc, node);
}