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
typedef  int /*<<< orphan*/  val2 ;
typedef  int /*<<< orphan*/  val1 ;
typedef  int /*<<< orphan*/  bufferW ;
typedef  int /*<<< orphan*/  bufferA ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_GREGORIAN ; 
 int CAL_ITWODIGITYEARMAX ; 
 int CAL_RETURN_NUMBER ; 
 int CAL_SDAYNAME1 ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  GetLastError () ; 
 int LANG_SYSTEM_DEFAULT ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pGetCalendarInfoA (int,int /*<<< orphan*/ ,int,char*,int,int*) ; 
 int pGetCalendarInfoW (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_GetCalendarInfo(void)
{
    char bufferA[20];
    WCHAR bufferW[20];
    DWORD val1, val2;
    int ret, ret2;

    if (!pGetCalendarInfoA || !pGetCalendarInfoW)
    {
        trace( "GetCalendarInfo missing\n" );
        return;
    }

    ret = pGetCalendarInfoA( 0x0409, CAL_GREGORIAN, CAL_ITWODIGITYEARMAX | CAL_RETURN_NUMBER,
                             NULL, 0, &val1 );
    ok( ret, "GetCalendarInfoA failed err %u\n", GetLastError() );
    ok( ret == sizeof(val1), "wrong size %u\n", ret );
    ok( val1 >= 2000 && val1 < 2100, "wrong value %u\n", val1 );

    ret = pGetCalendarInfoW( 0x0409, CAL_GREGORIAN, CAL_ITWODIGITYEARMAX | CAL_RETURN_NUMBER,
                             NULL, 0, &val2 );
    ok( ret, "GetCalendarInfoW failed err %u\n", GetLastError() );
    ok( ret == sizeof(val2)/sizeof(WCHAR), "wrong size %u\n", ret );
    ok( val1 == val2, "A/W mismatch %u/%u\n", val1, val2 );

    ret = pGetCalendarInfoA( 0x0409, CAL_GREGORIAN, CAL_ITWODIGITYEARMAX, bufferA, sizeof(bufferA), NULL );
    ok( ret, "GetCalendarInfoA failed err %u\n", GetLastError() );
    ok( ret == 5, "wrong size %u\n", ret );
    ok( atoi( bufferA ) == val1, "wrong value %s/%u\n", bufferA, val1 );

    ret = pGetCalendarInfoW( 0x0409, CAL_GREGORIAN, CAL_ITWODIGITYEARMAX, bufferW, sizeof(bufferW), NULL );
    ok( ret, "GetCalendarInfoW failed err %u\n", GetLastError() );
    ok( ret == 5, "wrong size %u\n", ret );
    memset( bufferA, 0x55, sizeof(bufferA) );
    WideCharToMultiByte( CP_ACP, 0, bufferW, -1, bufferA, sizeof(bufferA), NULL, NULL );
    ok( atoi( bufferA ) == val1, "wrong value %s/%u\n", bufferA, val1 );

    ret = pGetCalendarInfoA( 0x0409, CAL_GREGORIAN, CAL_ITWODIGITYEARMAX | CAL_RETURN_NUMBER,
                             NULL, 0, NULL );
    ok( !ret, "GetCalendarInfoA succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    ret = pGetCalendarInfoA( 0x0409, CAL_GREGORIAN, CAL_ITWODIGITYEARMAX, NULL, 0, NULL );
    ok( ret, "GetCalendarInfoA failed err %u\n", GetLastError() );
    ok( ret == 5, "wrong size %u\n", ret );

    ret = pGetCalendarInfoW( 0x0409, CAL_GREGORIAN, CAL_ITWODIGITYEARMAX | CAL_RETURN_NUMBER,
                             NULL, 0, NULL );
    ok( !ret, "GetCalendarInfoW succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    ret = pGetCalendarInfoW( 0x0409, CAL_GREGORIAN, CAL_ITWODIGITYEARMAX, NULL, 0, NULL );
    ok( ret, "GetCalendarInfoW failed err %u\n", GetLastError() );
    ok( ret == 5, "wrong size %u\n", ret );

    ret = pGetCalendarInfoA( LANG_SYSTEM_DEFAULT, CAL_GREGORIAN, CAL_SDAYNAME1,
                             bufferA, sizeof(bufferA), NULL);
    ok( ret, "GetCalendarInfoA failed err %u\n", GetLastError() );
    ret2 = pGetCalendarInfoA( LANG_SYSTEM_DEFAULT, CAL_GREGORIAN, CAL_SDAYNAME1,
                              bufferA, 0, NULL);
    ok( ret2, "GetCalendarInfoA failed err %u\n", GetLastError() );
    ok( ret == ret2, "got %d, expected %d\n", ret2, ret );

    ret2 = pGetCalendarInfoW( LANG_SYSTEM_DEFAULT, CAL_GREGORIAN, CAL_SDAYNAME1,
                              bufferW, sizeof(bufferW), NULL);
    ok( ret2, "GetCalendarInfoW failed err %u\n", GetLastError() );
    ret2 = WideCharToMultiByte( CP_ACP, 0, bufferW, -1, NULL, 0, NULL, NULL );
    ok( ret == ret2, "got %d, expected %d\n", ret, ret2 );
}