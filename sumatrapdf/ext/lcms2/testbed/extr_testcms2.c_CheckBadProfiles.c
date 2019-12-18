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
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int SimultaneousErrors ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromMem (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static
cmsInt32Number CheckBadProfiles(void)
{
    cmsHPROFILE h;

    h = cmsOpenProfileFromFile(DbgThread(), "IDoNotExist.icc", "r");
    if (h != NULL) {
        cmsCloseProfile(DbgThread(), h);
        return 0;
    }

    h = cmsOpenProfileFromFile(DbgThread(), "IAmIllFormed*.icc", "r");
    if (h != NULL) {
        cmsCloseProfile(DbgThread(), h);
        return 0;
    }

    // No profile name given
    h = cmsOpenProfileFromFile(DbgThread(), "", "r");
    if (h != NULL) {
        cmsCloseProfile(DbgThread(), h);
        return 0;
    }

    h = cmsOpenProfileFromFile(DbgThread(), "..", "r");
    if (h != NULL) {
        cmsCloseProfile(DbgThread(), h);
        return 0;
    }

    h = cmsOpenProfileFromFile(DbgThread(), "IHaveBadAccessMode.icc", "@");
    if (h != NULL) {
        cmsCloseProfile(DbgThread(), h);
        return 0;
    }

    h = cmsOpenProfileFromFile(DbgThread(), "bad.icc", "r");
    if (h != NULL) {
        cmsCloseProfile(DbgThread(), h);
        return 0;
    }

     h = cmsOpenProfileFromFile(DbgThread(), "toosmall.icc", "r");
    if (h != NULL) {
        cmsCloseProfile(DbgThread(), h);
        return 0;
    }

    h = cmsOpenProfileFromMem(DbgThread(), NULL, 3);
    if (h != NULL) {
        cmsCloseProfile(DbgThread(), h);
        return 0;
    }

    h = cmsOpenProfileFromMem(DbgThread(), "123", 3);
    if (h != NULL) {
        cmsCloseProfile(DbgThread(), h);
        return 0;
    }

    if (SimultaneousErrors != 9) return 0;

    return 1;
}