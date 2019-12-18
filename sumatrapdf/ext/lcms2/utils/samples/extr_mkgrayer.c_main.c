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
 int /*<<< orphan*/  Forward ; 
 int /*<<< orphan*/  cmsAddTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsAlloc3DGrid (char*,int,int,int) ; 
 char* cmsAllocLUT () ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFreeLUT (char*) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (char*,char*) ; 
 int /*<<< orphan*/  cmsSample3DGrid (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  icSigBToA0Tag ; 
 int /*<<< orphan*/  icSigCopyrightTag ; 
 int /*<<< orphan*/  icSigDeviceMfgDescTag ; 
 int /*<<< orphan*/  icSigDeviceModelDescTag ; 
 int /*<<< orphan*/  icSigLabData ; 
 int /*<<< orphan*/  icSigOutputClass ; 
 int /*<<< orphan*/  icSigProfileDescriptionTag ; 
 int /*<<< orphan*/  icSigRgbData ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 

int main(int argc, char *argv[])
{
	LPLUT BToA0;
	cmsHPROFILE hProfile;

	fprintf(stderr, "Creating interpol2.icc...");

	unlink("interpol2.icc");
	hProfile = cmsOpenProfileFromFile("interpol2.icc", "w8");


    BToA0 = cmsAllocLUT();

	cmsAlloc3DGrid(BToA0, 17, 3, 3);
	    
	cmsSample3DGrid(BToA0, Forward, NULL, 0);
			
    cmsAddTag(hProfile, icSigBToA0Tag, BToA0);
	                                
	cmsSetColorSpace(hProfile, icSigRgbData);
    cmsSetPCS(hProfile, icSigLabData);
    cmsSetDeviceClass(hProfile, icSigOutputClass);

	cmsAddTag(hProfile, icSigProfileDescriptionTag, "Interpolation test");
    cmsAddTag(hProfile, icSigCopyrightTag,          "Copyright (c) HP 2007. All rights reserved.");
    cmsAddTag(hProfile, icSigDeviceMfgDescTag,      "Little cms");    
    cmsAddTag(hProfile, icSigDeviceModelDescTag,    "Interpolation test profile");

	
	cmsCloseProfile(hProfile);
    
	cmsFreeLUT(BToA0);
	
	fprintf(stderr, "Done.\n");

	return 0;
}