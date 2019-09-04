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
typedef  int /*<<< orphan*/  format ;
typedef  char WCHAR ;
struct TYPE_4__ {int NumDigits; int LeadingZero; int Grouping; char* lpDecimalSep; char* lpThousandSep; void* NegativeOrder; } ;
typedef  TYPE_1__ NUMBERFMTW ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int COUNTOF (char*) ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_FLAGS ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EXPECT_EQW ; 
 int /*<<< orphan*/  EXPECT_LENW ; 
 int /*<<< orphan*/  GetLastError () ; 
 void* NEG_LEFT ; 
 void* NEG_LEFT_SPACE ; 
 void* NEG_PARENS ; 
 void* NEG_RIGHT ; 
 void* NEG_RIGHT_SPACE ; 
 int /*<<< orphan*/  NUO ; 
 int /*<<< orphan*/  STRINGSW (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pGetNumberFormatEx (char const*,int /*<<< orphan*/ ,char*,TYPE_1__*,char*,int) ; 
 scalar_t__ pIsValidLocaleName (char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetNumberFormatEx(void)
{
  int ret;
  NUMBERFMTW format;
  static WCHAR dotW[] = {'.',0};
  static WCHAR commaW[] = {',',0};
  static const WCHAR enW[] = {'e','n','-','U','S',0};
  static const WCHAR frW[] = {'f','r','-','F','R',0};
  static const WCHAR bogusW[] = {'b','o','g','u','s',0};
  WCHAR buffer[BUFFER_SIZE], input[BUFFER_SIZE], Expected[BUFFER_SIZE];

  if (!pGetNumberFormatEx)
  {
    win_skip("GetNumberFormatEx is not available.\n");
    return;
  }

  STRINGSW("23",""); /* NULL output, length > 0 --> Error */
  ret = pGetNumberFormatEx(enW, 0, input, NULL, NULL, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSW("23,53",""); /* Invalid character --> Error */
  ret = pGetNumberFormatEx(enW, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSW("--",""); /* Double '-' --> Error */
  ret = pGetNumberFormatEx(enW, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSW("0-",""); /* Trailing '-' --> Error */
  ret = pGetNumberFormatEx(enW, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSW("0..",""); /* Double '.' --> Error */
  ret = pGetNumberFormatEx(enW, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSW(" 0.1",""); /* Leading space --> Error */
  ret = pGetNumberFormatEx(enW, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSW("1234","1"); /* Length too small --> Write up to length chars */
  ret = pGetNumberFormatEx(enW, NUO, input, NULL, buffer, 2);
  ok( !ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
      "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());

  STRINGSW("23",""); /* Bogus locale --> Error */
  ret = pGetNumberFormatEx(bogusW, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  memset(&format, 0, sizeof(format));

  STRINGSW("2353",""); /* Format and flags given --> Error */
  ret = pGetNumberFormatEx(enW, NUO, input, &format, buffer, COUNTOF(buffer));
  ok( !ret, "Expected ret == 0, got %d\n", ret);
  ok( GetLastError() == ERROR_INVALID_FLAGS || GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());

  STRINGSW("2353",""); /* Invalid format --> Error */
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSW("2353","2,353.00"); /* Valid number */
  ret = pGetNumberFormatEx(enW, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("-2353","-2,353.00"); /* Valid negative number */
  ret = pGetNumberFormatEx(enW, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("-353","-353.00"); /* test for off by one error in grouping */
  ret = pGetNumberFormatEx(enW, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("2353.1","2,353.10"); /* Valid real number */
  ret = pGetNumberFormatEx(enW, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("2353.111","2,353.11"); /* Too many DP --> Truncated */
  ret = pGetNumberFormatEx(enW, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("2353.119","2,353.12");  /* Too many DP --> Rounded */
  ret = pGetNumberFormatEx(enW, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  format.NumDigits = 0; /* No decimal separator */
  format.LeadingZero = 0;
  format.Grouping = 0;  /* No grouping char */
  format.NegativeOrder = 0;
  format.lpDecimalSep = dotW;
  format.lpThousandSep = commaW;

  STRINGSW("2353","2353"); /* No decimal or grouping chars expected */
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  format.NumDigits = 1; /* 1 DP --> Expect decimal separator */
  STRINGSW("2353","2353.0");
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  format.Grouping = 2; /* Group by 100's */
  STRINGSW("2353","23,53.0");
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("235","235.0"); /* Grouping of a positive number */
  format.Grouping = 3;
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  STRINGSW("-235","-235.0"); /* Grouping of a negative number */
  format.NegativeOrder = NEG_LEFT;
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  format.LeadingZero = 1; /* Always provide leading zero */
  STRINGSW(".5","0.5");
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  format.NegativeOrder = NEG_PARENS;
  STRINGSW("-1","(1.0)");
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  format.NegativeOrder = NEG_LEFT;
  STRINGSW("-1","-1.0");
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  format.NegativeOrder = NEG_LEFT_SPACE;
  STRINGSW("-1","- 1.0");
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  format.NegativeOrder = NEG_RIGHT;
  STRINGSW("-1","1.0-");
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  format.NegativeOrder = NEG_RIGHT_SPACE;
  STRINGSW("-1","1.0 -");
  ret = pGetNumberFormatEx(enW, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENW; EXPECT_EQW;

  if (pIsValidLocaleName(frW))
  {
    STRINGSW("-12345","-12 345,00"); /* Try French formatting */
    Expected[3] = 160; /* Non breaking space */
    ret = pGetNumberFormatEx(frW, NUO, input, NULL, buffer, COUNTOF(buffer));
    ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
    EXPECT_LENW; EXPECT_EQW;
  }
}