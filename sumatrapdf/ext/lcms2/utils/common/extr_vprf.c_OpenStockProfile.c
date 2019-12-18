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
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsCIExyY ;

/* Variables and functions */
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsCreateGrayProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateLab2Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateLinearizationDeviceLink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cmsCreateNULLProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateXYZProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsD50_xyY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  cmsSigCmykData ; 
 int /*<<< orphan*/  cmsWhitePointFromTemp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cmsstrcasecmp (char const*,char*) ; 

cmsHPROFILE OpenStockProfile(cmsContext ContextID, const char* File)
{
       if (!File)
            return cmsCreate_sRGBProfile(ContextID);

       if (cmsstrcasecmp(File, "*Lab2") == 0)
                return cmsCreateLab2Profile(ContextID, NULL);

       if (cmsstrcasecmp(File, "*Lab4") == 0)
                return cmsCreateLab4Profile(ContextID, NULL);

       if (cmsstrcasecmp(File, "*Lab") == 0)
                return cmsCreateLab4Profile(ContextID, NULL);

       if (cmsstrcasecmp(File, "*LabD65") == 0) {

           cmsCIExyY D65xyY;

           cmsWhitePointFromTemp(ContextID,  &D65xyY, 6504);
           return cmsCreateLab4Profile(ContextID, &D65xyY);
       }

       if (cmsstrcasecmp(File, "*XYZ") == 0)
                return cmsCreateXYZProfile(ContextID);

       if (cmsstrcasecmp(File, "*Gray22") == 0) {

           cmsToneCurve* Curve = cmsBuildGamma(ContextID, 2.2);
           cmsHPROFILE hProfile = cmsCreateGrayProfile(ContextID, cmsD50_xyY(ContextID), Curve);
           cmsFreeToneCurve(ContextID, Curve);
           return hProfile;
       }

        if (cmsstrcasecmp(File, "*Gray30") == 0) {

           cmsToneCurve* Curve = cmsBuildGamma(ContextID, 3.0);
           cmsHPROFILE hProfile = cmsCreateGrayProfile(ContextID, cmsD50_xyY(ContextID), Curve);
           cmsFreeToneCurve(ContextID, Curve);
           return hProfile;
       }

       if (cmsstrcasecmp(File, "*srgb") == 0)
                return cmsCreate_sRGBProfile(ContextID);

       if (cmsstrcasecmp(File, "*null") == 0)
                return cmsCreateNULLProfile(ContextID);


       if (cmsstrcasecmp(File, "*Lin2222") == 0) {

            cmsToneCurve*  Gamma = cmsBuildGamma(0, 2.2);
            cmsToneCurve*  Gamma4[4];
            cmsHPROFILE hProfile;

            Gamma4[0] = Gamma4[1] = Gamma4[2] = Gamma4[3] = Gamma;
            hProfile = cmsCreateLinearizationDeviceLink(ContextID, cmsSigCmykData, Gamma4);
            cmsFreeToneCurve(ContextID, Gamma);
            return hProfile;
       }


        return cmsOpenProfileFromFile(ContextID, File, "r");
}