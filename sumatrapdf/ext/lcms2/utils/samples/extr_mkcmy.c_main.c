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
typedef  int /*<<< orphan*/  CARGO ;

/* Variables and functions */
 int /*<<< orphan*/  Forward ; 
 int /*<<< orphan*/  FreeCargo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitCargo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Reverse ; 
 int /*<<< orphan*/  _cmsSaveProfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsAddTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsAlloc3DGrid (char*,int,int,int) ; 
 char* cmsAllocLUT () ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateLabProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsFreeLUT (char*) ; 
 int /*<<< orphan*/  cmsSample3DGrid (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  icSigAToB0Tag ; 
 int /*<<< orphan*/  icSigBToA0Tag ; 
 int /*<<< orphan*/  icSigCmyData ; 
 int /*<<< orphan*/  icSigCopyrightTag ; 
 int /*<<< orphan*/  icSigDeviceMfgDescTag ; 
 int /*<<< orphan*/  icSigDeviceModelDescTag ; 
 int /*<<< orphan*/  icSigOutputClass ; 
 int /*<<< orphan*/  icSigProfileDescriptionTag ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
	LPLUT AToB0, BToA0;	
	CARGO Cargo;
	cmsHPROFILE hProfile;
	
	fprintf(stderr, "Creating lcmscmy.icm...");	
	
	InitCargo(&Cargo);

	hProfile = cmsCreateLabProfile(NULL);
	

    AToB0 = cmsAllocLUT();
	BToA0 = cmsAllocLUT();

	cmsAlloc3DGrid(AToB0, 25, 3, 3);
	cmsAlloc3DGrid(BToA0, 25, 3, 3);
	
	
	cmsSample3DGrid(AToB0, Reverse, &Cargo, 0);
	cmsSample3DGrid(BToA0, Forward, &Cargo, 0);
	
	
    cmsAddTag(hProfile, icSigAToB0Tag, AToB0);
	cmsAddTag(hProfile, icSigBToA0Tag, BToA0);

	cmsSetColorSpace(hProfile, icSigCmyData);
	cmsSetDeviceClass(hProfile, icSigOutputClass);

	cmsAddTag(hProfile, icSigProfileDescriptionTag, "CMY ");
    cmsAddTag(hProfile, icSigCopyrightTag,          "Copyright (c) HP, 2007. All rights reserved.");
    cmsAddTag(hProfile, icSigDeviceMfgDescTag,      "Little cms");    
    cmsAddTag(hProfile, icSigDeviceModelDescTag,    "CMY space");

	_cmsSaveProfile(hProfile, "lcmscmy.icm");
	
	
	cmsFreeLUT(AToB0);
	cmsFreeLUT(BToA0);
	cmsCloseProfile(hProfile);	
	FreeCargo(&Cargo);
	fprintf(stderr, "Done.\n");



	return 0;
}