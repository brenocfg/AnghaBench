#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * (* get_output_intent ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  TYPE_1__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

fz_colorspace *
fz_document_output_intent(fz_context *ctx, fz_document *doc)
{
	if (doc && doc->get_output_intent)
		return doc->get_output_intent(ctx, doc);
	return NULL;
}