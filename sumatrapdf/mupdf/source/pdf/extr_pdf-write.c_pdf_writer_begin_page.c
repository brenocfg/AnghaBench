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
struct TYPE_2__ {int /*<<< orphan*/  contents; int /*<<< orphan*/  resources; int /*<<< orphan*/  mediabox; int /*<<< orphan*/  pdf; } ;
typedef  TYPE_1__ pdf_writer ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_document_writer ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * pdf_page_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fz_device *
pdf_writer_begin_page(fz_context *ctx, fz_document_writer *wri_, fz_rect mediabox)
{
	pdf_writer *wri = (pdf_writer*)wri_;
	wri->mediabox = mediabox;
	return pdf_page_write(ctx, wri->pdf, wri->mediabox, &wri->resources, &wri->contents);
}