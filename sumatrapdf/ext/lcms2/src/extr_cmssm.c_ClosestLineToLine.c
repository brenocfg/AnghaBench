#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsVEC3 ;
struct TYPE_5__ {int /*<<< orphan*/  u; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ cmsLine ;
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  GetPointOfLine (int /*<<< orphan*/ *,TYPE_1__ const*,double) ; 
 double MATRIX_DET_TOLERANCE ; 
 int /*<<< orphan*/  TRUE ; 
 double _cmsVEC3dot (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsVEC3minus (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double fabs (double) ; 

__attribute__((used)) static
cmsBool ClosestLineToLine(cmsContext ContextID, cmsVEC3* r, const cmsLine* line1, const cmsLine* line2)
{
    cmsFloat64Number a, b, c, d, e, D;
    cmsFloat64Number sc, sN, sD;
    //cmsFloat64Number tc; // left for future use
    cmsFloat64Number tN, tD;
    cmsVEC3 w0;

    _cmsVEC3minus(ContextID, &w0, &line1 ->a, &line2 ->a);

    a  = _cmsVEC3dot(ContextID, &line1 ->u, &line1 ->u);
    b  = _cmsVEC3dot(ContextID, &line1 ->u, &line2 ->u);
    c  = _cmsVEC3dot(ContextID, &line2 ->u, &line2 ->u);
    d  = _cmsVEC3dot(ContextID, &line1 ->u, &w0);
    e  = _cmsVEC3dot(ContextID, &line2 ->u, &w0);

    D  = a*c - b * b;      // Denominator
    sD = tD = D;           // default sD = D >= 0

    if (D <  MATRIX_DET_TOLERANCE) {   // the lines are almost parallel

        sN = 0.0;        // force using point P0 on segment S1
        sD = 1.0;        // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    }
    else {                // get the closest points on the infinite lines

        sN = (b*e - c*d);
        tN = (a*e - b*d);

        if (sN < 0.0) {       // sc < 0 => the s=0 edge is visible

            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD) {   // sc > 1 => the s=1 edge is visible
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if (tN < 0.0) {           // tc < 0 => the t=0 edge is visible

        tN = 0.0;
        // recompute sc for this edge
        if (-d < 0.0)
            sN = 0.0;
        else if (-d > a)
            sN = sD;
        else {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD) {      // tc > 1 => the t=1 edge is visible

        tN = tD;

        // recompute sc for this edge
        if ((-d + b) < 0.0)
            sN = 0;
        else if ((-d + b) > a)
            sN = sD;
        else {
            sN = (-d + b);
            sD = a;
        }
    }
    // finally do the division to get sc and tc
    sc = (fabs(sN) < MATRIX_DET_TOLERANCE ? 0.0 : sN / sD);
    //tc = (fabs(tN) < MATRIX_DET_TOLERANCE ? 0.0 : tN / tD); // left for future use.

    GetPointOfLine(r, line1, sc);
    return TRUE;
}