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
struct TYPE_4__ {int wYear; int wMonth; int wDay; int wDayOfWeek; int wHour; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  LCID ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int COUNTOF (char*) ; 
 int DATE_LONGDATE ; 
 int DATE_SHORTDATE ; 
 int DATE_YEARMONTH ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_FLAGS ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EXPECT_EQA ; 
 int /*<<< orphan*/  EXPECT_LENA ; 
 int GetDateFormatA (int /*<<< orphan*/ ,int,TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_RUSSIAN ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUO ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  STRINGSA (char*,char*) ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetDateFormatA(void)
{
  int ret;
  SYSTEMTIME  curtime;
  LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
  LCID lcid_ru = MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_NEUTRAL), SORT_DEFAULT);
  char buffer[BUFFER_SIZE], input[BUFFER_SIZE], Expected[BUFFER_SIZE];
  char Broken[BUFFER_SIZE];
  char short_day[10], month[10], genitive_month[10];

  memset(&curtime, 2, sizeof(SYSTEMTIME)); /* Invalid time */
  STRINGSA("ddd',' MMM dd yy","");
  SetLastError(0xdeadbeef);
  ret = GetDateFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  curtime.wYear = 2002;
  curtime.wMonth = 5;
  curtime.wDay = 4;
  curtime.wDayOfWeek = 3;
  STRINGSA("ddd',' MMM dd yy","Sat, May 04 02"); /* Simple case */
  ret = GetDateFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  /* Same as above but with LOCALE_NOUSEROVERRIDE */
  STRINGSA("ddd',' MMM dd yy",""); /* Simple case */
  SetLastError(0xdeadbeef);
  ret = GetDateFormatA(lcid, NUO, &curtime, input, buffer, COUNTOF(buffer));
  ok(!ret && GetLastError() == ERROR_INVALID_FLAGS,
     "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());
  EXPECT_EQA;

  STRINGSA("ddd',' MMM dd yy","Sat, May 04 02"); /* Format containing "'" */
  ret = GetDateFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  curtime.wHour = 36; /* Invalid */
  STRINGSA("ddd',' MMM dd ''''yy","Sat, May 04 '02"); /* Invalid time */
  ret = GetDateFormatA(lcid, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("ddd',' MMM dd ''''yy",""); /* Get size only */
  ret = GetDateFormatA(lcid, 0, &curtime, input, NULL, 0);
  ok(ret == 16, "Expected ret == 16, got %d, error %d\n", ret, GetLastError());
  EXPECT_EQA;

  STRINGSA("ddd',' MMM dd ''''yy",""); /* Buffer too small */
  SetLastError(0xdeadbeef);
  ret = GetDateFormatA(lcid, 0, &curtime, input, buffer, 2);
  ok( !ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
      "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());

  STRINGSA("ddd',' MMM dd ''''yy","5/4/2002"); /* Default to DATE_SHORTDATE */
  ret = GetDateFormatA(lcid, NUO, &curtime, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  if (strncmp(buffer, Expected, strlen(Expected)) && strncmp(buffer, "5/4/02", strlen(Expected)) != 0)
	  ok (0, "Expected '%s' or '5/4/02', got '%s'\n", Expected, buffer);

  SetLastError(0xdeadbeef); buffer[0] = '\0'; /* DATE_LONGDATE */
  ret = GetDateFormatA(lcid, NUO|DATE_LONGDATE, &curtime, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  ok(strcmp(buffer, "Saturday, May 04, 2002") == 0 ||
     strcmp(buffer, "Saturday, May 4, 2002") == 0 /* Win 8 */,
     "got an unexpected date string '%s'\n", buffer);

  /* test for expected DATE_YEARMONTH behavior with null format */
  /* NT4 returns ERROR_INVALID_FLAGS for DATE_YEARMONTH */
  STRINGSA("ddd',' MMM dd ''''yy", ""); /* DATE_YEARMONTH */
  SetLastError(0xdeadbeef);
  ret = GetDateFormatA(lcid, NUO|DATE_YEARMONTH, &curtime, input, buffer, COUNTOF(buffer));
  ok(!ret && GetLastError() == ERROR_INVALID_FLAGS,
     "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());
  EXPECT_EQA;

  /* Test that using invalid DATE_* flags results in the correct error */
  /* and return values */
  STRINGSA("m/d/y", ""); /* Invalid flags */
  SetLastError(0xdeadbeef);
  ret = GetDateFormatA(lcid, DATE_YEARMONTH|DATE_SHORTDATE|DATE_LONGDATE,
                      &curtime, input, buffer, COUNTOF(buffer));
  ok(!ret && GetLastError() == ERROR_INVALID_FLAGS,
     "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());

  ret = GetDateFormatA(lcid_ru, 0, &curtime, "ddMMMM", buffer, COUNTOF(buffer));
  if (!ret)
  {
    win_skip("LANG_RUSSIAN locale data unavailable\n");
    return;
  }

  /* month part should be in genitive form */
  strcpy(genitive_month, buffer + 2);
  ret = GetDateFormatA(lcid_ru, 0, &curtime, "MMMM", buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  strcpy(month, buffer);
  ok(strcmp(genitive_month, month) != 0, "Expected different month forms\n");

  ret = GetDateFormatA(lcid_ru, 0, &curtime, "ddd", buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  strcpy(short_day, buffer);

  STRINGSA("dd MMMMddd dd", "");
  sprintf(Expected, "04 %s%s 04", genitive_month, short_day);
  ret = GetDateFormatA(lcid_ru, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_EQA;

  STRINGSA("MMMMddd dd", "");
  sprintf(Expected, "%s%s 04", month, short_day);
  ret = GetDateFormatA(lcid_ru, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_EQA;

  STRINGSA("MMMMddd", "");
  sprintf(Expected, "%s%s", month, short_day);
  ret = GetDateFormatA(lcid_ru, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_EQA;

  STRINGSA("MMMMdd", "");
  sprintf(Expected, "%s04", genitive_month);
  sprintf(Broken, "%s04", month);
  ret = GetDateFormatA(lcid_ru, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  ok(strncmp(buffer, Expected, strlen(Expected)) == 0 ||
     broken(strncmp(buffer, Broken, strlen(Broken)) == 0) /* nt4 */,
     "Expected '%s', got '%s'\n", Expected, buffer);

  STRINGSA("MMMMdd ddd", "");
  sprintf(Expected, "%s04 %s", genitive_month, short_day);
  sprintf(Broken, "%s04 %s", month, short_day);
  ret = GetDateFormatA(lcid_ru, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  ok(strncmp(buffer, Expected, strlen(Expected)) == 0 ||
     broken(strncmp(buffer, Broken, strlen(Broken)) == 0) /* nt4 */,
     "Expected '%s', got '%s'\n", Expected, buffer);

  STRINGSA("dd dddMMMM", "");
  sprintf(Expected, "04 %s%s", short_day, month);
  ret = GetDateFormatA(lcid_ru, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_EQA;

  STRINGSA("dd dddMMMM ddd MMMMdd", "");
  sprintf(Expected, "04 %s%s %s %s04", short_day, month, short_day, genitive_month);
  sprintf(Broken, "04 %s%s %s %s04", short_day, month, short_day, month);
  ret = GetDateFormatA(lcid_ru, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  ok(strncmp(buffer, Expected, strlen(Expected)) == 0 ||
     broken(strncmp(buffer, Broken, strlen(Broken)) == 0) /* nt4 */,
     "Expected '%s', got '%s'\n", Expected, buffer);

  /* with literal part */
  STRINGSA("ddd',' MMMM dd", "");
  sprintf(Expected, "%s, %s 04", short_day, genitive_month);
  sprintf(Broken, "%s, %s 04", short_day, month);
  ret = GetDateFormatA(lcid_ru, 0, &curtime, input, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  ok(strncmp(buffer, Expected, strlen(Expected)) == 0 ||
     broken(strncmp(buffer, Broken, strlen(Broken)) == 0) /* nt4 */,
     "Expected '%s', got '%s'\n", Expected, buffer);
}