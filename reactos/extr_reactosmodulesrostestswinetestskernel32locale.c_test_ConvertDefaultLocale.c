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
typedef  int LCID ;

/* Variables and functions */
 int ConvertDefaultLocale (int) ; 
 int /*<<< orphan*/  GetSystemDefaultLCID () ; 
 int /*<<< orphan*/  GetUserDefaultLCID () ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_INVARIANT ; 
 int /*<<< orphan*/  LANG_JAPANESE ; 
 int /*<<< orphan*/  LANG_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  LANG_USER_DEFAULT ; 
 int /*<<< orphan*/  LCID_RES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LOCALE_INVARIANT ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  MKLCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SORT_JAPANESE_UNICODE ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_UK ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 int /*<<< orphan*/  TEST_LCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_LCIDLANG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 

__attribute__((used)) static void test_ConvertDefaultLocale(void)
{
  LCID lcid;

  /* Doesn't change lcid, even if non default sublang/sort used */
  TEST_LCID(LANG_ENGLISH,  SUBLANG_ENGLISH_US, SORT_DEFAULT);
  TEST_LCID(LANG_ENGLISH,  SUBLANG_ENGLISH_UK, SORT_DEFAULT);
  TEST_LCID(LANG_JAPANESE, SUBLANG_DEFAULT,    SORT_DEFAULT);
  TEST_LCID(LANG_JAPANESE, SUBLANG_DEFAULT,    SORT_JAPANESE_UNICODE);

  /* SUBLANG_NEUTRAL -> SUBLANG_DEFAULT */
  LCID_RES(MKLCID(LANG_ENGLISH,  SUBLANG_NEUTRAL, SORT_DEFAULT),
           MKLCID(LANG_ENGLISH,  SUBLANG_DEFAULT, SORT_DEFAULT));
  LCID_RES(MKLCID(LANG_JAPANESE, SUBLANG_NEUTRAL, SORT_DEFAULT),
           MKLCID(LANG_JAPANESE, SUBLANG_DEFAULT, SORT_DEFAULT));

  /* Invariant language is not treated specially */
  TEST_LCID(LANG_INVARIANT, SUBLANG_DEFAULT, SORT_DEFAULT);

  /* User/system default languages alone are not mapped */
  TEST_LCIDLANG(LANG_SYSTEM_DEFAULT, SORT_JAPANESE_UNICODE);
  TEST_LCIDLANG(LANG_USER_DEFAULT,   SORT_JAPANESE_UNICODE);

  /* Default lcids */
  LCID_RES(LOCALE_SYSTEM_DEFAULT, GetSystemDefaultLCID());
  LCID_RES(LOCALE_USER_DEFAULT,   GetUserDefaultLCID());
  LCID_RES(LOCALE_NEUTRAL,        GetUserDefaultLCID());
  lcid = ConvertDefaultLocale(LOCALE_INVARIANT);
  ok(lcid == LOCALE_INVARIANT || broken(lcid == 0x47f) /* win2k[3]/winxp */,
     "Expected lcid = %08x, got %08x\n", LOCALE_INVARIANT, lcid);
}