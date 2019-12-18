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
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  TYPE_BGR_8 ; 
 int /*<<< orphan*/  TYPE_CMYK_8 ; 
 int /*<<< orphan*/  TYPE_Lab_8 ; 
 int /*<<< orphan*/  TYPE_RGB_8 ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static
cmsInt32Number CheckBadTransforms(void)
{
    cmsHPROFILE h1 = cmsCreate_sRGBProfile(DbgThread());
    cmsHTRANSFORM x1;

    x1 = cmsCreateTransform(DbgThread(), NULL, 0, NULL, 0, 0, 0);
    if (x1 != NULL) {
        cmsDeleteTransform(DbgThread(), x1);
        return 0;
    }



    x1 = cmsCreateTransform(DbgThread(), h1, TYPE_RGB_8, h1, TYPE_RGB_8, 12345, 0);
    if (x1 != NULL) {
        cmsDeleteTransform(DbgThread(), x1);
        return 0;
    }

    x1 = cmsCreateTransform(DbgThread(), h1, TYPE_CMYK_8, h1, TYPE_RGB_8, 0, 0);
    if (x1 != NULL) {
        cmsDeleteTransform(DbgThread(), x1);
        return 0;
    }

    x1 = cmsCreateTransform(DbgThread(), h1, TYPE_RGB_8, h1, TYPE_CMYK_8, 1, 0);
    if (x1 != NULL) {
        cmsDeleteTransform(DbgThread(), x1);
        return 0;
    }

    // sRGB does its output as XYZ!
    x1 = cmsCreateTransform(DbgThread(), h1, TYPE_RGB_8, NULL, TYPE_Lab_8, 1, 0);
    if (x1 != NULL) {
        cmsDeleteTransform(DbgThread(), x1);
        return 0;
    }

    cmsCloseProfile(DbgThread(), h1);


    {

    cmsHPROFILE hp1 = cmsOpenProfileFromFile(DbgThread(),  "test1.icc", "r");
    cmsHPROFILE hp2 = cmsCreate_sRGBProfile(DbgThread());

    x1 = cmsCreateTransform(DbgThread(), hp1, TYPE_BGR_8, hp2, TYPE_BGR_8, INTENT_PERCEPTUAL, 0);

    cmsCloseProfile(DbgThread(), hp1); cmsCloseProfile(DbgThread(), hp2);
    if (x1 != NULL) {
        cmsDeleteTransform(DbgThread(), x1);
        return 0;
    }
    }

    return 1;

}