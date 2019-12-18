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
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ pdf_load_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

fz_page *pdf_load_page_imp(fz_context *ctx, fz_document *doc, int chapter, int number)
{
	return (fz_page*)pdf_load_page(ctx, (pdf_document*)doc, number);
}