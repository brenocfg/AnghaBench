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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int CheckFloatlinearXFORM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Create_AboveRGB () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  TYPE_RGB_FLT ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsInt32Number CheckMatrixShaperXFORMFloat(void)
{
    cmsHPROFILE hAbove, hSRGB;
    cmsHTRANSFORM xform;
    cmsInt32Number rc1, rc2;

    hAbove = Create_AboveRGB();
    xform = cmsCreateTransform(DbgThread(), hAbove, TYPE_RGB_FLT, hAbove, TYPE_RGB_FLT,  INTENT_RELATIVE_COLORIMETRIC, 0);
    cmsCloseProfile(DbgThread(), hAbove);
    rc1 = CheckFloatlinearXFORM(xform, 3);
    cmsDeleteTransform(DbgThread(), xform);

    hSRGB = cmsCreate_sRGBProfile(DbgThread());
    xform = cmsCreateTransform(DbgThread(), hSRGB, TYPE_RGB_FLT, hSRGB, TYPE_RGB_FLT,  INTENT_RELATIVE_COLORIMETRIC, 0);
    cmsCloseProfile(DbgThread(), hSRGB);
    rc2 = CheckFloatlinearXFORM(xform, 3);
    cmsDeleteTransform(DbgThread(), xform);


    return rc1 && rc2;
}