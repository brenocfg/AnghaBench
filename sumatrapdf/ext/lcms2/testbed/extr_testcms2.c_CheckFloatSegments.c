#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int cmsInt32Number ;
typedef  int cmsFloat32Number ;
struct TYPE_3__ {float x0; float x1; int Type; float* Params; int nGridPoints; int* SampledPoints; } ;
typedef  TYPE_1__ cmsCurveSegment ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int StraightLine (int) ; 
 int TestCurve (char*,int /*<<< orphan*/ *,int (*) (int)) ; 
 int /*<<< orphan*/ * cmsBuildSegmentedToneCurve (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kNumPoints ; 

__attribute__((used)) static
cmsInt32Number CheckFloatSegments(void)
{
    cmsInt32Number ok = 1;
    int i;
    cmsToneCurve *curve;

    cmsFloat32Number y[ kNumPoints];

    // build a segmented curve with a sampled section...
    cmsCurveSegment Seg[3];

    // Initialize segmented curve part up to 0.1
    Seg[0].x0 = -1e22f;      // -infinity
    Seg[0].x1 = 0.1f;
    Seg[0].Type = 6;             // Y = (a * X + b) ^ Gamma + c
    Seg[0].Params[0] = 1.0f;     // gamma
    Seg[0].Params[1] = 0.9f;     // a
    Seg[0].Params[2] = 0.0f;        // b
    Seg[0].Params[3] = 0.1f;     // c
    Seg[0].Params[4] = 0.0f;

    // From zero to 1
    Seg[1].x0 = 0.1f;
    Seg[1].x1 = 0.9f;
    Seg[1].Type = 0;

    Seg[1].nGridPoints = kNumPoints;
    Seg[1].SampledPoints = y;

    for (i = 0; i < kNumPoints; i++) {
        cmsFloat32Number x = (cmsFloat32Number) (0.1 + ((cmsFloat32Number)i / (kNumPoints-1)) * (0.9 - 0.1));
        y[i] = StraightLine(x);
    }

    // from 1 to +infinity
    Seg[2].x0 = 0.9f;
    Seg[2].x1 = 1e22f;   // +infinity
    Seg[2].Type = 6;

    Seg[2].Params[0] = 1.0f;
    Seg[2].Params[1] = 0.9f;
    Seg[2].Params[2] = 0.0f;
    Seg[2].Params[3] = 0.1f;
    Seg[2].Params[4] = 0.0f;

    curve = cmsBuildSegmentedToneCurve(0, 3, Seg);

    ok = TestCurve( "Float Segmented Curve", curve, StraightLine);

    cmsFreeToneCurve(DbgThread(), curve);

    return ok;
}