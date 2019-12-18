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
typedef  int cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsCIExyY ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsTempFromWhitePoint (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsWhitePointFromTemp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int fabs (int) ; 

__attribute__((used)) static
cmsInt32Number CheckTemp2CHRM(void)
{
    cmsInt32Number j;
    cmsFloat64Number d, v, Max = 0;
    cmsCIExyY White;

    for (j=4000; j < 25000; j++) {

        cmsWhitePointFromTemp(DbgThread(), &White, j);
        if (!cmsTempFromWhitePoint(DbgThread(), &v, &White)) return 0;

        d = fabs(v - j);
        if (d > Max) Max = d;
    }

    // 100 degree is the actual resolution
    return (Max < 100);
}