#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nSegments; TYPE_1__* Segments; } ;
typedef  TYPE_2__ cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsTagTypeSignature ;
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int Type; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmsSigCurveType ; 
 int /*<<< orphan*/  cmsSigParametricCurveType ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsTagTypeSignature DecideCurveType(cmsContext ContextID, cmsFloat64Number ICCVersion, const void *Data)
{
    cmsToneCurve* Curve = (cmsToneCurve*) Data;
    cmsUNUSED_PARAMETER(ContextID);

    if (ICCVersion < 4.0) return cmsSigCurveType;
    if (Curve ->nSegments != 1) return cmsSigCurveType;          // Only 1-segment curves can be saved as parametric
    if (Curve ->Segments[0].Type < 0) return cmsSigCurveType;    // Only non-inverted curves
    if (Curve ->Segments[0].Type > 5) return cmsSigCurveType;    // Only ICC parametric curves

    return cmsSigParametricCurveType;
}