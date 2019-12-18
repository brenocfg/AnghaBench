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
struct TYPE_3__ {char* pProfileData; void* cbDataSize; void* dwType; } ;
typedef  TYPE_1__ PROFILE ;
typedef  int /*<<< orphan*/ * HTRANSFORM ;
typedef  int /*<<< orphan*/ * HPROFILE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 void* PROFILE_FILENAME ; 
 int /*<<< orphan*/  PROFILE_READ ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCloseColorProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pCreateMultiProfileTransform (int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pDeleteColorTransform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pOpenColorProfileA (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strlen (char*) ; 

__attribute__((used)) static void test_CreateMultiProfileTransform( char *standardprofile, char *testprofile )
{
    PROFILE profile;
    HPROFILE handle[2];
    HTRANSFORM transform;
    DWORD intents[2] = { INTENT_PERCEPTUAL, INTENT_PERCEPTUAL };

    if (testprofile)
    {
        profile.dwType       = PROFILE_FILENAME;
        profile.pProfileData = standardprofile;
        profile.cbDataSize   = strlen(standardprofile);

        handle[0] = pOpenColorProfileA( &profile, PROFILE_READ, 0, OPEN_EXISTING );
        ok( handle[0] != NULL, "got %u\n", GetLastError() );

        profile.dwType       = PROFILE_FILENAME;
        profile.pProfileData = testprofile;
        profile.cbDataSize   = strlen(testprofile);

        handle[1] = pOpenColorProfileA( &profile, PROFILE_READ, 0, OPEN_EXISTING );
        ok( handle[1] != NULL, "got %u\n", GetLastError() );

        transform = pCreateMultiProfileTransform( handle, 2, intents, 2, 0, 0 );
        ok( transform != NULL, "got %u\n", GetLastError() );

        pDeleteColorTransform( transform );
        pCloseColorProfile( handle[0] );
        pCloseColorProfile( handle[1] );
    }
}