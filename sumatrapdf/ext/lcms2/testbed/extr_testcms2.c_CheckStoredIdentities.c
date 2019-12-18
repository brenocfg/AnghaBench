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
 int CheckSeveralLab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  SubTest (char*) ; 
 int /*<<< orphan*/  TYPE_Lab_8 ; 
 int /*<<< orphan*/  TYPE_Lab_DBL ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsSaveProfileToFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsTransform2DeviceLink (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove (char*) ; 

__attribute__((used)) static
cmsInt32Number CheckStoredIdentities(void)
{
    cmsHPROFILE hLab, hLink, h4, h2;
    cmsHTRANSFORM xform;
    cmsInt32Number rc = 1;

    hLab  = cmsCreateLab4Profile(DbgThread(), NULL);
    xform = cmsCreateTransform(DbgThread(), hLab, TYPE_Lab_8, hLab, TYPE_Lab_8, 0, 0);

    hLink = cmsTransform2DeviceLink(NULL, xform, 3.4, 0);
    cmsSaveProfileToFile(DbgThread(), hLink, "abstractv2.icc");
    cmsCloseProfile(DbgThread(), hLink);

    hLink = cmsTransform2DeviceLink(NULL, xform, 4.3, 0);
    cmsSaveProfileToFile(DbgThread(), hLink, "abstractv4.icc");
    cmsCloseProfile(DbgThread(), hLink);

    cmsDeleteTransform(DbgThread(), xform);
    cmsCloseProfile(DbgThread(), hLab);

    h4 = cmsOpenProfileFromFile(DbgThread(), "abstractv4.icc", "r");

    xform = cmsCreateTransform(DbgThread(), h4, TYPE_Lab_DBL, h4, TYPE_Lab_DBL, INTENT_RELATIVE_COLORIMETRIC, 0);

    SubTest("V4");
    rc &= CheckSeveralLab(xform);

    cmsDeleteTransform(DbgThread(), xform);
    cmsCloseProfile(DbgThread(), h4);
    if (!rc) goto Error;


    SubTest("V2");
    h2 = cmsOpenProfileFromFile(DbgThread(), "abstractv2.icc", "r");

    xform = cmsCreateTransform(DbgThread(), h2, TYPE_Lab_DBL, h2, TYPE_Lab_DBL, INTENT_RELATIVE_COLORIMETRIC, 0);
    rc &= CheckSeveralLab(xform);
    cmsDeleteTransform(DbgThread(), xform);
    cmsCloseProfile(DbgThread(), h2);
    if (!rc) goto Error;


    SubTest("V2 -> V4");
    h2 = cmsOpenProfileFromFile(DbgThread(), "abstractv2.icc", "r");
    h4 = cmsOpenProfileFromFile(DbgThread(), "abstractv4.icc", "r");

    xform = cmsCreateTransform(DbgThread(), h4, TYPE_Lab_DBL, h2, TYPE_Lab_DBL, INTENT_RELATIVE_COLORIMETRIC, 0);
    rc &= CheckSeveralLab(xform);
    cmsDeleteTransform(DbgThread(), xform);
    cmsCloseProfile(DbgThread(), h2);
    cmsCloseProfile(DbgThread(), h4);

    SubTest("V4 -> V2");
    h2 = cmsOpenProfileFromFile(DbgThread(), "abstractv2.icc", "r");
    h4 = cmsOpenProfileFromFile(DbgThread(), "abstractv4.icc", "r");

    xform = cmsCreateTransform(DbgThread(), h2, TYPE_Lab_DBL, h4, TYPE_Lab_DBL, INTENT_RELATIVE_COLORIMETRIC, 0);
    rc &= CheckSeveralLab(xform);
    cmsDeleteTransform(DbgThread(), xform);
    cmsCloseProfile(DbgThread(), h2);
    cmsCloseProfile(DbgThread(), h4);

Error:
    remove("abstractv2.icc");
    remove("abstractv4.icc");
    return rc;

}