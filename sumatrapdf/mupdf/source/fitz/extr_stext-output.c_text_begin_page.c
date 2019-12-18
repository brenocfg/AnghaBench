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
struct TYPE_2__ {int /*<<< orphan*/  opts; int /*<<< orphan*/ * page; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ fz_text_writer ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_document_writer ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_stext_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_stext_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_stext_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_device *
text_begin_page(fz_context *ctx, fz_document_writer *wri_, fz_rect mediabox)
{
	fz_text_writer *wri = (fz_text_writer*)wri_;

	if (wri->page)
	{
		fz_drop_stext_page(ctx, wri->page);
		wri->page = NULL;
	}

	wri->number++;

	wri->page = fz_new_stext_page(ctx, mediabox);
	return fz_new_stext_device(ctx, wri->page, &wri->opts);
}