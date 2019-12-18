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

/* Variables and functions */

__attribute__((used)) static void Float3x3Inverse(double in_out[3 * 3])
{
    double m00 = in_out[0 + 0*3], m01 = in_out[1 + 0*3], m02 = in_out[2 + 0*3],
          m10 = in_out[0 + 1*3], m11 = in_out[1 + 1*3], m12 = in_out[2 + 1*3],
          m20 = in_out[0 + 2*3], m21 = in_out[1 + 2*3], m22 = in_out[2 + 2*3];

    // calculate the adjoint
    in_out[0 + 0*3] =  (m11 * m22 - m21 * m12);
    in_out[1 + 0*3] = -(m01 * m22 - m21 * m02);
    in_out[2 + 0*3] =  (m01 * m12 - m11 * m02);
    in_out[0 + 1*3] = -(m10 * m22 - m20 * m12);
    in_out[1 + 1*3] =  (m00 * m22 - m20 * m02);
    in_out[2 + 1*3] = -(m00 * m12 - m10 * m02);
    in_out[0 + 2*3] =  (m10 * m21 - m20 * m11);
    in_out[1 + 2*3] = -(m00 * m21 - m20 * m01);
    in_out[2 + 2*3] =  (m00 * m11 - m10 * m01);

    // calculate the determinant (as inverse == 1/det * adjoint,
    // adjoint * m == identity * det, so this calculates the det)
    double det = m00 * in_out[0 + 0*3] + m10 * in_out[1 + 0*3] + m20 * in_out[2 + 0*3];
    det = 1.0f / det;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            in_out[j + i*3] *= det;
    }
}