#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_document_writer ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int /*<<< orphan*/  pixmap; int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ fz_cbz_writer ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_new_draw_device_with_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fz_device *
cbz_begin_page(fz_context *ctx, fz_document_writer *wri_, fz_rect mediabox)
{
	fz_cbz_writer *wri = (fz_cbz_writer*)wri_;
	return fz_new_draw_device_with_options(ctx, &wri->options, mediabox, &wri->pixmap);
}