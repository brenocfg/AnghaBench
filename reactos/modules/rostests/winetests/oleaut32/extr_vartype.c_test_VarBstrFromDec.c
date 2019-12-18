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
 int /*<<< orphan*/  BSTR_DEC (int,int,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSTR_DEC64 (int,int /*<<< orphan*/ ,int,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_SPANISH ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 

__attribute__((used)) static void test_VarBstrFromDec(void)
{
#define BSTR_DEC(scale, sign, hi, lo, str, lcid) _BSTR_DEC(scale, sign, hi, 0, lo, str, lcid, __LINE__)
#define BSTR_DEC64(scale, sign, hi, mid, lo, str, lcid) _BSTR_DEC(scale, sign, hi, mid, lo, str, lcid, __LINE__)

  LCID en_us, sp;

  en_us = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);
  sp = MAKELCID(MAKELANGID(LANG_SPANISH, SUBLANG_DEFAULT), SORT_DEFAULT);

  BSTR_DEC(0,0,0,0, "0", en_us);

  BSTR_DEC(0,0,0,1,   "1", en_us);
  BSTR_DEC(1,0,0,10,  "1", en_us);
  BSTR_DEC(2,0,0,100, "1", en_us);
  BSTR_DEC(3,0,0,1000,"1", en_us);

  BSTR_DEC(1,0,0,15,  "1.5", en_us);
  BSTR_DEC(2,0,0,150, "1.5", en_us);
  BSTR_DEC(3,0,0,1500,"1.5", en_us);

  BSTR_DEC(1,0x80,0,15, "-1.5", en_us);

  /* (1 << 32) - 1 */
  BSTR_DEC(0,0,0,0xffffffff, "4294967295", en_us);
  /* (1 << 32) */
  BSTR_DEC64(0,0,0,1,0, "4294967296", en_us);
  /* (1 << 64) - 1 */
  BSTR_DEC64(0,0,0,0xffffffff,0xffffffff, "18446744073709551615", en_us);
  /* (1 << 64) */
  BSTR_DEC(0,0,1,0, "18446744073709551616", en_us);
  /* (1 << 96) - 1 */
  BSTR_DEC64(0,0,0xffffffff,0xffffffff,0xffffffff, "79228162514264337593543950335", en_us);
  /* 1 * 10^-10 */
  BSTR_DEC(10,0,0,1, "0.0000000001", en_us);
  /* ((1 << 96) - 1) * 10^-10 */
  BSTR_DEC64(10,0,0xffffffffUL,0xffffffff,0xffffffff, "7922816251426433759.3543950335", en_us);
  /* ((1 << 96) - 1) * 10^-28 */
  BSTR_DEC64(28,0,0xffffffffUL,0xffffffff,0xffffffff, "7.9228162514264337593543950335", en_us);

  /* check leading zeros and decimal sep. for English locale */
  BSTR_DEC(4,0,0,9, "0.0009", en_us);
  BSTR_DEC(5,0,0,90, "0.0009", en_us);
  BSTR_DEC(6,0,0,900, "0.0009", en_us);
  BSTR_DEC(7,0,0,9000, "0.0009", en_us);
  
  /* check leading zeros and decimal sep. for Spanish locale */
  BSTR_DEC(4,0,0,9, "0,0009", sp);
  BSTR_DEC(5,0,0,90, "0,0009", sp);
  BSTR_DEC(6,0,0,900, "0,0009", sp);
  BSTR_DEC(7,0,0,9000, "0,0009", sp);

#undef BSTR_DEC
#undef BSTR_DEC64
}