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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsSetProfileVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cmsSigGrayTRCTag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove (char*) ; 

__attribute__((used)) static
cmsInt32Number CheckV4gamma(void)
{
    cmsHPROFILE h;
    cmsUInt16Number Lin[] = {0, 0xffff};
    cmsToneCurve*g = cmsBuildTabulatedToneCurve16(DbgThread(), 2, Lin);

    h = cmsOpenProfileFromFile(DbgThread(), "v4gamma.icc", "w");
    if (h == NULL) return 0;


    cmsSetProfileVersion(DbgThread(), h, 4.3);

    if (!cmsWriteTag(DbgThread(), h, cmsSigGrayTRCTag, g)) return 0;
    cmsCloseProfile(DbgThread(), h);

    cmsFreeToneCurve(DbgThread(), g);
    remove("v4gamma.icc");
    return 1;
}