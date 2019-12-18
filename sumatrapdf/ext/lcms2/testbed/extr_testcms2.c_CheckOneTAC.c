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
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  scalar_t__ cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  CreateFakeCMYK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsDetectTAC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsSaveProfileToFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int fabs (scalar_t__) ; 
 int /*<<< orphan*/  remove (char*) ; 

__attribute__((used)) static
cmsInt32Number CheckOneTAC(cmsFloat64Number InkLimit)
{
    cmsHPROFILE h;
    cmsFloat64Number d;

    h =CreateFakeCMYK(InkLimit, TRUE);
    cmsSaveProfileToFile(DbgThread(), h, "lcmstac.icc");
    cmsCloseProfile(DbgThread(), h);

    h = cmsOpenProfileFromFile(DbgThread(), "lcmstac.icc", "r");
    d = cmsDetectTAC(DbgThread(), h);
    cmsCloseProfile(DbgThread(), h);

    remove("lcmstac.icc");

    if (fabs(d - InkLimit) > 5) return 0;

    return 1;
}