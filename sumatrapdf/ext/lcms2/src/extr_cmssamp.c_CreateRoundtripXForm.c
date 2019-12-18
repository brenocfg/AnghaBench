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
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  TYPE_Lab_DBL ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateExtendedTransform (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,double*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsFLAGS_NOCACHE ; 
 int cmsFLAGS_NOOPTIMIZE ; 

__attribute__((used)) static
cmsHTRANSFORM CreateRoundtripXForm(cmsContext ContextID, cmsHPROFILE hProfile, cmsUInt32Number nIntent)
{
    cmsHPROFILE hLab = cmsCreateLab4Profile(ContextID, NULL);
    cmsHTRANSFORM xform;
    cmsBool BPC[4] = { FALSE, FALSE, FALSE, FALSE };
    cmsFloat64Number States[4] = { 1.0, 1.0, 1.0, 1.0 };
    cmsHPROFILE hProfiles[4];
    cmsUInt32Number Intents[4];

    hProfiles[0] = hLab; hProfiles[1] = hProfile; hProfiles[2] = hProfile; hProfiles[3] = hLab;
    Intents[0]   = INTENT_RELATIVE_COLORIMETRIC; Intents[1] = nIntent; Intents[2] = INTENT_RELATIVE_COLORIMETRIC; Intents[3] = INTENT_RELATIVE_COLORIMETRIC;

    xform =  cmsCreateExtendedTransform(ContextID, 4, hProfiles, BPC, Intents,
        States, NULL, 0, TYPE_Lab_DBL, TYPE_Lab_DBL, cmsFLAGS_NOCACHE|cmsFLAGS_NOOPTIMIZE);

    cmsCloseProfile(ContextID, hLab);
    return xform;
}