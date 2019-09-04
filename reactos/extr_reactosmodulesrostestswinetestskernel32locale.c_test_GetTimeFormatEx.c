#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int wHour; int wMinute; int wSecond; int wMilliseconds; int wMonth; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_FLAGS ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EXPECT_EQW ; 
 int /*<<< orphan*/  EXPECT_LENW ; 
 int /*<<< orphan*/  GetLastError () ; 
 int NUO ; 
 int /*<<< orphan*/  STRINGSW (char*,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TIME_FORCE24HOURFORMAT ; 
 int TIME_NOMINUTESORSECONDS ; 
 int TIME_NOSECONDS ; 
 int TIME_NOTIMEMARKER ; 
 int /*<<< orphan*/  localeW ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pGetTimeFormatEx (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int strlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetTimeFormatEx(void)
{
  int ret;
  SYSTEMTIME  curtime;
  WCHAR buffer[BUFFER_SIZE], input[BUFFER_SIZE], Expected[BUFFER_SIZE];

  if (!pGetTimeFormatEx)
  {
      win_skip("GetTimeFormatEx not supported\n");
      return;
  }

  memset(&curtime, 2, sizeof(SYSTEMTIME));
  STRINGSW("tt HH':'mm'@'ss", ""); /* Invalid time */
  SetLastError(0xdeadbeef);
  ret = pGetTimeFormatEx(localeW, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  curtime.wHour = 8;
  curtime.wMinute = 56;
  curtime.wSecond = 13;
  curtime.wMilliseconds = 22;
  STRINGSW("tt HH':'mm'@'ss", "AM 08:56@13"); /* Valid time */
  SetLastError(0xdeadbeef);
  ret = pGetTimeFormatEx(localeW, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  /* MSDN: LOCALE_NOUSEROVERRIDE can't be specified with a format string */
  SetLastError(0xdeadbeef);
  ret = pGetTimeFormatEx(localeW, NUO|TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok(!ret && GetLastError() == ERROR_INVALID_FLAGS,
     "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());

  STRINGSW("tt HH':'mm'@'ss", "A"); /* Insufficient buffer */
  SetLastError(0xdeadbeef);
  ret = pGetTimeFormatEx(localeW, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, 2);
  ok( !ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
      "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());

  STRINGSW("tt HH':'mm'@'ss", "AM 08:56@13"); /* Calculate length only */
  ret = pGetTimeFormatEx(localeW, TIME_FORCE24HOURFORMAT, &curtime, input, NULL, 0);
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW;

  STRINGSW("", "8 AM"); /* TIME_NOMINUTESORSECONDS, default format */
  ret = pGetTimeFormatEx(localeW, NUO|TIME_NOMINUTESORSECONDS, &curtime, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("m1s2m3s4", ""); /* TIME_NOMINUTESORSECONDS/complex format */
  ret = pGetTimeFormatEx(localeW, TIME_NOMINUTESORSECONDS, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret == strlenW(buffer)+1, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("", "8:56 AM"); /* TIME_NOSECONDS/Default format */
  ret = pGetTimeFormatEx(localeW, NUO|TIME_NOSECONDS, &curtime, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("h:m:s tt", "8:56 AM"); /* TIME_NOSECONDS */
  ret = pGetTimeFormatEx(localeW, TIME_NOSECONDS, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("h.@:m.@:s.@:tt", "8.@:56AM"); /* Multiple delimiters */
  ret = pGetTimeFormatEx(localeW, TIME_NOSECONDS, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("s1s2s3", ""); /* Duplicate tokens */
  ret = pGetTimeFormatEx(localeW, TIME_NOSECONDS, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret == strlenW(buffer)+1, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("t/tt", "A/AM"); /* AM time marker */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  curtime.wHour = 13;
  STRINGSW("t/tt", "P/PM"); /* PM time marker */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("h1t2tt3m", "156"); /* TIME_NOTIMEMARKER: removes text around time marker token */
  ret = pGetTimeFormatEx(localeW, TIME_NOTIMEMARKER, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("h:m:s tt", "13:56:13 PM"); /* TIME_FORCE24HOURFORMAT */
  ret = pGetTimeFormatEx(localeW, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("h:m:s", "13:56:13"); /* TIME_FORCE24HOURFORMAT doesn't add time marker */
  ret = pGetTimeFormatEx(localeW, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  curtime.wHour = 14; /* change this to 14 or 2pm */
  curtime.wMinute = 5;
  curtime.wSecond = 3;
  STRINGSW("h hh H HH m mm s ss t tt", "2 02 14 14 5 05 3 03 P PM"); /* 24 hrs, leading 0 */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  curtime.wHour = 0;
  STRINGSW("h/H/hh/HH", "12/0/12/00"); /* "hh" and "HH" */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("h:m:s tt", "12:5:3 AM"); /* non-zero flags should fail with format, doesn't */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  /* try to convert formatting strings with more than two letters
   * "h:hh:hhh:H:HH:HHH:m:mm:mmm:M:MM:MMM:s:ss:sss:S:SS:SSS"
   * NOTE: We expect any letter for which there is an upper case value
   *       we should see a replacement.  For letters that DO NOT have
   *       upper case values we should see NO REPLACEMENT.
   */
  curtime.wHour = 8;
  curtime.wMinute = 56;
  curtime.wSecond = 13;
  curtime.wMilliseconds = 22;
  STRINGSW("h:hh:hhh H:HH:HHH m:mm:mmm M:MM:MMM s:ss:sss S:SS:SSS",
           "8:08:08 8:08:08 56:56:56 M:MM:MMM 13:13:13 S:SS:SSS");
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("h", "text"); /* Don't write to buffer if len is 0 */
  lstrcpyW(buffer, Expected);
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, 0);
  ok(ret == 2, "Expected ret == 2, got %d, error %d\n", ret, GetLastError());
  EXPECT_EQW;

  STRINGSW("h 'h' H 'H' HH 'HH' m 'm' s 's' t 't' tt 'tt'",
           "8 h 8 H 08 HH 56 m 13 s A t AM tt"); /* "'" preserves tokens */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("'''", "'"); /* invalid quoted string */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  /* test that msdn suggested single quotation usage works as expected */
  STRINGSW("''''", "'"); /* single quote mark */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("''HHHHHH", "08"); /* Normal use */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  /* and test for normal use of the single quotation mark */
  STRINGSW("'''HHHHHH'", "'HHHHHH"); /* Normal use */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("'''HHHHHH", "'HHHHHH"); /* Odd use */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("'123'tt", ""); /* TIME_NOTIMEMARKER drops literals too */
  ret = pGetTimeFormatEx(localeW, TIME_NOTIMEMARKER, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  curtime.wHour = 25;
  STRINGSW("'123'tt", ""); /* Invalid time */
  SetLastError(0xdeadbeef);
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  curtime.wHour = 12;
  curtime.wMonth = 60; /* Invalid */
  STRINGSW("h:m:s", "12:56:13"); /* Invalid date */
  ret = pGetTimeFormatEx(localeW, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;
}