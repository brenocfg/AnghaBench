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
typedef  int /*<<< orphan*/  icS15Fixed16Number ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  D50_X ; 
 int /*<<< orphan*/  D50_Y ; 
 int /*<<< orphan*/  D50_Z ; 
 int /*<<< orphan*/  double2XYZtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_D50(fz_context *ctx, icS15Fixed16Number XYZ[])
{
	XYZ[0] = double2XYZtype(ctx, D50_X);
	XYZ[1] = double2XYZtype(ctx, D50_Y);
	XYZ[2] = double2XYZtype(ctx, D50_Z);
}