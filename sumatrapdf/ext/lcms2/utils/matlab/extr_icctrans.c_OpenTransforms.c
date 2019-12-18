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

/* Variables and functions */
 int /*<<< orphan*/  FatalError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFlags () ; 
 void* InputChannels ; 
 int /*<<< orphan*/  InputColorSpace ; 
 int /*<<< orphan*/  Intent ; 
 int /*<<< orphan*/  MakeFormatDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* OpenProfile (char*) ; 
 void* OutputChannels ; 
 int /*<<< orphan*/  OutputColorSpace ; 
 int /*<<< orphan*/  ProofingIntent ; 
 int /*<<< orphan*/  SW ; 
 scalar_t__ TRUE ; 
 char* cInProf ; 
 char* cOutProf ; 
 char* cProofing ; 
 void* cmsChannelsOf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateMultiprofileTransform (void**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateProofingTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFLAGS_SOFTPROOFING ; 
 int /*<<< orphan*/  cmsGetColorSpace (int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsGetPCS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (char*,char*) ; 
 scalar_t__ cmsSigLinkClass ; 
 int /*<<< orphan*/ * cmsTransform2DeviceLink (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hColorTransform ; 
 int /*<<< orphan*/ * hInput ; 
 int /*<<< orphan*/ * hOutput ; 
 void** hProfiles ; 
 void* hProof ; 
 scalar_t__ lIsDeviceLink ; 
 scalar_t__ lMultiProfileChain ; 
 int /*<<< orphan*/  nBytesDepth ; 
 int nProfiles ; 
 int xoptind ; 

__attribute__((used)) static
void OpenTransforms(int argc, char *argv[])
{

	cmsUInt32Number dwIn, dwOut, dwFlags;


	if (lMultiProfileChain) {

		int i;
		cmsHTRANSFORM hTmp;


		nProfiles = argc - xoptind;
		for (i=0; i < nProfiles; i++) {

			hProfiles[i] = OpenProfile(argv[i+xoptind]);
		}


		// Create a temporary devicelink 

		hTmp = cmsCreateMultiprofileTransform(hProfiles, nProfiles, 
			0, 0, Intent, GetFlags());

		hInput = cmsTransform2DeviceLink(hTmp, 4.2, 0);
		hOutput = NULL;
		cmsDeleteTransform(hTmp);

		InputColorSpace  = cmsGetColorSpace(hInput);
		OutputColorSpace = cmsGetPCS(hInput);        
		lIsDeviceLink = TRUE;

	}
	else
		if (lIsDeviceLink) {

			hInput  = cmsOpenProfileFromFile(cInProf, "r");
			hOutput = NULL;
			InputColorSpace  = cmsGetColorSpace(hInput);
			OutputColorSpace = cmsGetPCS(hInput);


		}
		else {

			hInput  = OpenProfile(cInProf);
			hOutput = OpenProfile(cOutProf);    

			InputColorSpace   = cmsGetColorSpace(hInput);
			OutputColorSpace  = cmsGetColorSpace(hOutput);

			if (cmsGetDeviceClass(hInput) == cmsSigLinkClass ||
				cmsGetDeviceClass(hOutput) == cmsSigLinkClass)   
				FatalError("Use %cl flag for devicelink profiles!\n", SW);

		}


		/*

		if (Verbose) {

		mexPrintf("From: %s\n", cmsTakeProductName(hInput));
		if (hOutput) mexPrintf("To  : %s\n\n", cmsTakeProductName(hOutput));

		}
		*/


		OutputChannels = cmsChannelsOf(OutputColorSpace);
		InputChannels  = cmsChannelsOf(InputColorSpace);


		dwIn  = MakeFormatDescriptor(InputColorSpace, nBytesDepth);
		dwOut = MakeFormatDescriptor(OutputColorSpace, nBytesDepth);


		dwFlags = GetFlags();

		if (cProofing != NULL) {

			hProof = OpenProfile(cProofing);
			dwFlags |= cmsFLAGS_SOFTPROOFING;
		}




		hColorTransform = cmsCreateProofingTransform(hInput, dwIn, 
			hOutput, dwOut, 
			hProof, Intent, 
			ProofingIntent, 
			dwFlags);

}