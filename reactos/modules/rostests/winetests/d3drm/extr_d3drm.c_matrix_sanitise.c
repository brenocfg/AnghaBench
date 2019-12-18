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
typedef  float** D3DRMMATRIX4D ;

/* Variables and functions */

__attribute__((used)) static void matrix_sanitise(D3DRMMATRIX4D m)
{
    unsigned int i, j;

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            if (m[i][j] > -1e-7f && m[i][j] < 1e-7f)
                m[i][j] = 0.0f;
        }
    }
}