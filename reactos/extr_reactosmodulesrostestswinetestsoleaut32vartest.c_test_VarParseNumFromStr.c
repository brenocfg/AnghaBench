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
typedef  int /*<<< orphan*/  NUMPARSE ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONVERT (char*,int) ; 
 int /*<<< orphan*/  CONVERTN (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  EXPECT2 (int,int) ; 
 int /*<<< orphan*/  EXPECTFAIL ; 
 int /*<<< orphan*/  EXPECTRGB (int,int) ; 
 int FAILDIG ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUMPRS_CURRENCY ; 
 int NUMPRS_DECIMAL ; 
 int NUMPRS_EXPONENT ; 
 int NUMPRS_HEX_OCT ; 
 int NUMPRS_INEXACT ; 
 int NUMPRS_LEADING_MINUS ; 
 int NUMPRS_LEADING_PLUS ; 
 int NUMPRS_LEADING_WHITE ; 
 int NUMPRS_NEG ; 
 int NUMPRS_PARENS ; 
 int NUMPRS_STD ; 
 int NUMPRS_THOUSANDS ; 
 int NUMPRS_TRAILING_MINUS ; 
 int NUMPRS_TRAILING_PLUS ; 
 int NUMPRS_TRAILING_WHITE ; 
 int NUMPRS_USE_ALL ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  VarParseNumFromStr ; 

__attribute__((used)) static void test_VarParseNumFromStr(void)
{
  HRESULT hres;
  /* Ensure all tests are using the same locale characters for '$', ',' etc */
  LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);
  NUMPARSE np;
  BYTE rgb[128];

  /** No flags **/

  CHECKPTR(VarParseNumFromStr);

  /* Consume a single digit */
  CONVERT("7", 0);
  EXPECT(1,0,0,1,0,0);
  EXPECT2(7,FAILDIG);

  /* cDig is not literal digits - zeros are suppressed and nPwr10 is increased */
  CONVERT("10", 0);
  EXPECT(1,0,0,2,0,1);
  /* Note: Win32 writes the trailing zeros if they are within cDig's limits,
   * but then excludes them from the returned cDig count.
   * In our implementation we don't bother writing them at all.
   */
  EXPECTRGB(0, 1);

  /* if cDig is too small and numbers follow, sets INEXACT */
  CONVERTN("11",1, 0);
  EXPECT(1,0,NUMPRS_INEXACT,2,0,1);
  EXPECT2(1,FAILDIG);

  /* Strips leading zeros */
  CONVERT("01", 0);
  EXPECT(1,0,0,2,0,0);
  EXPECT2(1,FAILDIG);

  /* Strips leading zeros */
  CONVERTN("01",1, 0);
  EXPECT(1,0,0,2,0,0);
  EXPECT2(1,FAILDIG);


  /* Fails on non digits */
  CONVERT("a", 0);
  EXPECTFAIL;
  EXPECTRGB(0,FAILDIG);

  /** NUMPRS_LEADING_WHITE/NUMPRS_TRAILING_WHITE **/

  /* Without flag, fails on whitespace */
  CONVERT(" 0", 0);
  EXPECTFAIL;
  EXPECTRGB(0,FAILDIG);


  /* With flag, consumes whitespace */
  CONVERT(" 0", NUMPRS_LEADING_WHITE);
  EXPECT(1,NUMPRS_LEADING_WHITE,NUMPRS_LEADING_WHITE,2,0,0);
  EXPECT2(0,FAILDIG);

  /* Test TAB once, then assume it acts as space for all cases */
  CONVERT("\t0", NUMPRS_LEADING_WHITE);
  EXPECT(1,NUMPRS_LEADING_WHITE,NUMPRS_LEADING_WHITE,2,0,0);
  EXPECT2(0,FAILDIG);


  /* Doesn't pick up trailing whitespace without flag */
  CONVERT("0 ", 0);
  EXPECT(1,0,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* With flag, consumes trailing whitespace */
  CONVERT("0 ", NUMPRS_TRAILING_WHITE);
  EXPECT(1,NUMPRS_TRAILING_WHITE,NUMPRS_TRAILING_WHITE,2,0,0);
  EXPECT2(0,FAILDIG);

  /* Leading flag only consumes leading */
  CONVERT(" 0 ", NUMPRS_LEADING_WHITE);
  EXPECT(1,NUMPRS_LEADING_WHITE,NUMPRS_LEADING_WHITE,2,0,0);
  EXPECT2(0,FAILDIG);

  /* Both flags consumes both */
  CONVERT(" 0 ", NUMPRS_LEADING_WHITE|NUMPRS_TRAILING_WHITE);
  EXPECT(1,NUMPRS_LEADING_WHITE|NUMPRS_TRAILING_WHITE,NUMPRS_LEADING_WHITE|NUMPRS_TRAILING_WHITE,3,0,0);
  EXPECT2(0,FAILDIG);

  /** NUMPRS_LEADING_PLUS/NUMPRS_TRAILING_PLUS **/

  /* Without flag, fails on + */
  CONVERT("+0", 0);
  EXPECTFAIL;
  EXPECTRGB(0,FAILDIG);

  /* With flag, consumes + */
  CONVERT("+0", NUMPRS_LEADING_PLUS);
  EXPECT(1,NUMPRS_LEADING_PLUS,NUMPRS_LEADING_PLUS,2,0,0);
  EXPECT2(0,FAILDIG);

  /* Without flag, doesn't consume trailing + */
  CONVERT("0+", 0);
  EXPECT(1,0,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* With flag, consumes trailing + */
  CONVERT("0+", NUMPRS_TRAILING_PLUS);
  EXPECT(1,NUMPRS_TRAILING_PLUS,NUMPRS_TRAILING_PLUS,2,0,0);
  EXPECT2(0,FAILDIG);

  /* With leading flag, doesn't consume trailing + */
  CONVERT("+0+", NUMPRS_LEADING_PLUS);
  EXPECT(1,NUMPRS_LEADING_PLUS,NUMPRS_LEADING_PLUS,2,0,0);
  EXPECT2(0,FAILDIG);

  /* Trailing + doesn't get consumed if we specify both (unlike whitespace) */
  CONVERT("+0+", NUMPRS_LEADING_PLUS|NUMPRS_TRAILING_PLUS);
  EXPECT(1,NUMPRS_LEADING_PLUS|NUMPRS_TRAILING_PLUS,NUMPRS_LEADING_PLUS,2,0,0);
  EXPECT2(0,FAILDIG);

  /** NUMPRS_LEADING_MINUS/NUMPRS_TRAILING_MINUS **/

  /* Without flag, fails on - */
  CONVERT("-0", 0);
  EXPECTFAIL;
  EXPECTRGB(0,FAILDIG);

  /* With flag, consumes - */
  CONVERT("-0", NUMPRS_LEADING_MINUS);
  EXPECT(1,NUMPRS_LEADING_MINUS,NUMPRS_NEG|NUMPRS_LEADING_MINUS,2,0,0);
  EXPECT2(0,FAILDIG);

  /* Without flag, doesn't consume trailing - */
  CONVERT("0-", 0);
  EXPECT(1,0,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* With flag, consumes trailing - */
  CONVERT("0-", NUMPRS_TRAILING_MINUS);
  EXPECT(1,NUMPRS_TRAILING_MINUS,NUMPRS_NEG|NUMPRS_TRAILING_MINUS,2,0,0);
  EXPECT2(0,FAILDIG);

  /* With leading flag, doesn't consume trailing - */
  CONVERT("-0-", NUMPRS_LEADING_MINUS);
  EXPECT(1,NUMPRS_LEADING_MINUS,NUMPRS_NEG|NUMPRS_LEADING_MINUS,2,0,0);
  EXPECT2(0,FAILDIG);

  /* Trailing - doesn't get consumed if we specify both (unlike whitespace) */
  CONVERT("-0-", NUMPRS_LEADING_MINUS|NUMPRS_TRAILING_MINUS);
  EXPECT(1,NUMPRS_LEADING_MINUS|NUMPRS_TRAILING_MINUS,NUMPRS_NEG|NUMPRS_LEADING_MINUS,2,0,0);
  EXPECT2(0,FAILDIG);

  /** NUMPRS_HEX_OCT **/

  /* Could be hex, octal or decimal - With flag reads as decimal */
  CONVERT("0", NUMPRS_HEX_OCT);
  EXPECT(1,NUMPRS_HEX_OCT,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* Doesn't recognise hex in .asm syntax */
  CONVERT("0h", NUMPRS_HEX_OCT);
  EXPECT(1,NUMPRS_HEX_OCT,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* Doesn't fail with valid leading string but no digits */
  CONVERT("0x", NUMPRS_HEX_OCT);
  EXPECT(1,NUMPRS_HEX_OCT,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* Doesn't recognise hex format numbers at all! */
  CONVERT("0x0", NUMPRS_HEX_OCT);
  EXPECT(1,NUMPRS_HEX_OCT,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* Doesn't recognise plain hex digits either */
  CONVERT("FE", NUMPRS_HEX_OCT);
  EXPECTFAIL;
  EXPECTRGB(0,FAILDIG);

  /* Octal */
  CONVERT("0100", NUMPRS_HEX_OCT);
  EXPECT(1,NUMPRS_HEX_OCT,0,4,0,2);
  EXPECTRGB(0,1);
  EXPECTRGB(1,0);
  EXPECTRGB(2,0);
  EXPECTRGB(3,FAILDIG);

  /* VB hex */
  CONVERT("&HF800", NUMPRS_HEX_OCT);
  EXPECT(4,NUMPRS_HEX_OCT,0x40,6,4,0);
  EXPECTRGB(0,15);
  EXPECTRGB(1,8);
  EXPECTRGB(2,0);
  EXPECTRGB(3,0);
  EXPECTRGB(4,FAILDIG);

  /* VB hex lower case and leading zero */
  CONVERT("&h0abcdef", NUMPRS_HEX_OCT);
  EXPECT(6,NUMPRS_HEX_OCT,0x40,9,4,0);
  EXPECTRGB(0,10);
  EXPECTRGB(1,11);
  EXPECTRGB(2,12);
  EXPECTRGB(3,13);
  EXPECTRGB(4,14);
  EXPECTRGB(5,15);
  EXPECTRGB(6,FAILDIG);

  /* VB oct */
  CONVERT("&O300", NUMPRS_HEX_OCT);
  EXPECT(3,NUMPRS_HEX_OCT,0x40,5,3,0);
  EXPECTRGB(0,3);
  EXPECTRGB(1,0);
  EXPECTRGB(2,0);
  EXPECTRGB(3,FAILDIG);

  /* VB oct lower case and leading zero */
  CONVERT("&o0777", NUMPRS_HEX_OCT);
  EXPECT(3,NUMPRS_HEX_OCT,0x40,6,3,0);
  EXPECTRGB(0,7);
  EXPECTRGB(1,7);
  EXPECTRGB(2,7);
  EXPECTRGB(3,FAILDIG);

  /* VB oct char bigger than 7 */
  CONVERT("&o128", NUMPRS_HEX_OCT);
  EXPECT(2,NUMPRS_HEX_OCT,0x40,4,3,0);
  EXPECTRGB(0,1);
  EXPECTRGB(1,2);
  EXPECTRGB(3,FAILDIG);

  /** NUMPRS_PARENS **/

  /* Empty parens = error */
  CONVERT("()", NUMPRS_PARENS);
  EXPECTFAIL;
  EXPECTRGB(0,FAILDIG);

  /* With flag, trailing parens not consumed */
  CONVERT("0()", NUMPRS_PARENS);
  EXPECT(1,NUMPRS_PARENS,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* With flag, Number in parens made negative and parens consumed */
  CONVERT("(0)", NUMPRS_PARENS);
  EXPECT(1,NUMPRS_PARENS,NUMPRS_NEG|NUMPRS_PARENS,3,0,0);
  EXPECT2(0,FAILDIG);

  /** NUMPRS_THOUSANDS **/

  /* With flag, thousands sep. not needed */
  CONVERT("0", NUMPRS_THOUSANDS);
  EXPECT(1,NUMPRS_THOUSANDS,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* With flag, thousands sep. and following digits consumed */
  CONVERT("1,000", NUMPRS_THOUSANDS);
  EXPECT(1,NUMPRS_THOUSANDS,NUMPRS_THOUSANDS,5,0,3);
  EXPECTRGB(0,1);

  /* With flag and decimal point, thousands sep. but not decimals consumed */
  CONVERT("1,000.0", NUMPRS_THOUSANDS);
  EXPECT(1,NUMPRS_THOUSANDS,NUMPRS_THOUSANDS,5,0,3);
  EXPECTRGB(0,1);

  /** NUMPRS_CURRENCY **/

  /* Without flag, chokes on currency sign */
  CONVERT("$11", 0);
  EXPECTFAIL;
  EXPECTRGB(0,FAILDIG);

  /* With flag, consumes currency sign */
  CONVERT("$11", NUMPRS_CURRENCY);
  EXPECT(2,NUMPRS_CURRENCY,NUMPRS_CURRENCY,3,0,0);
  EXPECT2(1,1);
  EXPECTRGB(2,FAILDIG);

  /* With flag only, doesn't consume decimal point */
  CONVERT("$11.1", NUMPRS_CURRENCY);
  EXPECT(2,NUMPRS_CURRENCY,NUMPRS_CURRENCY,3,0,0);
  EXPECT2(1,1);
  EXPECTRGB(2,FAILDIG);

  /* With flag and decimal flag, consumes decimal point and following digits */
  CONVERT("$11.1", NUMPRS_CURRENCY|NUMPRS_DECIMAL);
  EXPECT(3,NUMPRS_CURRENCY|NUMPRS_DECIMAL,NUMPRS_CURRENCY|NUMPRS_DECIMAL,5,0,-1);
  EXPECT2(1,1);
  EXPECTRGB(2,1);
  EXPECTRGB(3,FAILDIG);

  /* Thousands flag can only be used with currency */
  CONVERT("$1,234", NUMPRS_CURRENCY|NUMPRS_THOUSANDS);
  EXPECT(4,NUMPRS_CURRENCY|NUMPRS_THOUSANDS,NUMPRS_CURRENCY|NUMPRS_THOUSANDS,6,0,0);
  EXPECT2(1,2);
  EXPECTRGB(2,3);
  EXPECTRGB(3,4);
  EXPECTRGB(4,FAILDIG);

  /** NUMPRS_DECIMAL **/

  /* With flag, consumes decimal point */
  CONVERT("1.1", NUMPRS_DECIMAL);
  EXPECT(2,NUMPRS_DECIMAL,NUMPRS_DECIMAL,3,0,-1);
  EXPECT2(1,1);
  EXPECTRGB(2,FAILDIG);

  /* With flag, consumes decimal point. Skipping the decimal part is not an error */
  CONVERT("1.", NUMPRS_DECIMAL);
  EXPECT(1,NUMPRS_DECIMAL,NUMPRS_DECIMAL,2,0,0);
  EXPECT2(1,FAILDIG);

  /* Consumes only one decimal point */
  CONVERT("1.1.", NUMPRS_DECIMAL);
  EXPECT(2,NUMPRS_DECIMAL,NUMPRS_DECIMAL,3,0,-1);
  EXPECT2(1,1);
  EXPECTRGB(2,FAILDIG);

  /** NUMPRS_EXPONENT **/

  /* Without flag, doesn't consume exponent */
  CONVERT("1e1", 0);
  EXPECT(1,0,0,1,0,0);
  EXPECT2(1,FAILDIG);

  /* With flag, consumes exponent */
  CONVERT("1e1", NUMPRS_EXPONENT);
  EXPECT(1,NUMPRS_EXPONENT,NUMPRS_EXPONENT,3,0,1);
  EXPECT2(1,FAILDIG);

  /* Negative exponents are accepted without flags */
  CONVERT("1e-1", NUMPRS_EXPONENT);
  EXPECT(1,NUMPRS_EXPONENT,NUMPRS_EXPONENT,4,0,-1);
  EXPECT2(1,FAILDIG);

  /* As are positive exponents and leading exponent 0s */
  CONVERT("1e+01", NUMPRS_EXPONENT);
  EXPECT(1,NUMPRS_EXPONENT,NUMPRS_EXPONENT,5,0,1);
  EXPECT2(1,FAILDIG);

  /* The same for zero exponents */
  CONVERT("1e0", NUMPRS_EXPONENT);
  EXPECT(1,NUMPRS_EXPONENT,NUMPRS_EXPONENT,3,0,0);
  EXPECT2(1,FAILDIG);

  /* Sign on a zero exponent doesn't matter */
  CONVERT("1e+0", NUMPRS_EXPONENT);
  EXPECT(1,NUMPRS_EXPONENT,NUMPRS_EXPONENT,4,0,0);
  EXPECT2(1,FAILDIG);

  CONVERT("1e-0", NUMPRS_EXPONENT);
  EXPECT(1,NUMPRS_EXPONENT,NUMPRS_EXPONENT,4,0,0);
  EXPECT2(1,FAILDIG);

  /* Doesn't consume a real number exponent */
  CONVERT("1e1.", NUMPRS_EXPONENT);
  EXPECT(1,NUMPRS_EXPONENT,NUMPRS_EXPONENT,3,0,1);
  EXPECT2(1,FAILDIG);

  /* Powers of 10 are calculated from the position of any decimal point */
  CONVERT("1.5e20", NUMPRS_EXPONENT|NUMPRS_DECIMAL);
  EXPECT(2,NUMPRS_EXPONENT|NUMPRS_DECIMAL,NUMPRS_EXPONENT|NUMPRS_DECIMAL,6,0,19);
  EXPECT2(1,5);

  CONVERT("1.5e-20", NUMPRS_EXPONENT|NUMPRS_DECIMAL);
  EXPECT(2,NUMPRS_EXPONENT|NUMPRS_DECIMAL,NUMPRS_EXPONENT|NUMPRS_DECIMAL,7,0,-21);
  EXPECT2(1,5);

  /** NUMPRS_USE_ALL **/

  /* Flag expects all digits */
  CONVERT("0", NUMPRS_USE_ALL);
  EXPECT(1,NUMPRS_USE_ALL,0,1,0,0);
  EXPECT2(0,FAILDIG);

  /* Rejects anything trailing */
  CONVERT("0 ", NUMPRS_USE_ALL);
  EXPECTFAIL;
  EXPECT2(0,FAILDIG);

  /* Unless consumed by trailing flag */
  CONVERT("0 ", NUMPRS_USE_ALL|NUMPRS_TRAILING_WHITE);
  EXPECT(1,NUMPRS_USE_ALL|NUMPRS_TRAILING_WHITE,NUMPRS_TRAILING_WHITE,2,0,0);
  EXPECT2(0,FAILDIG);

  /** Combinations **/

  /* Leading whitespace and plus, doesn't consume trailing whitespace */
  CONVERT("+ 0 ", NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE);
  EXPECT(1,NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE,NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE,3,0,0);
  EXPECT2(0,FAILDIG);

  /* Order of whitespace and plus is unimportant */
  CONVERT(" +0", NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE);
  EXPECT(1,NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE,NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE,3,0,0);
  EXPECT2(0,FAILDIG);

  /* Leading whitespace can be repeated */
  CONVERT(" + 0", NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE);
  EXPECT(1,NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE,NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE,4,0,0);
  EXPECT2(0,FAILDIG);

  /* But plus/minus etc. cannot */
  CONVERT("+ +0", NUMPRS_LEADING_PLUS|NUMPRS_LEADING_WHITE);
  EXPECTFAIL;
  EXPECTRGB(0,FAILDIG);

  /* Inexact is not set if trailing zeros are removed */
  CONVERTN("10", 1, 0);
  EXPECT(1,0,0,2,0,1);
  EXPECT2(1,FAILDIG);

  /* Make sure a leading 0 is stripped but decimals after it get read */
  CONVERT("-0.51", NUMPRS_STD);
  EXPECT(2,NUMPRS_STD,NUMPRS_NEG|NUMPRS_DECIMAL|NUMPRS_LEADING_MINUS,5,0,-2);
  EXPECT2(5,1);

  /* Keep trailing zeros on whole number part of a decimal */
  CONVERT("10.1", NUMPRS_STD);
  EXPECT(3,NUMPRS_STD,NUMPRS_DECIMAL,4,0,-1);
  EXPECT2(1,0);
  EXPECTRGB(2,1);

  /* Zeros after decimal sign */
  CONVERT("0.01", NUMPRS_STD);
  EXPECT(1,NUMPRS_STD,NUMPRS_DECIMAL,4,0,-2);
  EXPECT2(1,FAILDIG);

  /* Trailing zeros after decimal part */
  CONVERT("0.10", NUMPRS_STD);
  EXPECT(1,NUMPRS_STD,NUMPRS_DECIMAL,4,0,-1);
  EXPECT2(1,0);
}