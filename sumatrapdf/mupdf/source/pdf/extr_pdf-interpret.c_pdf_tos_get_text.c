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
struct TYPE_3__ {int /*<<< orphan*/ * text; } ;
typedef  TYPE_1__ pdf_text_object_state ;
typedef  int /*<<< orphan*/  fz_text ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

fz_text *
pdf_tos_get_text(fz_context *ctx, pdf_text_object_state *tos)
{
	fz_text *text = tos->text;

	tos->text = NULL;

	return text;
}