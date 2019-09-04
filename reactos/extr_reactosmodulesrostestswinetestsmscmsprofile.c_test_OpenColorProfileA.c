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
struct TYPE_3__ {char* pProfileData; int cbDataSize; void* dwType; } ;
typedef  TYPE_1__ PROFILE ;
typedef  int /*<<< orphan*/ * HPROFILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 void* PROFILE_FILENAME ; 
 int PROFILE_READ ; 
 int PROFILE_READWRITE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pCloseColorProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pOpenColorProfileA (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void test_OpenColorProfileA( char *standardprofile )
{
    PROFILE profile;
    HPROFILE handle;
    BOOL ret;

    profile.dwType = PROFILE_FILENAME;
    profile.pProfileData = NULL;
    profile.cbDataSize = 0;

    /* Parameter checks */

    handle = pOpenColorProfileA( NULL, 0, 0, 0 );
    ok( handle == NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

    handle = pOpenColorProfileA( &profile, 0, 0, 0 );
    ok( handle == NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

    handle = pOpenColorProfileA( &profile, PROFILE_READ, 0, 0 );
    ok( handle == NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

    handle = pOpenColorProfileA( &profile, PROFILE_READWRITE, 0, 0 );
    ok( handle == NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

    ok ( !pCloseColorProfile( NULL ), "CloseColorProfile() succeeded\n" );

    if (standardprofile)
    {
        profile.pProfileData = standardprofile;
        profile.cbDataSize = strlen(standardprofile);

        handle = pOpenColorProfileA( &profile, 0, 0, 0 );
        ok( handle == NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

        handle = pOpenColorProfileA( &profile, PROFILE_READ, 0, 0 );
        ok( handle == NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

        handle = pOpenColorProfileA( &profile, PROFILE_READ|PROFILE_READWRITE, 0, 0 );
        ok( handle == NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

        /* Functional checks */

        handle = pOpenColorProfileA( &profile, PROFILE_READ, 0, OPEN_EXISTING );
        ok( handle != NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

        ret = pCloseColorProfile( handle );
        ok( ret, "CloseColorProfile() failed (%d)\n", GetLastError() );

        profile.dwType = PROFILE_FILENAME;
        profile.pProfileData = (void *)"sRGB Color Space Profile.icm";
        profile.cbDataSize = sizeof("sRGB Color Space Profile.icm");

        handle = pOpenColorProfileA( &profile, PROFILE_READ, FILE_SHARE_READ, OPEN_EXISTING );
        ok( handle != NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

        ret = pCloseColorProfile( handle );
        ok( ret, "CloseColorProfile() failed (%d)\n", GetLastError() );
    }
}