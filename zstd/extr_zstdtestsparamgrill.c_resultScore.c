#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cMem; scalar_t__ dSpeed; scalar_t__ cSpeed; } ;
typedef  TYPE_1__ constraint_t ;
typedef  scalar_t__ U32 ;
struct TYPE_6__ {double cSpeed; double dSpeed; double cMem; double cSize; } ;
typedef  TYPE_2__ BMK_benchResult_t ;

/* Variables and functions */
 double const MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double const MIN (int,double) ; 
 int /*<<< orphan*/  log (double) ; 

__attribute__((used)) static double
resultScore(const BMK_benchResult_t res, const size_t srcSize, const constraint_t target)
{
    double cs = 0., ds = 0., rt, cm = 0.;
    const double r1 = 1, r2 = 0.1, rtr = 0.5;
    double ret;
    if(target.cSpeed) { cs = res.cSpeed / (double)target.cSpeed; }
    if(target.dSpeed) { ds = res.dSpeed / (double)target.dSpeed; }
    if(target.cMem != (U32)-1) { cm = (double)target.cMem / res.cMem; }
    rt = ((double)srcSize / res.cSize);

    ret = (MIN(1, cs) + MIN(1, ds)  + MIN(1, cm))*r1 + rt * rtr +
         (MAX(0, log(cs))+ MAX(0, log(ds))+ MAX(0, log(cm))) * r2;

    return ret;
}