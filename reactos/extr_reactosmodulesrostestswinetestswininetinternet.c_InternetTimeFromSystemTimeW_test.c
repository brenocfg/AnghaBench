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
typedef  int /*<<< orphan*/  string ;
typedef  int /*<<< orphan*/  expect ;
typedef  float WCHAR ;
struct TYPE_3__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int /*<<< orphan*/  member_7; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INTERNET_RFC1123_BUFSIZE ; 
 scalar_t__ INTERNET_RFC1123_FORMAT ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  memcmp (float*,float const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pInternetTimeFromSystemTimeW (TYPE_1__ const*,scalar_t__,float*,int) ; 

__attribute__((used)) static void InternetTimeFromSystemTimeW_test(void)
{
    BOOL ret;
    static const SYSTEMTIME time = { 2005, 1, 5, 7, 12, 6, 35, 0 };
    WCHAR string[INTERNET_RFC1123_BUFSIZE + 1];
    static const WCHAR expect[] = { 'F','r','i',',',' ','0','7',' ','J','a','n',' ','2','0','0','5',' ',
                                    '1','2',':','0','6',':','3','5',' ','G','M','T',0 };
    DWORD error;

    ret = pInternetTimeFromSystemTimeW( &time, INTERNET_RFC1123_FORMAT, string, sizeof(string) );
    ok( ret, "InternetTimeFromSystemTimeW failed (%u)\n", GetLastError() );

    ok( !memcmp( string, expect, sizeof(expect) ),
        "InternetTimeFromSystemTimeW failed (%u)\n", GetLastError() );

    /* test NULL time parameter */
    SetLastError(0xdeadbeef);
    ret = pInternetTimeFromSystemTimeW( NULL, INTERNET_RFC1123_FORMAT, string, sizeof(string) );
    error = GetLastError();
    ok( !ret, "InternetTimeFromSystemTimeW should have returned FALSE\n" );
    ok( error == ERROR_INVALID_PARAMETER,
        "InternetTimeFromSystemTimeW failed with ERROR_INVALID_PARAMETER instead of %u\n",
        error );

    /* test NULL string parameter */
    SetLastError(0xdeadbeef);
    ret = pInternetTimeFromSystemTimeW( &time, INTERNET_RFC1123_FORMAT, NULL, sizeof(string) );
    error = GetLastError();
    ok( !ret, "InternetTimeFromSystemTimeW should have returned FALSE\n" );
    ok( error == ERROR_INVALID_PARAMETER,
        "InternetTimeFromSystemTimeW failed with ERROR_INVALID_PARAMETER instead of %u\n",
        error );

    /* test invalid format parameter */
    SetLastError(0xdeadbeef);
    ret = pInternetTimeFromSystemTimeW( &time, INTERNET_RFC1123_FORMAT + 1, string, sizeof(string) );
    error = GetLastError();
    ok( !ret, "InternetTimeFromSystemTimeW should have returned FALSE\n" );
    ok( error == ERROR_INVALID_PARAMETER,
        "InternetTimeFromSystemTimeW failed with ERROR_INVALID_PARAMETER instead of %u\n",
        error );

    /* test too small buffer size */
    SetLastError(0xdeadbeef);
    ret = pInternetTimeFromSystemTimeW( &time, INTERNET_RFC1123_FORMAT, string, sizeof(string)/sizeof(string[0]) );
    error = GetLastError();
    ok( !ret, "InternetTimeFromSystemTimeW should have returned FALSE\n" );
    ok( error == ERROR_INSUFFICIENT_BUFFER,
        "InternetTimeFromSystemTimeW failed with ERROR_INSUFFICIENT_BUFFER instead of %u\n",
        error );
}