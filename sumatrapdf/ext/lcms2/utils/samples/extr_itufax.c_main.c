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
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  char* LPLUT ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_POINTS ; 
 int /*<<< orphan*/  InputDirection ; 
 int /*<<< orphan*/  OutputDirection ; 
 int /*<<< orphan*/  cmsAddTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsAlloc3DGrid (char*,int /*<<< orphan*/ ,int,int) ; 
 char* cmsAllocLUT () ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFreeLUT (char*) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (char*,char*) ; 
 int /*<<< orphan*/  cmsSample3DGrid (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  icSigAToB0Tag ; 
 int /*<<< orphan*/  icSigBToA0Tag ; 
 int /*<<< orphan*/  icSigColorSpaceClass ; 
 int /*<<< orphan*/  icSigCopyrightTag ; 
 int /*<<< orphan*/  icSigDeviceMfgDescTag ; 
 int /*<<< orphan*/  icSigDeviceModelDescTag ; 
 int /*<<< orphan*/  icSigLabData ; 
 int /*<<< orphan*/  icSigProfileDescriptionTag ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 

int main(int argc, char *argv[])
{
	LPLUT AToB0, BToA0;
	cmsHPROFILE hProfile;

	fprintf(stderr, "Creating itufax.icm...");

	unlink("itufax.icm");
	hProfile = cmsOpenProfileFromFile("itufax.icm", "w");
	
    AToB0 = cmsAllocLUT();
	BToA0 = cmsAllocLUT(); 

	cmsAlloc3DGrid(AToB0, GRID_POINTS, 3, 3);
	cmsAlloc3DGrid(BToA0, GRID_POINTS, 3, 3);
    
	cmsSample3DGrid(AToB0, InputDirection, NULL, 0);
	cmsSample3DGrid(BToA0, OutputDirection, NULL, 0);
		
    cmsAddTag(hProfile, icSigAToB0Tag, AToB0);
	cmsAddTag(hProfile, icSigBToA0Tag, BToA0);

                                
	cmsSetColorSpace(hProfile, icSigLabData);
    cmsSetPCS(hProfile, icSigLabData);
    cmsSetDeviceClass(hProfile, icSigColorSpaceClass);

	cmsAddTag(hProfile, icSigProfileDescriptionTag, "ITU T.42/Fax JPEG CIEL*a*b*");
    cmsAddTag(hProfile, icSigCopyrightTag,          "No Copyright, use freely.");
    cmsAddTag(hProfile, icSigDeviceMfgDescTag,      "Little cms");    
    cmsAddTag(hProfile, icSigDeviceModelDescTag,    "ITU T.42/Fax JPEG CIEL*a*b*");
	
	cmsCloseProfile(hProfile);
    
	cmsFreeLUT(AToB0);
	cmsFreeLUT(BToA0);

	fprintf(stderr, "Done.\n");

	return 0;
}