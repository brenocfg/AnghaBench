#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ID8; } ;
typedef  TYPE_1__ cmsProfileID ;
typedef  scalar_t__ cmsHPROFILE ;
typedef  int /*<<< orphan*/  _cmsICCPROFILE ;
typedef  int /*<<< orphan*/  ProfileID2 ;
typedef  int /*<<< orphan*/  ProfileID1 ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmsGetHeaderProfileID (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsMD5computeID (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
int CheckMD5(void)
{
    _cmsICCPROFILE* h;
    cmsHPROFILE pProfile = cmsOpenProfileFromFile(DbgThread(), "sRGBlcms2.icc", "r");
    cmsProfileID ProfileID1, ProfileID2, ProfileID3, ProfileID4;

    h =(_cmsICCPROFILE*) pProfile;
    if (cmsMD5computeID(DbgThread(), pProfile)) cmsGetHeaderProfileID(DbgThread(), pProfile, ProfileID1.ID8);
    if (cmsMD5computeID(DbgThread(), pProfile)) cmsGetHeaderProfileID(DbgThread(), pProfile,ProfileID2.ID8);

    cmsCloseProfile(DbgThread(), pProfile);


    pProfile = cmsOpenProfileFromFile(DbgThread(), "sRGBlcms2.icc", "r");

    h =(_cmsICCPROFILE*) pProfile;
    if (cmsMD5computeID(DbgThread(), pProfile)) cmsGetHeaderProfileID(DbgThread(), pProfile, ProfileID3.ID8);
    if (cmsMD5computeID(DbgThread(), pProfile)) cmsGetHeaderProfileID(DbgThread(), pProfile,ProfileID4.ID8);

    cmsCloseProfile(DbgThread(), pProfile);

    return ((memcmp(ProfileID1.ID8, ProfileID3.ID8, sizeof(ProfileID1)) == 0) &&
            (memcmp(ProfileID2.ID8, ProfileID4.ID8, sizeof(ProfileID2)) == 0));
}