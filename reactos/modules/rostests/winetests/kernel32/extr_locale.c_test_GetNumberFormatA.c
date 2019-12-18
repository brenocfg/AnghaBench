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
struct TYPE_4__ {int NumDigits; int LeadingZero; int Grouping; char* lpDecimalSep; char* lpThousandSep; void* NegativeOrder; } ;
typedef  TYPE_1__ NUMBERFMTA ;
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
 int GetNumberFormatA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,char*,int) ; 
 scalar_t__ IsValidLocale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_FRENCH ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* NEG_LEFT ; 
 void* NEG_LEFT_SPACE ; 
 void* NEG_PARENS ; 
 void* NEG_RIGHT ; 
 void* NEG_RIGHT_SPACE ; 
 int /*<<< orphan*/  NUO ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  STRINGSA (char*,char*) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_GetNumberFormatA(void)
{
  static char szDot[] = { '.', '\0' };
  static char szComma[] = { ',', '\0' };
  int ret;
  LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
  char buffer[BUFFER_SIZE], Expected[BUFFER_SIZE], input[BUFFER_SIZE];
  NUMBERFMTA format;

  memset(&format, 0, sizeof(format));

  STRINGSA("23",""); /* NULL output, length > 0 --> Error */
  SetLastError(0xdeadbeef);
  ret = GetNumberFormatA(lcid, 0, input, NULL, NULL, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("23,53",""); /* Invalid character --> Error */
  SetLastError(0xdeadbeef);
  ret = GetNumberFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("--",""); /* Double '-' --> Error */
  SetLastError(0xdeadbeef);
  ret = GetNumberFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("0-",""); /* Trailing '-' --> Error */
  SetLastError(0xdeadbeef);
  ret = GetNumberFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("0..",""); /* Double '.' --> Error */
  SetLastError(0xdeadbeef);
  ret = GetNumberFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA(" 0.1",""); /* Leading space --> Error */
  SetLastError(0xdeadbeef);
  ret = GetNumberFormatA(lcid, 0, input, NULL, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("1234","1"); /* Length too small --> Write up to length chars */
  SetLastError(0xdeadbeef);
  ret = GetNumberFormatA(lcid, NUO, input, NULL, buffer, 2);
  ok( !ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
      "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());

  STRINGSA("2353",""); /* Format and flags given --> Error */
  SetLastError(0xdeadbeef);
  ret = GetNumberFormatA(lcid, NUO, input, &format, buffer, COUNTOF(buffer));
  ok( !ret, "Expected ret == 0, got %d\n", ret);
  ok( GetLastError() == ERROR_INVALID_FLAGS || GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_FLAGS, got %d\n", GetLastError());

  STRINGSA("2353",""); /* Invalid format --> Error */
  SetLastError(0xdeadbeef);
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

  STRINGSA("2353","2,353.00"); /* Valid number */
  ret = GetNumberFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("-2353","-2,353.00"); /* Valid negative number */
  ret = GetNumberFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("-353","-353.00"); /* test for off by one error in grouping */
  ret = GetNumberFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("2353.1","2,353.10"); /* Valid real number */
  ret = GetNumberFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("2353.111","2,353.11"); /* Too many DP --> Truncated */
  ret = GetNumberFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("2353.119","2,353.12");  /* Too many DP --> Rounded */
  ret = GetNumberFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NumDigits = 0; /* No decimal separator */
  format.LeadingZero = 0;
  format.Grouping = 0;  /* No grouping char */
  format.NegativeOrder = 0;
  format.lpDecimalSep = szDot;
  format.lpThousandSep = szComma;

  STRINGSA("2353","2353"); /* No decimal or grouping chars expected */
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NumDigits = 1; /* 1 DP --> Expect decimal separator */
  STRINGSA("2353","2353.0");
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.Grouping = 2; /* Group by 100's */
  STRINGSA("2353","23,53.0");
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("235","235.0"); /* Grouping of a positive number */
  format.Grouping = 3;
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  STRINGSA("-235","-235.0"); /* Grouping of a negative number */
  format.NegativeOrder = NEG_LEFT;
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.LeadingZero = 1; /* Always provide leading zero */
  STRINGSA(".5","0.5");
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = NEG_PARENS;
  STRINGSA("-1","(1.0)");
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = NEG_LEFT;
  STRINGSA("-1","-1.0");
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = NEG_LEFT_SPACE;
  STRINGSA("-1","- 1.0");
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = NEG_RIGHT;
  STRINGSA("-1","1.0-");
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  format.NegativeOrder = NEG_RIGHT_SPACE;
  STRINGSA("-1","1.0 -");
  ret = GetNumberFormatA(lcid, 0, input, &format, buffer, COUNTOF(buffer));
  ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
  EXPECT_LENA; EXPECT_EQA;

  lcid = MAKELCID(MAKELANGID(LANG_FRENCH, SUBLANG_DEFAULT), SORT_DEFAULT);

  if (IsValidLocale(lcid, 0))
  {
    STRINGSA("-12345","-12 345,00"); /* Try French formatting */
    Expected[3] = 160; /* Non breaking space */
    ret = GetNumberFormatA(lcid, NUO, input, NULL, buffer, COUNTOF(buffer));
    ok(ret, "Expected ret != 0, got %d, error %d\n", ret, GetLastError());
    EXPECT_LENA; EXPECT_EQA;
  }
}