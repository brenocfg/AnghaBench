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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
struct TYPE_3__ {int /*<<< orphan*/  L; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ cmsCIELab ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  IsGoodVal (char*,double,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static
cmsInt32Number CheckGray(cmsHTRANSFORM xform, cmsUInt8Number g, double L)
{
    cmsCIELab Lab;

    cmsDoTransform(DbgThread(), xform, &g, &Lab, 1);

    if (!IsGoodVal("a axis on gray", 0, Lab.a, 0.001)) return 0;
    if (!IsGoodVal("b axis on gray", 0, Lab.b, 0.001)) return 0;

    return IsGoodVal("Gray value", L, Lab.L, 0.01);
}