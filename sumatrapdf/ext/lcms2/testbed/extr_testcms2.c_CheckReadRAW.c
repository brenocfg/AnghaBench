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
 int /*<<< orphan*/  SubTest (char*) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int cmsReadRawTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cmsSigGamutTag ; 
 int /*<<< orphan*/  cmsSigGreenColorantTag ; 

__attribute__((used)) static
cmsInt32Number CheckReadRAW(void)
{
    cmsInt32Number tag_size, tag_size1;
    char buffer[4];
    cmsHPROFILE hProfile;


    SubTest("RAW read on on-disk");
    hProfile = cmsOpenProfileFromFile(DbgThread(), "test1.icc", "r");

    if (hProfile == NULL)
        return 0;

    tag_size = cmsReadRawTag(DbgThread(), hProfile, cmsSigGamutTag, buffer, 4);
    tag_size1 = cmsReadRawTag(DbgThread(), hProfile, cmsSigGamutTag, NULL, 0);

    cmsCloseProfile(DbgThread(), hProfile);

    if (tag_size != 4)
        return 0;

    if (tag_size1 != 37009)
        return 0;

    SubTest("RAW read on in-memory created profiles");
    hProfile = cmsCreate_sRGBProfile(DbgThread());
    tag_size = cmsReadRawTag(DbgThread(), hProfile, cmsSigGreenColorantTag, buffer, 4);
    tag_size1 = cmsReadRawTag(DbgThread(), hProfile, cmsSigGreenColorantTag, NULL, 0);

    cmsCloseProfile(DbgThread(), hProfile);

    if (tag_size != 4)
        return 0;
    if (tag_size1 != 20)
        return 0;

    return 1;
}