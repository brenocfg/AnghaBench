#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  image; } ;
struct TYPE_7__ {TYPE_1__ i; } ;
struct TYPE_8__ {int x1; int x0; int y1; int y0; } ;
struct TYPE_9__ {TYPE_2__ u; TYPE_3__ bbox; } ;
typedef  TYPE_4__ fz_stext_block ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_image_as_data_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
fz_print_stext_image_as_xhtml(fz_context *ctx, fz_output *out, fz_stext_block *block)
{
	int w = block->bbox.x1 - block->bbox.x0;
	int h = block->bbox.y1 - block->bbox.y0;

	fz_write_printf(ctx, out, "<p><img width=\"%d\" height=\"%d\" src=\"", w, h);
	fz_write_image_as_data_uri(ctx, out, block->u.i.image);
	fz_write_string(ctx, out, "\"/></p>\n");
}