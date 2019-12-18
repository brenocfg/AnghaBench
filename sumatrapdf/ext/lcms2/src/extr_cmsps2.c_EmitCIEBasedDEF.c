#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt32Number ;
struct TYPE_9__ {struct TYPE_9__* Next; } ;
typedef  TYPE_1__ cmsStage ;
struct TYPE_10__ {TYPE_1__* Elements; } ;
typedef  TYPE_2__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsColorSpaceSignature ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;

/* Variables and functions */
 int /*<<< orphan*/  EmitIntent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmitLab2XYZ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EmitNGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmitWhiteBlackD50 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  WriteCLUT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  _cmsStageGetPtrToCurveSet (TYPE_1__*) ; 
 scalar_t__ cmsSigCLutElemType ; 
 scalar_t__ cmsSigCurveSetElemType ; 
 int cmsStageInputChannels (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsStageOutputChannels (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ cmsStageType (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
int EmitCIEBasedDEF(cmsContext ContextID, cmsIOHANDLER* m, cmsPipeline* Pipeline, cmsUInt32Number Intent, cmsCIEXYZ* BlackPoint)
{
    const char* PreMaj;
    const char* PostMaj;
    const char* PreMin, *PostMin;
    cmsStage* mpe;

    mpe = Pipeline ->Elements;

    switch (cmsStageInputChannels(ContextID, mpe)) {
    case 3:

            _cmsIOPrintf(ContextID, m, "[ /CIEBasedDEF\n");
            PreMaj ="<";
            PostMaj= ">\n";
            PreMin = PostMin = "";
            break;
    case 4:
            _cmsIOPrintf(ContextID, m, "[ /CIEBasedDEFG\n");
            PreMaj = "[";
            PostMaj = "]\n";
            PreMin = "<";
            PostMin = ">\n";
            break;
    default:
            return 0;

    }

    _cmsIOPrintf(ContextID, m, "<<\n");

    if (cmsStageType(ContextID, mpe) == cmsSigCurveSetElemType) {

        _cmsIOPrintf(ContextID, m, "/DecodeDEF [ ");
        EmitNGamma(ContextID, m, cmsStageOutputChannels(ContextID, mpe), _cmsStageGetPtrToCurveSet(mpe));
        _cmsIOPrintf(ContextID, m, "]\n");

        mpe = mpe ->Next;
    }

    if (cmsStageType(ContextID, mpe) == cmsSigCLutElemType) {

            _cmsIOPrintf(ContextID, m, "/Table ");
            WriteCLUT(ContextID, m, mpe, PreMaj, PostMaj, PreMin, PostMin, FALSE, (cmsColorSpaceSignature) 0);
            _cmsIOPrintf(ContextID, m, "]\n");
    }

    EmitLab2XYZ(ContextID, m);
    EmitWhiteBlackD50(ContextID, m, BlackPoint);
    EmitIntent(ContextID, m, Intent);

    _cmsIOPrintf(ContextID, m, "   >>\n");
    _cmsIOPrintf(ContextID, m, "]\n");

    return 1;
}