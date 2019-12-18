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
typedef  int cmsUInt8Number ;
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  Create_AboveRGB () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  TYPE_RGBA_16_SE ; 
 int /*<<< orphan*/  TYPE_RGBA_8 ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  cmsFLAGS_COPY_ALPHA ; 

__attribute__((used)) static
int CheckSE(void)
{
    cmsHPROFILE input_profile = Create_AboveRGB();
    cmsHPROFILE output_profile = cmsCreate_sRGBProfile(DbgThread());

    cmsHTRANSFORM tr = cmsCreateTransform(DbgThread(), input_profile, TYPE_RGBA_8, output_profile, TYPE_RGBA_16_SE, INTENT_RELATIVE_COLORIMETRIC, cmsFLAGS_COPY_ALPHA);

    cmsUInt8Number rgba[4] = { 40, 41, 41, 0xfa };
    cmsUInt16Number out[4];

    cmsDoTransform(DbgThread(), tr, rgba, out, 1);
    cmsCloseProfile(DbgThread(), input_profile);
    cmsCloseProfile(DbgThread(), output_profile);
    cmsDeleteTransform(DbgThread(), tr);

    if (out[0] != 0xf622 || out[1] != 0x7f24 || out[2] != 0x7f24)
        return 0;

    return 1;
}