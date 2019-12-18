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
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int cmsBool ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int _MultiplyMatrix (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _Remove1Op (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int _Remove2Op (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigFloatPCS2Lab ; 
 int /*<<< orphan*/  cmsSigFloatPCS2XYZ ; 
 int /*<<< orphan*/  cmsSigIdentityElemType ; 
 int /*<<< orphan*/  cmsSigLab2FloatPCS ; 
 int /*<<< orphan*/  cmsSigLab2XYZElemType ; 
 int /*<<< orphan*/  cmsSigLabV2toV4 ; 
 int /*<<< orphan*/  cmsSigLabV4toV2 ; 
 int /*<<< orphan*/  cmsSigXYZ2FloatPCS ; 
 int /*<<< orphan*/  cmsSigXYZ2LabElemType ; 

__attribute__((used)) static
cmsBool PreOptimize(cmsContext ContextID, cmsPipeline* Lut)
{
    cmsBool AnyOpt = FALSE, Opt;

    do {

        Opt = FALSE;

        // Remove all identities
        Opt |= _Remove1Op(ContextID, Lut, cmsSigIdentityElemType);

        // Remove XYZ2Lab followed by Lab2XYZ
        Opt |= _Remove2Op(ContextID, Lut, cmsSigXYZ2LabElemType, cmsSigLab2XYZElemType);

        // Remove Lab2XYZ followed by XYZ2Lab
        Opt |= _Remove2Op(ContextID, Lut, cmsSigLab2XYZElemType, cmsSigXYZ2LabElemType);

        // Remove V4 to V2 followed by V2 to V4
        Opt |= _Remove2Op(ContextID, Lut, cmsSigLabV4toV2, cmsSigLabV2toV4);

        // Remove V2 to V4 followed by V4 to V2
        Opt |= _Remove2Op(ContextID, Lut, cmsSigLabV2toV4, cmsSigLabV4toV2);

        // Remove float pcs Lab conversions
        Opt |= _Remove2Op(ContextID, Lut, cmsSigLab2FloatPCS, cmsSigFloatPCS2Lab);

        // Remove float pcs Lab conversions
        Opt |= _Remove2Op(ContextID, Lut, cmsSigXYZ2FloatPCS, cmsSigFloatPCS2XYZ);

        // Simplify matrix.
        Opt |= _MultiplyMatrix(ContextID, Lut);

        if (Opt) AnyOpt = TRUE;

    } while (Opt);

    return AnyOpt;
}