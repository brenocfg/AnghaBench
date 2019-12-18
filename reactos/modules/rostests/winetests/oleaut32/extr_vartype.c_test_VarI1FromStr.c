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
typedef  int /*<<< orphan*/  OLECHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_STR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  EXPECT_MISMATCH ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LCID ; 
 int /*<<< orphan*/  LOCALE_NOUSEROVERRIDE ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  VarI1FromStr ; 
 int /*<<< orphan*/  in ; 

__attribute__((used)) static void test_VarI1FromStr(void)
{
  CONVVARS(LCID);
  OLECHAR buff[128];

  in = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);

  CONVERT_STR(VarI1FromStr,NULL, 0);   EXPECT_MISMATCH;
  CONVERT_STR(VarI1FromStr,"0", 0);    EXPECT(0);
  CONVERT_STR(VarI1FromStr,"-129", 0); EXPECT_OVERFLOW;
  CONVERT_STR(VarI1FromStr,"-128", 0); EXPECT(-128);
  CONVERT_STR(VarI1FromStr,"127", 0);  EXPECT(127);
  CONVERT_STR(VarI1FromStr,"128", 0);  EXPECT_OVERFLOW;

  CONVERT_STR(VarI1FromStr,"-1.5", LOCALE_NOUSEROVERRIDE); EXPECT(-2);
  CONVERT_STR(VarI1FromStr,"-0.6", LOCALE_NOUSEROVERRIDE); EXPECT(-1);
  CONVERT_STR(VarI1FromStr,"-0.5", LOCALE_NOUSEROVERRIDE); EXPECT(0);
  CONVERT_STR(VarI1FromStr,"-0.4", LOCALE_NOUSEROVERRIDE); EXPECT(0);
  CONVERT_STR(VarI1FromStr,"0.4", LOCALE_NOUSEROVERRIDE);  EXPECT(0);
  CONVERT_STR(VarI1FromStr,"0.5", LOCALE_NOUSEROVERRIDE);  EXPECT(0);
  CONVERT_STR(VarI1FromStr,"0.6", LOCALE_NOUSEROVERRIDE);  EXPECT(1);
  CONVERT_STR(VarI1FromStr,"1.5", LOCALE_NOUSEROVERRIDE);  EXPECT(2);
}