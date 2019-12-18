#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ocg; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int num_configs; } ;

/* Variables and functions */

int
pdf_count_layer_configs(fz_context *ctx, pdf_document *doc)
{
	/* If no OCProperties, then no OCGs */
	if (!doc || !doc->ocg)
		return 0;
	return doc->ocg->num_configs;
}