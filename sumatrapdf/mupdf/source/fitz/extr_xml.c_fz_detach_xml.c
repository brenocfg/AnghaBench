#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* root; } ;
typedef  TYPE_2__ fz_xml_doc ;
struct TYPE_8__ {TYPE_1__* up; } ;
typedef  TYPE_3__ fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int /*<<< orphan*/ * down; } ;

/* Variables and functions */

void fz_detach_xml(fz_context *ctx, fz_xml_doc *xml, fz_xml *node)
{
	if (node->up)
		node->up->down = NULL;
	xml->root = node;
}