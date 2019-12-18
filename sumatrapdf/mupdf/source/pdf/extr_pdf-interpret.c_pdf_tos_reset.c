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
struct TYPE_3__ {int text_mode; int /*<<< orphan*/  text_bbox; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ pdf_text_object_state ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_empty_rect ; 
 int /*<<< orphan*/  fz_new_text (int /*<<< orphan*/ *) ; 

void
pdf_tos_reset(fz_context *ctx, pdf_text_object_state *tos, int render)
{
	tos->text = fz_new_text(ctx);
	tos->text_mode = render;
	tos->text_bbox = fz_empty_rect;
}