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
 int /*<<< orphan*/  pdf_eval_function (int /*<<< orphan*/ *,void*,float const*,int,float*,int) ; 

__attribute__((used)) static void
devicen_eval(fz_context *ctx, void *tint, const float *sv, int sn, float *dv, int dn)
{
	pdf_eval_function(ctx, tint, sv, sn, dv, dn);
}