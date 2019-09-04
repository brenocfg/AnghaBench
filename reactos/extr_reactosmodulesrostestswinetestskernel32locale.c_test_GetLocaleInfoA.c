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
typedef  int /*<<< orphan*/  val ;
typedef  int LCID ;
typedef  int DWORD ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int COUNTOF (char*) ; 
 char* ERROR_INSUFFICIENT_BUFFER ; 
 char* GetLastError () ; 
 int GetLocaleInfoA (int,int,char*,int) ; 
 int LANG_ARABIC ; 
 int LANG_ENGLISH ; 
 int LANG_GERMAN ; 
 int LOCALE_ILANGUAGE ; 
 int LOCALE_RETURN_NUMBER ; 
 int LOCALE_SDAYNAME1 ; 
 int LOCALE_SLANGUAGE ; 
 int MAKELANGID (int,int /*<<< orphan*/ ) ; 
 int MAKELCID (int,int /*<<< orphan*/ ) ; 
 int NUO ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetLocaleInfoA(void)
{
  int ret;
  int len;
  LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
  char buffer[BUFFER_SIZE];
  char expected[BUFFER_SIZE];
  DWORD val;

  ok(lcid == 0x409, "wrong LCID calculated - %d\n", lcid);

  ret = GetLocaleInfoA(lcid, LOCALE_ILANGUAGE|LOCALE_RETURN_NUMBER, (char*)&val, sizeof(val));
  ok(ret, "got %d\n", ret);
  ok(val == lcid, "got 0x%08x\n", val);

  /* en and ar use SUBLANG_NEUTRAL, but GetLocaleInfo assume SUBLANG_DEFAULT
     Same is true for zh on pre-Vista, but on Vista and higher GetLocaleInfo
     assumes SUBLANG_NEUTRAL for zh */
  memset(expected, 0, COUNTOF(expected));
  len = GetLocaleInfoA(MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), LOCALE_SLANGUAGE, expected, COUNTOF(expected));
  SetLastError(0xdeadbeef);
  memset(buffer, 0, COUNTOF(buffer));
  ret = GetLocaleInfoA(LANG_ENGLISH, LOCALE_SLANGUAGE, buffer, COUNTOF(buffer));
  ok((ret == len) && !lstrcmpA(buffer, expected),
      "got %d with '%s' (expected %d with '%s')\n",
      ret, buffer, len, expected);

  memset(expected, 0, COUNTOF(expected));
  len = GetLocaleInfoA(MAKELANGID(LANG_ARABIC, SUBLANG_DEFAULT), LOCALE_SLANGUAGE, expected, COUNTOF(expected));
  if (len) {
      SetLastError(0xdeadbeef);
      memset(buffer, 0, COUNTOF(buffer));
      ret = GetLocaleInfoA(LANG_ARABIC, LOCALE_SLANGUAGE, buffer, COUNTOF(buffer));
      ok((ret == len) && !lstrcmpA(buffer, expected),
          "got %d with '%s' (expected %d with '%s')\n",
          ret, buffer, len, expected);
  }
  else
      win_skip("LANG_ARABIC not installed\n");

  /* SUBLANG_DEFAULT is required for mlang.dll, but optional for GetLocaleInfo */
  memset(expected, 0, COUNTOF(expected));
  len = GetLocaleInfoA(MAKELANGID(LANG_GERMAN, SUBLANG_DEFAULT), LOCALE_SLANGUAGE, expected, COUNTOF(expected));
  SetLastError(0xdeadbeef);
  memset(buffer, 0, COUNTOF(buffer));
  ret = GetLocaleInfoA(LANG_GERMAN, LOCALE_SLANGUAGE, buffer, COUNTOF(buffer));
  ok((ret == len) && !lstrcmpA(buffer, expected),
      "got %d with '%s' (expected %d with '%s')\n",
      ret, buffer, len, expected);


  /* HTMLKit and "Font xplorer lite" expect GetLocaleInfoA to
   * partially fill the buffer even if it is too short. See bug 637.
   */
  SetLastError(0xdeadbeef);
  memset(buffer, 0, COUNTOF(buffer));
  ret = GetLocaleInfoA(lcid, NUO|LOCALE_SDAYNAME1, buffer, 0);
  ok(ret == 7 && !buffer[0], "Expected len=7, got %d\n", ret);

  SetLastError(0xdeadbeef);
  memset(buffer, 0, COUNTOF(buffer));
  ret = GetLocaleInfoA(lcid, NUO|LOCALE_SDAYNAME1, buffer, 3);
  ok( !ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
      "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());
  ok(!strcmp(buffer, "Mon"), "Expected 'Mon', got '%s'\n", buffer);

  SetLastError(0xdeadbeef);
  memset(buffer, 0, COUNTOF(buffer));
  ret = GetLocaleInfoA(lcid, NUO|LOCALE_SDAYNAME1, buffer, 10);
  ok(ret == 7, "Expected ret == 7, got %d, error %d\n", ret, GetLastError());
  ok(!strcmp(buffer, "Monday"), "Expected 'Monday', got '%s'\n", buffer);
}