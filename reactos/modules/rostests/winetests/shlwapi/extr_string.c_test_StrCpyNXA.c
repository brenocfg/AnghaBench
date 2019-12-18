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
typedef  int /*<<< orphan*/  dest ;
typedef  char* LPSTR ;
typedef  char* LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,char*,char*,char,char,char,char,char,char,char,char) ; 
 char* pStrCpyNXA (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_StrCpyNXA(void)
{
  LPCSTR lpSrc = "hello";
  LPSTR lpszRes;
  char dest[8];

  if (!pStrCpyNXA)
  {
    win_skip("StrCpyNXA() is not available\n");
    return;
  }

  memset(dest, '\n', sizeof(dest));
  lpszRes = pStrCpyNXA(dest, lpSrc, ARRAY_SIZE(dest));
  ok(lpszRes == dest + 5 && !memcmp(dest, "hello\0\n\n", sizeof(dest)),
       "StrCpyNXA: expected %p, \"hello\\0\\n\\n\", got %p, \"%d,%d,%d,%d,%d,%d,%d,%d\"\n",
       dest + 5, lpszRes, dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);
}