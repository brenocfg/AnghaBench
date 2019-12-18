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
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  Create_AboveRGB () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  TYPE_RGB_8_PLANAR ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int CheckPlanar8opt(void)
{
    cmsHPROFILE aboveRGB = Create_AboveRGB();
    cmsHPROFILE sRGB = cmsCreate_sRGBProfile(DbgThread());

    cmsHTRANSFORM transform = cmsCreateTransform(DbgThread(),
        sRGB, TYPE_RGB_8_PLANAR,
        aboveRGB, TYPE_RGB_8_PLANAR,
        INTENT_PERCEPTUAL, 0);

    cmsDeleteTransform(DbgThread(), transform);
    cmsCloseProfile(DbgThread(), aboveRGB);
    cmsCloseProfile(DbgThread(), sRGB);

    return 1;
}