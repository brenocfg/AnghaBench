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
typedef  int /*<<< orphan*/  LCID ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_CY (int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_SPANISH ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 

__attribute__((used)) static void test_VarBstrFromCy(void)
{
#define BSTR_CY(a, b, str, lcid) _BSTR_CY(a, b, str, lcid, __LINE__)

  LCID en_us, sp;

  en_us = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);
  sp = MAKELCID(MAKELANGID(LANG_SPANISH, SUBLANG_DEFAULT), SORT_DEFAULT);

  BSTR_CY(0, 0, "0", en_us);
  BSTR_CY(0, 10000, "1", en_us);
  BSTR_CY(0, 15000, "1.5", en_us);
  BSTR_CY(0xffffffff, ((15000)^0xffffffff)+1, "-1.5", en_us);
  /* (1 << 32) - 1 / 1000 */
  BSTR_CY(0, 0xffffffff, "429496.7295", en_us);
  /* (1 << 32) / 1000 */
  BSTR_CY(1, 0, "429496.7296", en_us);
  /* ((1 << 63) - 1)/10000 */
  BSTR_CY(0x7fffffff, 0xffffffff, "922337203685477.5807", en_us);
  BSTR_CY(0, 9, "0.0009", en_us);
  BSTR_CY(0, 9, "0,0009", sp);

#undef BSTR_CY
}