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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 scalar_t__ IsGoodVal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
cmsInt32Number CheckOneRGB_double(cmsHTRANSFORM xform, cmsFloat64Number R, cmsFloat64Number G, cmsFloat64Number B, cmsFloat64Number Ro, cmsFloat64Number Go, cmsFloat64Number Bo)
{
    cmsFloat64Number RGB[3];
    cmsFloat64Number Out[3];

    RGB[0] = R;
    RGB[1] = G;
    RGB[2] = B;

    cmsDoTransform(DbgThread(), xform, RGB, Out, 1);

    return IsGoodVal("R", Ro , Out[0], 0.01) &&
           IsGoodVal("G", Go , Out[1], 0.01) &&
           IsGoodVal("B", Bo , Out[2], 0.01);
}