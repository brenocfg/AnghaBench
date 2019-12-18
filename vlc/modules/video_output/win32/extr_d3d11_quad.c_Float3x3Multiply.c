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

__attribute__((used)) static void Float3x3Multiply(double m1[3 * 3], const double m2[3 * 3])
{
    double a00 = m1[0 + 0*3], a01 = m1[1 + 0*3], a02 = m1[2 + 0*3],
           a10 = m1[0 + 1*3], a11 = m1[1 + 1*3], a12 = m1[2 + 1*3],
           a20 = m1[0 + 2*3], a21 = m1[1 + 2*3], a22 = m1[2 + 2*3];

    for (int i = 0; i < 3; i++) {
        m1[i + 0*3] = a00 * m2[i + 0*3] + a01 * m2[i + 1*3] + a02 * m2[i + 2*3];
        m1[i + 1*3] = a10 * m2[i + 0*3] + a11 * m2[i + 1*3] + a12 * m2[i + 2*3];
        m1[i + 2*3] = a20 * m2[i + 0*3] + a21 * m2[i + 1*3] + a22 * m2[i + 2*3];
    }
}