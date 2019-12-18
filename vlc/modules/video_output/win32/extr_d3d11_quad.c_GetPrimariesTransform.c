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
typedef  size_t video_color_primaries_t ;
struct cie1931_primaries {int /*<<< orphan*/  white; } ;
typedef  double FLOAT ;

/* Variables and functions */
 int /*<<< orphan*/  ChromaticAdaptation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  Float3x3Multiply (double*,double*) ; 
 int /*<<< orphan*/  GetRGB2XYZMatrix (struct cie1931_primaries const*,double*) ; 
 int /*<<< orphan*/  GetXYZ2RGBMatrix (struct cie1931_primaries const*,double*) ; 
 struct cie1931_primaries* STANDARD_PRIMARIES ; 

__attribute__((used)) static void GetPrimariesTransform(FLOAT Primaries[4*4], video_color_primaries_t src,
                                  video_color_primaries_t dst)
{
    const struct cie1931_primaries *p_src = &STANDARD_PRIMARIES[src];
    const struct cie1931_primaries *p_dst = &STANDARD_PRIMARIES[dst];
    double rgb2xyz[3 * 3], xyz2rgb[3 * 3];

    /* src[RGB] -> src[XYZ] */
    GetRGB2XYZMatrix(p_src, rgb2xyz);

    /* src[XYZ] -> dst[XYZ] */
    ChromaticAdaptation(&p_src->white, &p_dst->white, rgb2xyz);

    /* dst[XYZ] -> dst[RGB] */
    GetXYZ2RGBMatrix(p_dst, xyz2rgb);

    /* src[RGB] -> src[XYZ] -> dst[XYZ] -> dst[RGB] */
    Float3x3Multiply(xyz2rgb, rgb2xyz);

    for (size_t i=0;i<3; ++i)
    {
        for (size_t j=0;j<3; ++j)
            Primaries[j + i*4] = xyz2rgb[j + i*3];
        Primaries[3 + i*4] = 0;
    }
    for (size_t j=0;j<4; ++j)
        Primaries[j + 3*4] = j == 3;
}