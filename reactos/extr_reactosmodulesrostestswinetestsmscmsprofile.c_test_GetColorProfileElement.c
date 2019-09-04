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
typedef  int /*<<< orphan*/  expect ;
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
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pCloseColorProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pGetColorProfileElement (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pOpenColorProfileA (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void test_GetColorProfileElement( char *standardprofile )
{
    if (standardprofile)
    {
        PROFILE profile;
        HPROFILE handle;
        BOOL ret, ref;
        DWORD size;
        TAGTYPE tag = 0x63707274;  /* 'cprt' */
        static char buffer[51];
        static const char expect[] =
            { 0x74, 0x65, 0x78, 0x74, 0x00, 0x00, 0x00, 0x00, 0x43, 0x6f, 0x70,
              0x79, 0x72, 0x69, 0x67, 0x68, 0x74, 0x20, 0x28, 0x63, 0x29, 0x20,
              0x31, 0x39, 0x39, 0x38, 0x20, 0x48, 0x65, 0x77, 0x6c, 0x65, 0x74,
              0x74, 0x2d, 0x50, 0x61, 0x63, 0x6b, 0x61, 0x72, 0x64, 0x20, 0x43,
              0x6f, 0x6d, 0x70, 0x61, 0x6e, 0x79, 0x00 };

        profile.dwType = PROFILE_FILENAME;
        profile.pProfileData = standardprofile;
        profile.cbDataSize = strlen(standardprofile);

        handle = pOpenColorProfileA( &profile, PROFILE_READ, 0, OPEN_EXISTING );
        ok( handle != NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

        /* Parameter checks */

        ret = pGetColorProfileElement( handle, tag, 0, NULL, NULL, &ref );
        ok( !ret, "GetColorProfileElement() succeeded (%d)\n", GetLastError() );

        ret = pGetColorProfileElement( handle, tag, 0, &size, NULL, NULL );
        ok( !ret, "GetColorProfileElement() succeeded (%d)\n", GetLastError() );

        size = 0;
        ret = pGetColorProfileElement( handle, tag, 0, &size, NULL, &ref );
        ok( !ret, "GetColorProfileElement() succeeded\n" );
        ok( size > 0, "wrong size\n" );

        /* Functional checks */

        size = sizeof(buffer);
        ret = pGetColorProfileElement( handle, tag, 0, &size, buffer, &ref );
        ok( ret, "GetColorProfileElement() failed %u\n", GetLastError() );
        ok( size > 0, "wrong size\n" );
        ok( !memcmp( buffer, expect, sizeof(expect) ), "Unexpected tag data\n" );

        pCloseColorProfile( handle );
    }
}