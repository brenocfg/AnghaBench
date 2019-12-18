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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char const* pdf_to_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const char *pdf_array_get_text_string(fz_context *ctx, pdf_obj *array, int index)
{
	return pdf_to_text_string(ctx, pdf_array_get(ctx, array, index));
}