#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expect ;
typedef  float WCHAR ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int /*<<< orphan*/  member_7; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  memcmp (TYPE_1__*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int pInternetTimeToSystemTimeW (float const*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void InternetTimeToSystemTimeW_test(void)
{
    BOOL ret;
    SYSTEMTIME time;
    static const SYSTEMTIME expect = { 2005, 1, 5, 7, 12, 6, 35, 0 };
    static const WCHAR string[] = { 'F','r','i',',',' ','0','7',' ','J','a','n',' ','2','0','0','5',' ',
                                    '1','2',':','0','6',':','3','5',' ','G','M','T',0 };
    static const WCHAR string2[] = { ' ','f','r','i',' ','7',' ','j','a','n',' ','2','0','0','5',' ',
                                     '1','2',' ','0','6',' ','3','5',0 };
    static const WCHAR string3[] = { 'F','r',0 };

    ret = pInternetTimeToSystemTimeW( NULL, NULL, 0 );
    ok( !ret, "InternetTimeToSystemTimeW succeeded (%u)\n", GetLastError() );

    ret = pInternetTimeToSystemTimeW( NULL, &time, 0 );
    ok( !ret, "InternetTimeToSystemTimeW succeeded (%u)\n", GetLastError() );

    ret = pInternetTimeToSystemTimeW( string, NULL, 0 );
    ok( !ret, "InternetTimeToSystemTimeW succeeded (%u)\n", GetLastError() );

    ret = pInternetTimeToSystemTimeW( string, &time, 0 );
    ok( ret, "InternetTimeToSystemTimeW failed (%u)\n", GetLastError() );

    ret = pInternetTimeToSystemTimeW( string, &time, 0 );
    ok( ret, "InternetTimeToSystemTimeW failed (%u)\n", GetLastError() );
    ok( !memcmp( &time, &expect, sizeof(expect) ),
        "InternetTimeToSystemTimeW failed (%u)\n", GetLastError() );

    ret = pInternetTimeToSystemTimeW( string2, &time, 0 );
    ok( ret, "InternetTimeToSystemTimeW failed (%u)\n", GetLastError() );
    ok( !memcmp( &time, &expect, sizeof(expect) ),
        "InternetTimeToSystemTimeW failed (%u)\n", GetLastError() );

    ret = pInternetTimeToSystemTimeW( string3, &time, 0 );
    ok( ret, "InternetTimeToSystemTimeW failed (%u)\n", GetLastError() );
}