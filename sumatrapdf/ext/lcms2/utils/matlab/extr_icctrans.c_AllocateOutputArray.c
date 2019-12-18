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
 int /*<<< orphan*/  memmove (int*,int const*,int) ; 
#define  mxDOUBLE_CLASS 132 
 int /*<<< orphan*/ * mxDuplicateArray (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mxFree (int*) ; 
 int mxGetClassID (int /*<<< orphan*/  const*) ; 
 int* mxGetDimensions (int /*<<< orphan*/  const*) ; 
 int mxGetNumberOfDimensions (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mxGetPr (int /*<<< orphan*/ *) ; 
#define  mxINT16_CLASS 131 
#define  mxINT8_CLASS 130 
 scalar_t__ mxMalloc (int) ; 
 int /*<<< orphan*/  mxRealloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxSetDimensions (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  mxSetPr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  mxUINT16_CLASS 129 
#define  mxUINT8_CLASS 128 

__attribute__((used)) static
mxArray* AllocateOutputArray(const mxArray* In, int OutputChannels)
{       

	mxArray*	Out			  = mxDuplicateArray(In);   // Make a "deep copy" of Input array 
	int         nDimensions   = mxGetNumberOfDimensions(In);    
	const int*	Dimensions    = mxGetDimensions(In);
	int         InputChannels = Dimensions[nDimensions-1];


	// Modify pixel size only if needed

	if (InputChannels != OutputChannels) {


		int i, NewSize;
		int *ModifiedDimensions = (int*) mxMalloc(nDimensions * sizeof(int));


		memmove(ModifiedDimensions, Dimensions, nDimensions * sizeof(int));
		ModifiedDimensions[nDimensions - 1] = OutputChannels;

		switch (mxGetClassID(In))  {

		case mxINT8_CLASS:   NewSize = sizeof(char); break;
		case mxUINT8_CLASS:  NewSize = sizeof(unsigned char); break;
		case mxINT16_CLASS:  NewSize = sizeof(short); break;
		case mxUINT16_CLASS: NewSize = sizeof(unsigned short); break;

		default:
		case mxDOUBLE_CLASS: NewSize = sizeof(double); break;
		}


		// NewSize = 1;
		for (i=0; i < nDimensions; i++)
			NewSize *= ModifiedDimensions[i];


		mxSetDimensions(Out, ModifiedDimensions, nDimensions);
		mxFree(ModifiedDimensions);

		mxSetPr(Out, mxRealloc(mxGetPr(Out), NewSize));             

	}


	return Out;
}