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
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateFakeCMYK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Create_AboveRGB () ; 
 int /*<<< orphan*/ * Create_CMYK_DeviceLink () ; 
 int /*<<< orphan*/ * Create_Gray22 () ; 
 int /*<<< orphan*/ * Create_Gray30 () ; 
 int /*<<< orphan*/ * Create_GrayLab () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OneVirtual (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * cmsCreateBCHSWabstractProfile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * cmsCreateInkLimitingDeviceLink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cmsCreateLab2Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateNULLProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreateXYZProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigCmykData ; 

__attribute__((used)) static
cmsInt32Number CreateTestProfiles(void)
{
    cmsHPROFILE h;

    h = cmsCreate_sRGBProfile(DbgThread());
    if (!OneVirtual(h, "sRGB profile", "sRGBlcms2.icc")) return 0;

    // ----

    h = Create_AboveRGB();
    if (!OneVirtual(h, "aRGB profile", "aRGBlcms2.icc")) return 0;

    // ----

    h = Create_Gray22();
    if (!OneVirtual(h, "Gray profile", "graylcms2.icc")) return 0;

    // ----

    h = Create_Gray30();
    if (!OneVirtual(h, "Gray 3.0 profile", "gray3lcms2.icc")) return 0;

    // ----

    h = Create_GrayLab();
    if (!OneVirtual(h, "Gray Lab profile", "glablcms2.icc")) return 0;

    // ----

    h = Create_CMYK_DeviceLink();
    if (!OneVirtual(h, "Linearization profile", "linlcms2.icc")) return 0;

    // -------
    h = cmsCreateInkLimitingDeviceLink(DbgThread(), cmsSigCmykData, 150);
    if (h == NULL) return 0;
    if (!OneVirtual(h, "Ink-limiting profile", "limitlcms2.icc")) return 0;

    // ------

    h = cmsCreateLab2Profile(DbgThread(), NULL);
    if (!OneVirtual(h, "Lab 2 identity profile", "labv2lcms2.icc")) return 0;

    // ----

    h = cmsCreateLab4Profile(DbgThread(), NULL);
    if (!OneVirtual(h, "Lab 4 identity profile", "labv4lcms2.icc")) return 0;

    // ----

    h = cmsCreateXYZProfile(DbgThread());
    if (!OneVirtual(h, "XYZ identity profile", "xyzlcms2.icc")) return 0;

    // ----

    h = cmsCreateNULLProfile(DbgThread());
    if (!OneVirtual(h, "NULL profile", "nullcms2.icc")) return 0;

    // ---

    h = cmsCreateBCHSWabstractProfile(DbgThread(), 17, 0, 0, 0, 0, 5000, 6000);
    if (!OneVirtual(h, "BCHS profile", "bchslcms2.icc")) return 0;

    // ---

    h = CreateFakeCMYK(300, FALSE);
    if (!OneVirtual(h, "Fake CMYK profile", "lcms2cmyk.icc")) return 0;

    // ---

    h = cmsCreateBCHSWabstractProfile(DbgThread(), 17, 0, 1.2, 0, 3, 5000, 5000);
    if (!OneVirtual(h, "Brightness", "brightness.icc")) return 0;
    return 1;
}