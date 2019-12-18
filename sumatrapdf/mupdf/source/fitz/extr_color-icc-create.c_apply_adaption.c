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

__attribute__((used)) static void
apply_adaption(fz_context *ctx, float matrix[], float in[], float out[])
{
	out[0] = matrix[0] * in[0] + matrix[1] * in[1] + matrix[2] * in[2];
	out[1] = matrix[3] * in[0] + matrix[4] * in[1] + matrix[5] * in[2];
	out[2] = matrix[6] * in[0] + matrix[7] * in[1] + matrix[8] * in[2];
}