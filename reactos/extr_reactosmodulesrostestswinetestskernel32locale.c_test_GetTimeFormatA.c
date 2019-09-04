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
struct TYPE_4__ {int wHour; int wMinute; int wSecond; int wMilliseconds; int wMonth; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  LCID ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int COUNTOF (char*) ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_FLAGS ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EXPECT_EQA ; 
 int /*<<< orphan*/  EXPECT_LENA ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetTimeFormatA (int /*<<< orphan*/ ,int,TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUO ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  STRINGSA (char*,char*) ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TIME_FORCE24HOURFORMAT ; 
 int TIME_NOMINUTESORSECONDS ; 
 int TIME_NOSECONDS ; 
 int TIME_NOTIMEMARKER ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void test_GetTimeFormatA(void)
{
  int ret;
  SYSTEMTIME  curtime;
  LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
  char buffer[BUFFER_SIZE], input[BUFFER_SIZE], Expected[BUFFER_SIZE];

  memset(&curtime, 2, sizeof(SYSTEMTIME));
  STRINGSA("tt HH':'mm'@'ss", ""); /* Invalid time */
  SetLastError(0xdeadbeef);
  ret = GetTimeFormatA(lcid, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  curtime.wHour = 8;
  curtime.wMinute = 56;
  curtime.wSecond = 13;
  curtime.wMilliseconds = 22;
  STRINGSA("tt HH':'mm'@'ss", "AM 08:56@13"); /* Valid time */
  SetLastError(0xdeadbeef);
  ret = GetTimeFormatA(lcid, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  /* MSDN: LOCALE_NOUSEROVERRIDE can't be specified with a format string */
  SetLastError(0xdeadbeef);
  ret = GetTimeFormatA(lcid, NUO|TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok(!ret && GetLastError() == ERROR_INVALID_FLAGS,
     "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());

  STRINGSA("tt HH':'mm'@'ss", "A"); /* Insufficient buffer */
  SetLastError(0xdeadbeef);
  ret = GetTimeFormatA(lcid, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, 2);
  ok( !ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
      "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());

  STRINGSA("tt HH':'mm'@'ss", "AM 08:56@13"); /* Calculate length only */
  ret = GetTimeFormatA(lcid, TIME_FORCE24HOURFORMAT, &curtime, input, NULL, 0);
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA;

  STRINGSA("", "8 AM"); /* TIME_NOMINUTESORSECONDS, default format */
  ret = GetTimeFormatA(lcid, NUO|TIME_NOMINUTESORSECONDS, &curtime, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("m1s2m3s4", ""); /* TIME_NOMINUTESORSECONDS/complex format */
  ret = GetTimeFormatA(lcid, TIME_NOMINUTESORSECONDS, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret == strlen(buffer)+1, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  ok( !strcmp( buffer, "" ) || broken( !strcmp( buffer, "4" )), /* win9x */
      "Expected '', got '%s'\n", buffer );

  STRINGSA("", "8:56 AM"); /* TIME_NOSECONDS/Default format */
  ret = GetTimeFormatA(lcid, NUO|TIME_NOSECONDS, &curtime, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("h:m:s tt", "8:56 AM"); /* TIME_NOSECONDS */
  strcpy(Expected, "8:56 AM");
  ret = GetTimeFormatA(lcid, TIME_NOSECONDS, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("h.@:m.@:s.@:tt", "8.@:56AM"); /* Multiple delimiters */
  ret = GetTimeFormatA(lcid, TIME_NOSECONDS, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  ok( !strcmp( buffer, "8.@:56AM" ) || broken( !strcmp( buffer, "8.@:56.@:AM" )) /* win9x */,
      "Expected '8.@:56AM', got '%s'\n", buffer );

  STRINGSA("s1s2s3", ""); /* Duplicate tokens */
  ret = GetTimeFormatA(lcid, TIME_NOSECONDS, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret == strlen(buffer)+1, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  ok( !strcmp( buffer, "" ) || broken( !strcmp( buffer, "3" )), /* win9x */
      "Expected '', got '%s'\n", buffer );

  STRINGSA("t/tt", "A/AM"); /* AM time marker */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  curtime.wHour = 13;
  STRINGSA("t/tt", "P/PM"); /* PM time marker */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("h1t2tt3m", "156"); /* TIME_NOTIMEMARKER: removes text around time marker token */
  ret = GetTimeFormatA(lcid, TIME_NOTIMEMARKER, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("h:m:s tt", "13:56:13 PM"); /* TIME_FORCE24HOURFORMAT */
  ret = GetTimeFormatA(lcid, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("h:m:s", "13:56:13"); /* TIME_FORCE24HOURFORMAT doesn't add time marker */
  ret = GetTimeFormatA(lcid, TIME_FORCE24HOURFORMAT, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  curtime.wHour = 14; /* change this to 14 or 2pm */
  curtime.wMinute = 5;
  curtime.wSecond = 3;
  STRINGSA("h hh H HH m mm s ss t tt", "2 02 14 14 5 05 3 03 P PM"); /* 24 hrs, leading 0 */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  curtime.wHour = 0;
  STRINGSA("h/H/hh/HH", "12/0/12/00"); /* "hh" and "HH" */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("h:m:s tt", "12:5:3 AM"); /* non-zero flags should fail with format, doesn't */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

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
  STRINGSA("h:hh:hhh H:HH:HHH m:mm:mmm M:MM:MMM s:ss:sss S:SS:SSS",
           "8:08:08 8:08:08 56:56:56 M:MM:MMM 13:13:13 S:SS:SSS");
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("h", "text"); /* Don't write to buffer if len is 0 */
  strcpy(buffer, "text");
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, 0);
  ok(ret == 2, "Expected ret == 2, got %d, error %d\n", ret, GetLastError());
  EXPECT_EQA;

  STRINGSA("h 'h' H 'H' HH 'HH' m 'm' s 's' t 't' tt 'tt'",
           "8 h 8 H 08 HH 56 m 13 s A t AM tt"); /* "'" preserves tokens */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("'''", "'"); /* invalid quoted string */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  /* test that msdn suggested single quotation usage works as expected */
  STRINGSA("''''", "'"); /* single quote mark */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("''HHHHHH", "08"); /* Normal use */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  /* and test for normal use of the single quotation mark */
  STRINGSA("'''HHHHHH'", "'HHHHHH"); /* Normal use */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("'''HHHHHH", "'HHHHHH"); /* Odd use */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("'123'tt", ""); /* TIME_NOTIMEMARKER drops literals too */
  ret = GetTimeFormatA(lcid, TIME_NOTIMEMARKER, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  curtime.wHour = 25;
  STRINGSA("'123'tt", ""); /* Invalid time */
  SetLastError(0xdeadbeef);
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  curtime.wHour = 12;
  curtime.wMonth = 60; /* Invalid */
  STRINGSA("h:m:s", "12:56:13"); /* Invalid date */
  ret = GetTimeFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;
}