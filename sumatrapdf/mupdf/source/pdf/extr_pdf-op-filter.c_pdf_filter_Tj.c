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
typedef  int /*<<< orphan*/  pdf_processor ;
typedef  int /*<<< orphan*/  pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  filter_show_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void
pdf_filter_Tj(fz_context *ctx, pdf_processor *proc, char *str, int len)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_show_string(ctx, p, (unsigned char *)str, len);
}