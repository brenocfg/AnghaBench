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

__attribute__((used)) static void GetTextureCropParamsForStereo(unsigned i_nbTextures,
                                          const float *stereoCoefs,
                                          const float *stereoOffsets,
                                          float *left, float *top,
                                          float *right, float *bottom)
{
    for (unsigned i = 0; i < i_nbTextures; ++i)
    {
        float f_2eyesWidth = right[i] - left[i];
        left[i] = left[i] + f_2eyesWidth * stereoOffsets[0];
        right[i] = left[i] + f_2eyesWidth * stereoCoefs[0];

        float f_2eyesHeight = bottom[i] - top[i];
        top[i] = top[i] + f_2eyesHeight * stereoOffsets[1];
        bottom[i] = top[i] + f_2eyesHeight * stereoCoefs[1];
    }
}