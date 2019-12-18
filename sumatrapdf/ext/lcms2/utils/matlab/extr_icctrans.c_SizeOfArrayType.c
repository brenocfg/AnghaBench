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
 int /*<<< orphan*/  FatalError (char*) ; 
#define  mxDOUBLE_CLASS 133 
 int mxGetClassID (int /*<<< orphan*/  const*) ; 
#define  mxINT16_CLASS 132 
#define  mxINT8_CLASS 131 
#define  mxSINGLE_CLASS 130 
#define  mxUINT16_CLASS 129 
#define  mxUINT8_CLASS 128 

__attribute__((used)) static
size_t SizeOfArrayType(const mxArray *Array)
{

	switch (mxGetClassID(Array))  {

	 case mxINT8_CLASS:   return 1;
	 case mxUINT8_CLASS:  return 1;
	 case mxINT16_CLASS:  return 2;
	 case mxUINT16_CLASS: return 2;  
	 case mxSINGLE_CLASS: return 4;
	 case mxDOUBLE_CLASS: return 0; // Special case -- lcms handles double as size=0


	 default:
		 FatalError("Unsupported data type");
		 return 0;
	}
}