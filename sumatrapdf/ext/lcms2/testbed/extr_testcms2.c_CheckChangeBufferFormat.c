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
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  CheckOneRGB (int /*<<< orphan*/ *,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  CheckOneRGB_double (int /*<<< orphan*/ *,double,double,int,double,double,int) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  TYPE_BGR_16 ; 
 int /*<<< orphan*/  TYPE_RGB_16 ; 
 int /*<<< orphan*/  TYPE_RGB_DBL ; 
 int /*<<< orphan*/ * cmsCloneTransformChangingFormats (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckChangeBufferFormat(void)
{
    cmsHPROFILE hsRGB = cmsCreate_sRGBProfile(DbgThread());
    cmsHTRANSFORM xform;
    cmsHTRANSFORM xform2;


    xform = cmsCreateTransform(DbgThread(), hsRGB, TYPE_RGB_16, hsRGB, TYPE_RGB_16, INTENT_PERCEPTUAL, 0);
    cmsCloseProfile(DbgThread(), hsRGB);
    if (xform == NULL) return 0;


    if (!CheckOneRGB(xform, 0, 0, 0, 0, 0, 0)) return 0;
    if (!CheckOneRGB(xform, 120, 0, 0, 120, 0, 0)) return 0;
    if (!CheckOneRGB(xform, 0, 222, 255, 0, 222, 255)) return 0;

    xform2 = cmsCloneTransformChangingFormats(DbgThread(), xform, TYPE_BGR_16, TYPE_RGB_16);
    if (!xform2) return 0;

    if (!CheckOneRGB(xform2, 0, 0, 123, 123, 0, 0)) return 0;
    if (!CheckOneRGB(xform2, 154, 234, 0, 0, 234, 154)) return 0;

    cmsDeleteTransform(DbgThread(),xform2);
    xform2 = cmsCloneTransformChangingFormats(DbgThread(), xform, TYPE_RGB_DBL, TYPE_RGB_DBL);
    if (!xform2) return 0;

    if (!CheckOneRGB_double(xform2, 0.20, 0, 0, 0.20, 0, 0)) return 0;
    if (!CheckOneRGB_double(xform2, 0, 0.9, 1, 0, 0.9, 1)) return 0;

    cmsDeleteTransform(DbgThread(),xform2);
    cmsDeleteTransform(DbgThread(),xform);

return 1;
}