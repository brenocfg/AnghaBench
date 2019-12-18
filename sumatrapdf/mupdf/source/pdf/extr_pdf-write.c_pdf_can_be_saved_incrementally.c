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
struct TYPE_3__ {scalar_t__ has_old_style_xrefs; scalar_t__ has_xref_streams; scalar_t__ redacted; scalar_t__ repair_attempted; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

int pdf_can_be_saved_incrementally(fz_context *ctx, pdf_document *doc)
{
	if (doc->repair_attempted)
		return 0;
	if (doc->redacted)
		return 0;
	if (doc->has_xref_streams && doc->has_old_style_xrefs)
		return 0;
	return 1;
}