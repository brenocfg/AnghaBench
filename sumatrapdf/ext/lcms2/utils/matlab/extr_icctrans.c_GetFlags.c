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

/* Variables and functions */
 scalar_t__ BlackPointCompensation ; 
 int /*<<< orphan*/  FatalError (char*,int) ; 
 int PrecalcMode ; 
 int /*<<< orphan*/  cmsFLAGS_BLACKPOINTCOMPENSATION ; 
 int /*<<< orphan*/  cmsFLAGS_HIGHRESPRECALC ; 
 int /*<<< orphan*/  cmsFLAGS_LOWRESPRECALC ; 
 int /*<<< orphan*/  cmsFLAGS_NOOPTIMIZE ; 

__attribute__((used)) static
cmsUInt32Number GetFlags()
{
	cmsUInt32Number dwFlags = 0; 

	switch (PrecalcMode) {

	case 0: dwFlags = cmsFLAGS_NOOPTIMIZE; break;
	case 2: dwFlags = cmsFLAGS_HIGHRESPRECALC; break;
	case 3: dwFlags = cmsFLAGS_LOWRESPRECALC; break;
	case 1: break;

	default: FatalError("Unknown precalculation mode '%d'", PrecalcMode);
	}

	if (BlackPointCompensation) 
		dwFlags |= cmsFLAGS_BLACKPOINTCOMPENSATION;

	return dwFlags;
}