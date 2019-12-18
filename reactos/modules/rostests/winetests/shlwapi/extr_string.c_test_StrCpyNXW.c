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
typedef  int /*<<< orphan*/  lpInit ;
typedef  int /*<<< orphan*/  dest ;
typedef  char WCHAR ;
typedef  char* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,char*,char*,char,char,char,char,char,char,char,char) ; 
 char* pStrCpyNXW (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_StrCpyNXW(void)
{
  static const WCHAR lpInit[] = { '\n','\n','\n','\n','\n','\n','\n','\n' };
  static const WCHAR lpSrc[] = { 'h','e','l','l','o','\0' };
  static const WCHAR lpRes[] = { 'h','e','l','l','o','\0','\n','\n' };
  LPWSTR lpszRes;
  WCHAR dest[8];

  if (!pStrCpyNXW)
  {
    win_skip("StrCpyNXW() is not available\n");
    return;
  }

  memcpy(dest, lpInit, sizeof(lpInit));
  lpszRes = pStrCpyNXW(dest, lpSrc, ARRAY_SIZE(dest));
  ok(lpszRes == dest + 5 && !memcmp(dest, lpRes, sizeof(dest)),
       "StrCpyNXW: expected %p, \"hello\\0\\n\\n\", got %p, \"%d,%d,%d,%d,%d,%d,%d,%d\"\n",
       dest + 5, lpszRes, dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);
}