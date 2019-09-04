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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int wYear; int wMonth; int wDay; int wDayOfWeek; int wHour; int wMinute; int wSecond; int wMilliseconds; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int DATE_LONGDATE ; 
 int DATE_SHORTDATE ; 
 int /*<<< orphan*/  ERROR_INVALID_FLAGS ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EXPECT_EQW ; 
 int /*<<< orphan*/  EXPECT_LENW ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  STRINGSW (char*,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * emptyW ; 
 int /*<<< orphan*/  localeW ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pGetDateFormatEx (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetDateFormatEx(void)
{
  int ret;
  SYSTEMTIME  curtime;
  WCHAR buffer[BUFFER_SIZE], input[BUFFER_SIZE], Expected[BUFFER_SIZE];

  if (!pGetDateFormatEx)
  {
      win_skip("GetDateFormatEx not supported\n");
      return;
  }

  STRINGSW("",""); /* If flags are set, then format must be NULL */
  SetLastError(0xdeadbeef);
  ret = pGetDateFormatEx(localeW, DATE_LONGDATE, NULL,
                       input, buffer, COUNTOF(buffer), NULL);
  ok(!ret && GetLastError() == ERROR_INVALID_FLAGS,
     "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());
  EXPECT_EQW;

  STRINGSW("",""); /* NULL buffer, len > 0 */
  SetLastError(0xdeadbeef);
  ret = pGetDateFormatEx(localeW, 0, NULL, input, NULL, COUNTOF(buffer), NULL);
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSW("",""); /* NULL buffer, len == 0 */
  ret = pGetDateFormatEx(localeW, 0, NULL, input, NULL, 0, NULL);
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("",""); /* Invalid flag combination */
  SetLastError(0xdeadbeef);
  ret = pGetDateFormatEx(localeW, DATE_LONGDATE|DATE_SHORTDATE, NULL,
                       input, NULL, 0, NULL);
  ok(!ret && GetLastError() == ERROR_INVALID_FLAGS,
     "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());
  EXPECT_EQW;

  curtime.wYear = 2002;
  curtime.wMonth = 10;
  curtime.wDay = 23;
  curtime.wDayOfWeek = 45612; /* Should be 3 - Wednesday */
  curtime.wHour = 65432; /* Invalid */
  curtime.wMinute = 34512; /* Invalid */
  curtime.wSecond = 65535; /* Invalid */
  curtime.wMilliseconds = 12345;
  STRINGSW("dddd d MMMM yyyy","Wednesday 23 October 2002"); /* Incorrect DOW and time */
  ret = pGetDateFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer), NULL);
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  curtime.wYear = 2002;
  curtime.wMonth = 10;
  curtime.wDay = 23;
  curtime.wDayOfWeek = 45612; /* Should be 3 - Wednesday */
  curtime.wHour = 65432; /* Invalid */
  curtime.wMinute = 34512; /* Invalid */
  curtime.wSecond = 65535; /* Invalid */
  curtime.wMilliseconds = 12345;
  STRINGSW("dddd d MMMM yyyy","Wednesday 23 October 2002");
  ret = pGetDateFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer), emptyW); /* Use reserved arg */
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  /* Limit tests */

  curtime.wYear = 1601;
  curtime.wMonth = 1;
  curtime.wDay = 1;
  curtime.wDayOfWeek = 0; /* Irrelevant */
  curtime.wHour = 0;
  curtime.wMinute = 0;
  curtime.wSecond = 0;
  curtime.wMilliseconds = 0;
  STRINGSW("dddd d MMMM yyyy","Monday 1 January 1601");
  SetLastError(0xdeadbeef);
  ret = pGetDateFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer), NULL);
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  curtime.wYear = 1600;
  curtime.wMonth = 12;
  curtime.wDay = 31;
  curtime.wDayOfWeek = 0; /* Irrelevant */
  curtime.wHour = 23;
  curtime.wMinute = 59;
  curtime.wSecond = 59;
  curtime.wMilliseconds = 999;
  STRINGSW("dddd d MMMM yyyy","Friday 31 December 1600");
  SetLastError(0xdeadbeef);
  ret = pGetDateFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer), NULL);
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
}