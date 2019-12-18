#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* Segments; scalar_t__* Table16; } ;
typedef  TYPE_2__ cmsToneCurve ;
typedef  int cmsInt32Number ;
struct TYPE_11__ {scalar_t__ Type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 TYPE_2__* cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int cmsIsToneCurveLinear (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* cmsJoinToneCurve (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_2__* cmsReverseToneCurve (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static
cmsInt32Number CheckJointCurvesDescending(void)
{
    cmsToneCurve *Forward, *Reverse, *Result;
    cmsInt32Number i, rc;

     Forward = cmsBuildGamma(DbgThread(), 2.2);

    // Fake the curve to be table-based

    for (i=0; i < 4096; i++)
        Forward ->Table16[i] = 0xffff - Forward->Table16[i];
    Forward ->Segments[0].Type = 0;

    Reverse = cmsReverseToneCurve(DbgThread(), Forward);

    Result = cmsJoinToneCurve(DbgThread(), Reverse, Reverse, 256);

    cmsFreeToneCurve(DbgThread(), Forward);
    cmsFreeToneCurve(DbgThread(), Reverse);

    rc = cmsIsToneCurveLinear(DbgThread(), Result);
    cmsFreeToneCurve(DbgThread(), Result);

    return rc;
}