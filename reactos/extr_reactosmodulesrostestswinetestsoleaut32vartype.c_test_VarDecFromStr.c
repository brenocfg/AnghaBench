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
 int /*<<< orphan*/  EXPECTDEC (int,int,int,int) ; 
 int /*<<< orphan*/  EXPECTDEC64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT_MISMATCH ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LCID ; 
 int /*<<< orphan*/  LOCALE_NOUSEROVERRIDE ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  VarDecFromStr ; 
 int /*<<< orphan*/  in ; 

__attribute__((used)) static void test_VarDecFromStr(void)
{
  CONVVARS(LCID);
  OLECHAR buff[128];

  in = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);

  CONVERT_STR(VarDecFromStr,NULL,0);                       EXPECT_MISMATCH;
  CONVERT_STR(VarDecFromStr,"-1",  LOCALE_NOUSEROVERRIDE); EXPECTDEC(0,0x80,0,1);
  CONVERT_STR(VarDecFromStr,"0",   LOCALE_NOUSEROVERRIDE); EXPECTDEC(0,0,0,0);
  CONVERT_STR(VarDecFromStr,"1",   LOCALE_NOUSEROVERRIDE); EXPECTDEC(0,0,0,1);
  CONVERT_STR(VarDecFromStr,"0.5", LOCALE_NOUSEROVERRIDE); EXPECTDEC(1,0,0,5);
  CONVERT_STR(VarDecFromStr,"4294967296", LOCALE_NOUSEROVERRIDE); EXPECTDEC64(0,0,0,1,0);
  CONVERT_STR(VarDecFromStr,"18446744073709551616", LOCALE_NOUSEROVERRIDE); EXPECTDEC(0,0,1,0);
  CONVERT_STR(VarDecFromStr,"4294967296.0", LOCALE_NOUSEROVERRIDE); EXPECTDEC64(0,0,0,1,0);
  CONVERT_STR(VarDecFromStr,"18446744073709551616.0", LOCALE_NOUSEROVERRIDE); EXPECTDEC(0,0,1,0);
}