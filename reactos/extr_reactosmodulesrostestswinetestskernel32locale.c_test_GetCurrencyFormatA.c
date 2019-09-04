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
struct TYPE_4__ {int NumDigits; int LeadingZero; int Grouping; int NegativeOrder; char* lpDecimalSep; char* lpThousandSep; char* lpCurrencySymbol; int /*<<< orphan*/  PositiveOrder; } ;
typedef  int /*<<< orphan*/  LCID ;
typedef  TYPE_1__ CURRENCYFMTA ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int COUNTOF (char*) ; 
 int /*<<< orphan*/  CY_POS_LEFT ; 
 int /*<<< orphan*/  CY_POS_LEFT_SPACE ; 
 int /*<<< orphan*/  CY_POS_RIGHT ; 
 int /*<<< orphan*/  CY_POS_RIGHT_SPACE ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_FLAGS ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EXPECT_EQA ; 
 int /*<<< orphan*/  EXPECT_LENA ; 
 int GetCurrencyFormatA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUO ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  STRINGSA (char*,char*) ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_GetCurrencyFormatA(void)
{
  static char szDot[] = { '.', '\0' };
  static char szComma[] = { ',', '\0' };
  static char szDollar[] = { '$', '\0' };
  int ret;
  LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
  char buffer[BUFFER_SIZE], Expected[BUFFER_SIZE], input[BUFFER_SIZE];
  CURRENCYFMTA format;

  memset(&format, 0, sizeof(format));

  STRINGSA("23",""); /* NULL output, length > 0 --> Error */
  SetLastError(0xdeadbeef);
  ret = GetCurrencyFormatA(lcid, 0, input, NULL, NULL, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("23,53",""); /* Invalid character --> Error */
  SetLastError(0xdeadbeef);
  ret = GetCurrencyFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("--",""); /* Double '-' --> Error */
  SetLastError(0xdeadbeef);
  ret = GetCurrencyFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("0-",""); /* Trailing '-' --> Error */
  SetLastError(0xdeadbeef);
  ret = GetCurrencyFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("0..",""); /* Double '.' --> Error */
  SetLastError(0xdeadbeef);
  ret = GetCurrencyFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA(" 0.1",""); /* Leading space --> Error */
  SetLastError(0xdeadbeef);
  ret = GetCurrencyFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("1234","$"); /* Length too small --> Write up to length chars */
  SetLastError(0xdeadbeef);
  ret = GetCurrencyFormatA(lcid, NUO, input, NULL, buffer, 2);
  ok( !ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
      "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());

  STRINGSA("2353",""); /* Format and flags given --> Error */
  SetLastError(0xdeadbeef);
  ret = GetCurrencyFormatA(lcid, NUO, input, &format, buffer, COUNTOF(buffer));
  ok( !ret, "Expected ret == 0, got %d\n", ret);
  ok( GetLastError() == ERROR_INVALID_FLAGS || GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());

  STRINGSA("2353",""); /* Invalid format --> Error */
  SetLastError(0xdeadbeef);
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("2353","$2,353.00"); /* Valid number */
  ret = GetCurrencyFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("-2353","($2,353.00)"); /* Valid negative number */
  ret = GetCurrencyFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("2353.1","$2,353.10"); /* Valid real number */
  ret = GetCurrencyFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("2353.111","$2,353.11"); /* Too many DP --> Truncated */
  ret = GetCurrencyFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("2353.119","$2,353.12");  /* Too many DP --> Rounded */
  ret = GetCurrencyFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NumDigits = 0; /* No decimal separator */
  format.LeadingZero = 0;
  format.Grouping = 0;  /* No grouping char */
  format.NegativeOrder = 0;
  format.PositiveOrder = CY_POS_LEFT;
  format.lpDecimalSep = szDot;
  format.lpThousandSep = szComma;
  format.lpCurrencySymbol = szDollar;

  STRINGSA("2353","$2353"); /* No decimal or grouping chars expected */
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NumDigits = 1; /* 1 DP --> Expect decimal separator */
  STRINGSA("2353","$2353.0");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.Grouping = 2; /* Group by 100's */
  STRINGSA("2353","$23,53.0");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("235","$235.0"); /* Grouping of a positive number */
  format.Grouping = 3;
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("-235","$-235.0"); /* Grouping of a negative number */
  format.NegativeOrder = 2;
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.LeadingZero = 1; /* Always provide leading zero */
  STRINGSA(".5","$0.5");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.PositiveOrder = CY_POS_RIGHT;
  STRINGSA("1","1.0$");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.PositiveOrder = CY_POS_LEFT_SPACE;
  STRINGSA("1","$ 1.0");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.PositiveOrder = CY_POS_RIGHT_SPACE;
  STRINGSA("1","1.0 $");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 0;
  STRINGSA("-1","($1.0)");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 1;
  STRINGSA("-1","-$1.0");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 2;
  STRINGSA("-1","$-1.0");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 3;
  STRINGSA("-1","$1.0-");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 4;
  STRINGSA("-1","(1.0$)");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 5;
  STRINGSA("-1","-1.0$");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 6;
  STRINGSA("-1","1.0-$");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 7;
  STRINGSA("-1","1.0$-");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 8;
  STRINGSA("-1","-1.0 $");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 9;
  STRINGSA("-1","-$ 1.0");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 10;
  STRINGSA("-1","1.0 $-");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 11;
  STRINGSA("-1","$ 1.0-");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 12;
  STRINGSA("-1","$ -1.0");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 13;
  STRINGSA("-1","1.0- $");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 14;
  STRINGSA("-1","($ 1.0)");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = 15;
  STRINGSA("-1","(1.0 $)");
  ret = GetCurrencyFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;
}