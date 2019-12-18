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
typedef  int /*<<< orphan*/  mxArray ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateOutputArray (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ApplyTransforms (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 void* BlackPointCompensation ; 
 int /*<<< orphan*/  CloseTransforms () ; 
 void* FALSE ; 
 int /*<<< orphan*/  FatalError (char*) ; 
 int /*<<< orphan*/  HandleSwitches (int,char**) ; 
 int /*<<< orphan*/  INTENT_ABSOLUTE_COLORIMETRIC ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  Intent ; 
 int /*<<< orphan*/  MatLabErrorHandler ; 
 int /*<<< orphan*/  OpenTransforms (int,char**) ; 
 int /*<<< orphan*/  OutputChannels ; 
 int PrecalcMode ; 
 int /*<<< orphan*/  PrintHelp () ; 
 int /*<<< orphan*/  ProofingIntent ; 
 int /*<<< orphan*/  SizeOfArrayType (int /*<<< orphan*/  const*) ; 
 scalar_t__ Verbose ; 
 int /*<<< orphan*/ * cInProf ; 
 int /*<<< orphan*/ * cOutProf ; 
 int /*<<< orphan*/ * cProofing ; 
 int /*<<< orphan*/  cmsSetLogErrorHandler (int /*<<< orphan*/ ) ; 
 void* lIsDeviceLink ; 
 void* lMultiProfileChain ; 
 scalar_t__ mxGetString (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  mxIsChar (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mxIsNumeric (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nBytesDepth ; 
 scalar_t__ nProfiles ; 
 char* strtok (char*,char*) ; 

void mexFunction(
				 int nlhs,              // Number of left hand side (output) arguments
				 mxArray *plhs[],       // Array of left hand side arguments
				 int nrhs,              // Number of right hand side (input) arguments
				 const mxArray *prhs[]  // Array of right hand side arguments
)
{

	char CommandLine[4096+1];
	char *pt, *argv[128];
	int argc = 1;


	if (nrhs != 2) {    

		PrintHelp();              
		return;
	}


	if(nlhs > 1) {        
		FatalError("Too many output arguments.");
	}


	// Setup error handler

	cmsSetLogErrorHandler(MatLabErrorHandler);

	// Defaults

	Verbose     = 0;
	cInProf     = NULL;
	cOutProf    = NULL;
	cProofing   = NULL;

	lMultiProfileChain = FALSE;
	nProfiles   = 0;

	Intent                  = INTENT_PERCEPTUAL;
	ProofingIntent          = INTENT_ABSOLUTE_COLORIMETRIC;
	PrecalcMode = 1;
	BlackPointCompensation  = FALSE;
	lIsDeviceLink           = FALSE;

	// Check types. Fist parameter is array of values, second parameter is command line

	if (!mxIsNumeric(prhs[0]))
		FatalError("Type mismatch on argument 1 -- Must be numeric");

	if (!mxIsChar(prhs[1]))
		FatalError("Type mismatch on argument 2 -- Must be string");




	// Unpack string to command line buffer

	if (mxGetString(prhs[1], CommandLine, 4096))
		FatalError("Cannot unpack command string");

	// Separate to argv[] convention

	argv[0] = NULL;
	for (pt = strtok(CommandLine, " ");
		pt;
		pt = strtok(NULL, " ")) {

			argv[argc++] = pt;
	}



	// Parse arguments
	HandleSwitches(argc, argv);


	nBytesDepth = SizeOfArrayType(prhs[0]);

	OpenTransforms(argc, argv);


	plhs[0] = AllocateOutputArray(prhs[0], OutputChannels);


	ApplyTransforms(prhs[0], plhs[0]);

	CloseTransforms();

	// Done!
}