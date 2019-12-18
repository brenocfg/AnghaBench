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
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;

/* Variables and functions */
 int /*<<< orphan*/  Emit1Gamma (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EmitIntent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmitWhiteBlackD50 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static
int EmitCIEBasedA(cmsContext ContextID, cmsIOHANDLER* m, cmsToneCurve* Curve, cmsCIEXYZ* BlackPoint)
{

    _cmsIOPrintf(ContextID, m, "[ /CIEBasedA\n");
    _cmsIOPrintf(ContextID, m, "  <<\n");

    _cmsIOPrintf(ContextID, m, "/DecodeA ");

    Emit1Gamma(ContextID, m, Curve);

    _cmsIOPrintf(ContextID, m, " \n");

    _cmsIOPrintf(ContextID, m, "/MatrixA [ 0.9642 1.0000 0.8249 ]\n");
    _cmsIOPrintf(ContextID, m, "/RangeLMN [ 0.0 0.9642 0.0 1.0000 0.0 0.8249 ]\n");

    EmitWhiteBlackD50(ContextID, m, BlackPoint);
    EmitIntent(ContextID, m, INTENT_PERCEPTUAL);

    _cmsIOPrintf(ContextID, m, ">>\n");
    _cmsIOPrintf(ContextID, m, "]\n");

    return 1;
}