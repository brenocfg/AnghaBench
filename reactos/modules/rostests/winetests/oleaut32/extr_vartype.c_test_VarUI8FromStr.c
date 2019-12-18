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
 int /*<<< orphan*/  EXPECTI8 (int) ; 
 int /*<<< orphan*/  EXPECTI864 (int,int) ; 
 int /*<<< orphan*/  EXPECT_MISMATCH ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LCID ; 
 int /*<<< orphan*/  LOCALE_NOUSEROVERRIDE ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  VarUI8FromStr ; 
 int /*<<< orphan*/  in ; 

__attribute__((used)) static void test_VarUI8FromStr(void)
{
  CONVVARS(LCID);
  OLECHAR buff[128];

  in = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);

  CONVERT_STR(VarUI8FromStr,NULL,0);                    EXPECT_MISMATCH;
  CONVERT_STR(VarUI8FromStr,"0",0);                     EXPECTI8(0);
  CONVERT_STR(VarUI8FromStr,"-1",0);                    EXPECT_OVERFLOW;
  CONVERT_STR(VarUI8FromStr,"2147483647",0);            EXPECTI8(2147483647);
  CONVERT_STR(VarUI8FromStr,"18446744073709551614",0);  EXPECTI864(0xFFFFFFFF,0xFFFFFFFE);
  CONVERT_STR(VarUI8FromStr,"18446744073709551615",0);  EXPECTI864(0xFFFFFFFF,0xFFFFFFFF);
  CONVERT_STR(VarUI8FromStr,"18446744073709551616",0);  EXPECT_OVERFLOW;

  CONVERT_STR(VarUI8FromStr,"-1.5",LOCALE_NOUSEROVERRIDE); EXPECT_OVERFLOW;
  CONVERT_STR(VarUI8FromStr,"-0.6",LOCALE_NOUSEROVERRIDE); EXPECT_OVERFLOW;
  CONVERT_STR(VarUI8FromStr,"-0.5",LOCALE_NOUSEROVERRIDE); EXPECTI8(0);
  CONVERT_STR(VarUI8FromStr,"-0.4",LOCALE_NOUSEROVERRIDE); EXPECTI8(0);
  CONVERT_STR(VarUI8FromStr,"0.4",LOCALE_NOUSEROVERRIDE);  EXPECTI8(0);
  CONVERT_STR(VarUI8FromStr,"0.5",LOCALE_NOUSEROVERRIDE);  EXPECTI8(0);
  CONVERT_STR(VarUI8FromStr,"0.6",LOCALE_NOUSEROVERRIDE);  EXPECTI8(1);
  CONVERT_STR(VarUI8FromStr,"1.5",LOCALE_NOUSEROVERRIDE);  EXPECTI8(2);
}