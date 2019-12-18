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
typedef  scalar_t__ cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
struct TYPE_3__ {double L; scalar_t__ b; scalar_t__ a; } ;
typedef  TYPE_1__ cmsCIELab ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  IsGoodVal (char*,scalar_t__,double,double) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*,int) ; 

__attribute__((used)) static
cmsInt32Number CheckOutGray(cmsHTRANSFORM xform, double L, cmsUInt8Number g)
{
    cmsCIELab Lab;
    cmsUInt8Number g_out;

    Lab.L = L;
    Lab.a = 0;
    Lab.b = 0;

    cmsDoTransform(DbgThread(), xform, &Lab, &g_out, 1);

    return IsGoodVal("Gray value", g, (double) g_out, 0.01);
}