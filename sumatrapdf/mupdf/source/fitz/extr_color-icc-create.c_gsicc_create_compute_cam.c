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
 float D50_X ; 
 float D50_Y ; 
 float D50_Z ; 
 int /*<<< orphan*/  matrixmult (int /*<<< orphan*/ *,float*,int,int,float*,int,int,float*) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gsicc_create_compute_cam(fz_context *ctx, float white_src[], float *cam)
{
	float cat02matrix[] = { 0.7328f, 0.4296f, -0.1624f, -0.7036f, 1.6975f, 0.0061f, 0.003f, 0.0136f, 0.9834f };
	float cat02matrixinv[] = { 1.0961f, -0.2789f, 0.1827f, 0.4544f, 0.4735f, 0.0721f, -0.0096f, -0.0057f, 1.0153f };
	float vonkries_diag[9];
	float temp_matrix[9];
	float lms_wp_src[3], lms_wp_des[3];
	int k;
	float d50[3] = { D50_X, D50_Y, D50_Z };

	matrixmult(ctx, cat02matrix, 3, 3, white_src, 3, 1, lms_wp_src);
	matrixmult(ctx, cat02matrix, 3, 3, d50, 3, 1, lms_wp_des);
	memset(&(vonkries_diag[0]), 0, sizeof(float) * 9);

	for (k = 0; k < 3; k++)
	{
		if (lms_wp_src[k] > 0)
			vonkries_diag[k * 3 + k] = lms_wp_des[k] / lms_wp_src[k];
		else
			vonkries_diag[k * 3 + k] = 1;
	}
	matrixmult(ctx, &(vonkries_diag[0]), 3, 3, cat02matrix, 3, 3, temp_matrix);
	matrixmult(ctx, &(cat02matrixinv[0]), 3, 3, temp_matrix, 3, 3, cam);
}