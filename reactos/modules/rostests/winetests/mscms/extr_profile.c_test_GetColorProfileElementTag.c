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
struct TYPE_3__ {char* pProfileData; int /*<<< orphan*/  cbDataSize; int /*<<< orphan*/  dwType; } ;
typedef  scalar_t__ TAGTYPE ;
typedef  TYPE_1__ PROFILE ;
typedef  int /*<<< orphan*/ * HPROFILE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PROFILE_FILENAME ; 
 int /*<<< orphan*/  PROFILE_READ ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCloseColorProfile (int /*<<< orphan*/ *) ; 
 scalar_t__ pGetColorProfileElementTag (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/ * pOpenColorProfileA (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void test_GetColorProfileElementTag( char *standardprofile )
{
    if (standardprofile)
    {
        PROFILE profile;
        HPROFILE handle;
        BOOL ret;
        DWORD index = 1;
        TAGTYPE tag, expect = 0x63707274;  /* 'cprt' */

        profile.dwType = PROFILE_FILENAME;
        profile.pProfileData = standardprofile;
        profile.cbDataSize = strlen(standardprofile);

        handle = pOpenColorProfileA( &profile, PROFILE_READ, 0, OPEN_EXISTING );
        ok( handle != NULL, "OpenColorProfileA() failed (%d)\n", GetLastError() );

        /* Parameter checks */

        ret = pGetColorProfileElementTag( NULL, index, &tag );
        ok( !ret, "GetColorProfileElementTag() succeeded (%d)\n", GetLastError() );

        ret = pGetColorProfileElementTag( handle, 0, &tag );
        ok( !ret, "GetColorProfileElementTag() succeeded (%d)\n", GetLastError() );

        ret = pGetColorProfileElementTag( handle, index, NULL );
        ok( !ret, "GetColorProfileElementTag() succeeded (%d)\n", GetLastError() );

        ret = pGetColorProfileElementTag( handle, 18, NULL );
        ok( !ret, "GetColorProfileElementTag() succeeded (%d)\n", GetLastError() );

        /* Functional checks */

        ret = pGetColorProfileElementTag( handle, index, &tag );
        ok( ret && tag == expect, "GetColorProfileElementTag() failed (%d)\n",
            GetLastError() );

        pCloseColorProfile( handle );
    }
}