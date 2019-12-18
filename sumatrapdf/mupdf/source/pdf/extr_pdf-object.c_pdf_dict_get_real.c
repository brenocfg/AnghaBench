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
 int /*<<< orphan*/  pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float pdf_to_real (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

float pdf_dict_get_real(fz_context *ctx, pdf_obj *dict, pdf_obj *key)
{
	return pdf_to_real(ctx, pdf_dict_get(ctx, dict, key));
}