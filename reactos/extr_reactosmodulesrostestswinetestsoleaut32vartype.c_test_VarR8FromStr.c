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
 int /*<<< orphan*/  EXPECT (double) ; 
 int /*<<< orphan*/  EXPECT_MISMATCH ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LCID ; 
 int /*<<< orphan*/  LOCALE_NOUSEROVERRIDE ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  VarR8FromStr ; 
 int /*<<< orphan*/  in ; 

__attribute__((used)) static void test_VarR8FromStr(void)
{
  CONVVARS(LCID);
  OLECHAR buff[128];

  in = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);

  CONVERT_STR(VarR8FromStr,NULL,0);   EXPECT_MISMATCH;
  CONVERT_STR(VarR8FromStr,"",0);     EXPECT_MISMATCH;
  CONVERT_STR(VarR8FromStr," ",0);    EXPECT_MISMATCH;

  CONVERT_STR(VarR8FromStr,"0",LOCALE_NOUSEROVERRIDE);    EXPECT(0.0);
  CONVERT_STR(VarR8FromStr,"-1.5",LOCALE_NOUSEROVERRIDE); EXPECT(-1.5);
  CONVERT_STR(VarR8FromStr,"-0.6",LOCALE_NOUSEROVERRIDE); EXPECT(-0.6);
  CONVERT_STR(VarR8FromStr,"-0.5",LOCALE_NOUSEROVERRIDE); EXPECT(-0.5);
  CONVERT_STR(VarR8FromStr,"-0.4",LOCALE_NOUSEROVERRIDE); EXPECT(-0.4);
  CONVERT_STR(VarR8FromStr,"0.4",LOCALE_NOUSEROVERRIDE);  EXPECT(0.4);
  CONVERT_STR(VarR8FromStr,"0.5",LOCALE_NOUSEROVERRIDE);  EXPECT(0.5);
  CONVERT_STR(VarR8FromStr,"0.6",LOCALE_NOUSEROVERRIDE);  EXPECT(0.6);
  CONVERT_STR(VarR8FromStr,"1.5",LOCALE_NOUSEROVERRIDE);  EXPECT(1.5);
  CONVERT_STR(VarR8FromStr,"1e-94938484",LOCALE_NOUSEROVERRIDE);  EXPECT(0);

  /* We already have exhaustive tests for number parsing, so skip those tests here */
}