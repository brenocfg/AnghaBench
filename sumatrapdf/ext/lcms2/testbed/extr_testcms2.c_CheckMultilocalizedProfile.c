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
typedef  int /*<<< orphan*/  cmsMLU ;
typedef  int /*<<< orphan*/  cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsMLUgetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*,int) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigProfileDescriptionTag ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static
cmsInt32Number CheckMultilocalizedProfile(void)
{
    cmsHPROFILE hProfile;
    cmsMLU *Pt;
    char Buffer[256];

    hProfile = cmsOpenProfileFromFile(DbgThread(), "crayons.icc", "r");

    Pt = (cmsMLU *) cmsReadTag(DbgThread(), hProfile, cmsSigProfileDescriptionTag);
    cmsMLUgetASCII(DbgThread(), Pt, "en", "GB", Buffer, 256);
    if (strcmp(Buffer, "Crayon Colours") != 0) return FALSE;
    cmsMLUgetASCII(DbgThread(), Pt, "en", "US", Buffer, 256);
    if (strcmp(Buffer, "Crayon Colors") != 0) return FALSE;

    cmsCloseProfile(DbgThread(), hProfile);

    return TRUE;
}