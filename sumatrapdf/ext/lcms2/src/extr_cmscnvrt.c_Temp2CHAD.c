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
typedef  int /*<<< orphan*/  cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsCIExyY ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsAdaptationMatrix (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsD50_XYZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsWhitePointFromTemp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsxyY2XYZ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
    void Temp2CHAD(cmsContext ContextID, cmsMAT3* Chad, cmsFloat64Number Temp)
{
    cmsCIEXYZ White;
    cmsCIExyY ChromaticityOfWhite;

    cmsWhitePointFromTemp(ContextID, &ChromaticityOfWhite, Temp);
    cmsxyY2XYZ(ContextID,&White, &ChromaticityOfWhite);
    _cmsAdaptationMatrix(ContextID, Chad, NULL, &White, cmsD50_XYZ(ContextID));
}