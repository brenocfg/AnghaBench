#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_8__ {double X; double Y; double Z; } ;
typedef  TYPE_1__ cmsCIEXYZ ;
struct TYPE_9__ {int L; int a; int b; } ;
typedef  TYPE_2__ cmsCIELab ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateRoundtripXForm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  LCMS_USED_AS_INPUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  cmsIsIntentSupported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsLab2XYZ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static
cmsBool BlackPointUsingPerceptualBlack(cmsContext ContextID, cmsCIEXYZ* BlackPoint, cmsHPROFILE hProfile)
{
    cmsHTRANSFORM hRoundTrip;
    cmsCIELab LabIn, LabOut;
    cmsCIEXYZ  BlackXYZ;

     // Is the intent supported by the profile?
    if (!cmsIsIntentSupported(ContextID, hProfile, INTENT_PERCEPTUAL, LCMS_USED_AS_INPUT)) {

        BlackPoint -> X = BlackPoint ->Y = BlackPoint -> Z = 0.0;
        return TRUE;
    }

    hRoundTrip = CreateRoundtripXForm(ContextID, hProfile, INTENT_PERCEPTUAL);
    if (hRoundTrip == NULL) {
        BlackPoint -> X = BlackPoint ->Y = BlackPoint -> Z = 0.0;
        return FALSE;
    }

    LabIn.L = LabIn.a = LabIn.b = 0;
    cmsDoTransform(ContextID, hRoundTrip, &LabIn, &LabOut, 1);

    // Clip Lab to reasonable limits
    if (LabOut.L > 50) LabOut.L = 50;
    LabOut.a = LabOut.b = 0;

    cmsDeleteTransform(ContextID, hRoundTrip);

    // Convert it to XYZ
    cmsLab2XYZ(ContextID, NULL, &BlackXYZ, &LabOut);

    if (BlackPoint != NULL)
        *BlackPoint = BlackXYZ;

    return TRUE;
}