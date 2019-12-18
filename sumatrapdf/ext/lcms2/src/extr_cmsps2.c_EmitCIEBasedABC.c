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
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;

/* Variables and functions */
 int /*<<< orphan*/  EmitIntent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmitNGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  EmitWhiteBlackD50 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static
int EmitCIEBasedABC(cmsContext ContextID, cmsIOHANDLER* m, cmsFloat64Number* Matrix, cmsToneCurve** CurveSet, cmsCIEXYZ* BlackPoint)
{
    int i;

    _cmsIOPrintf(ContextID, m, "[ /CIEBasedABC\n");
    _cmsIOPrintf(ContextID, m, "<<\n");
    _cmsIOPrintf(ContextID, m, "/DecodeABC [ ");

    EmitNGamma(ContextID, m, 3, CurveSet);

    _cmsIOPrintf(ContextID, m, "]\n");

    _cmsIOPrintf(ContextID, m, "/MatrixABC [ " );

    for( i=0; i < 3; i++ ) {

        _cmsIOPrintf(ContextID, m, "%.6f %.6f %.6f ", Matrix[i + 3*0],
                                           Matrix[i + 3*1],
                                           Matrix[i + 3*2]);
    }


    _cmsIOPrintf(ContextID, m, "]\n");

    _cmsIOPrintf(ContextID, m, "/RangeLMN [ 0.0 0.9642 0.0 1.0000 0.0 0.8249 ]\n");

    EmitWhiteBlackD50(ContextID, m, BlackPoint);
    EmitIntent(ContextID, m, INTENT_PERCEPTUAL);

    _cmsIOPrintf(ContextID, m, ">>\n");
    _cmsIOPrintf(ContextID, m, "]\n");


    return 1;
}