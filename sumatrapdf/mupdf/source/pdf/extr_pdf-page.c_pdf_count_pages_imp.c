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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int pdf_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pdf_count_pages_imp(fz_context *ctx, fz_document *doc, int chapter)
{
	return pdf_count_pages(ctx, (pdf_document*)doc);
}