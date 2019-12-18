#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  cbz_document_handler ; 
 int /*<<< orphan*/  epub_document_handler ; 
 int /*<<< orphan*/  fz_register_document_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  html_document_handler ; 
 int /*<<< orphan*/  img_document_handler ; 
 int /*<<< orphan*/  pdf_document_handler ; 
 int /*<<< orphan*/  svg_document_handler ; 
 int /*<<< orphan*/  xps_document_handler ; 

void fz_register_document_handlers(fz_context *ctx)
{
#if FZ_ENABLE_PDF
	fz_register_document_handler(ctx, &pdf_document_handler);
#endif /* FZ_ENABLE_PDF */
#if FZ_ENABLE_XPS
	fz_register_document_handler(ctx, &xps_document_handler);
#endif /* FZ_ENABLE_XPS */
#if FZ_ENABLE_SVG
	fz_register_document_handler(ctx, &svg_document_handler);
#endif /* FZ_ENABLE_SVG */
#if FZ_ENABLE_CBZ
	fz_register_document_handler(ctx, &cbz_document_handler);
#endif /* FZ_ENABLE_CBZ */
#if FZ_ENABLE_IMG
	fz_register_document_handler(ctx, &img_document_handler);
#endif /* FZ_ENABLE_IMG */
#if FZ_ENABLE_HTML
	fz_register_document_handler(ctx, &html_document_handler);
#endif /* FZ_ENABLE_HTML */
#if FZ_ENABLE_EPUB
	fz_register_document_handler(ctx, &epub_document_handler);
#endif /* FZ_ENABLE_EPUB */
}