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
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_3__ {char* pProfileData; int /*<<< orphan*/  cbDataSize; int /*<<< orphan*/  dwType; } ;
typedef  int TAGTYPE ;
typedef  TYPE_1__ PROFILE ;
typedef  int /*<<< orphan*/ * HPROFILE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PROFILE_FILENAME ; 
 int /*<<< orphan*/  PROFILE_READ ; 
 int /*<<< orphan*/  PROFILE_READWRITE ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pCloseColorProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pGetColorProfileElement (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pOpenColorProfileA (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pSetColorProfileElement (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void test_SetColorProfileElement( char *testprofile )
{
    if (testprofile)
    {
        PROFILE profile;
        HPROFILE handle;
        DWORD size;
        BOOL ret, ref;

        TAGTYPE tag = 0x63707274;  /* 'cprt' */
        static char data[] = "(c) The Wine Project";
        static char buffer[51];

        profile.dwType = PROFILE_FILENAME;
        profile.pProfileData = testprofile;
        profile.cbDataSize = strlen(testprofile);

        /* Parameter checks */

        handle = pOpenColorProfileA( &profile, PROFILE_READ, 0, OPEN_EXISTING );
        ok( handle != NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

        ret = pSetColorProfileElement( handle, tag, 0, &size, data );
        ok( !ret, "SetColorProfileElement() succeeded (%d)\n", GetLastError() );

        pCloseColorProfile( handle );

        handle = pOpenColorProfileA( &profile, PROFILE_READWRITE, 0, OPEN_EXISTING );
        ok( handle != NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

        ret = pSetColorProfileElement( NULL, 0, 0, NULL, NULL );
        ok( !ret, "SetColorProfileElement() succeeded (%d)\n", GetLastError() );

        ret = pSetColorProfileElement( handle, 0, 0, NULL, NULL );
        ok( !ret, "SetColorProfileElement() succeeded (%d)\n", GetLastError() );

        ret = pSetColorProfileElement( handle, tag, 0, NULL, NULL );
        ok( !ret, "SetColorProfileElement() succeeded (%d)\n", GetLastError() );

        ret = pSetColorProfileElement( handle, tag, 0, &size, NULL );
        ok( !ret, "SetColorProfileElement() succeeded (%d)\n", GetLastError() );

        /* Functional checks */

        size = sizeof(data);
        ret = pSetColorProfileElement( handle, tag, 0, &size, data );
        ok( ret, "SetColorProfileElement() failed %u\n", GetLastError() );

        size = sizeof(buffer);
        ret = pGetColorProfileElement( handle, tag, 0, &size, buffer, &ref );
        ok( ret, "GetColorProfileElement() failed %u\n", GetLastError() );
        ok( size > 0, "wrong size\n" );

        ok( !memcmp( data, buffer, sizeof(data) ),
            "Unexpected tag data, expected %s, got %s (%u)\n", data, buffer, GetLastError() );

        pCloseColorProfile( handle );
    }
}