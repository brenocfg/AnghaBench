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
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int GetCurrentDirectoryA (int,char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetShortPathNameA (char*,char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,char*,...) ; 

__attribute__((used)) static void full_file_path_name_in_a_CWD(const char *src, char *dst, BOOL expect_short)
{
  DWORD retval;
  char shortname[MAX_PATH];

  retval = GetCurrentDirectoryA(MAX_PATH, dst);
  ok(retval > 0, "GetCurrentDirectoryA returned %d, GLE=%d\n",
     retval, GetLastError());
  if(dst[retval-1] != '\\')
    /* Append backslash only when it's missing */
      lstrcatA(dst, "\\");
  lstrcatA(dst, src);
  if(expect_short) 
  {
    memcpy(shortname, dst, MAX_PATH);
    retval = GetShortPathNameA(shortname, dst, MAX_PATH-1);
    ok(retval > 0, "GetShortPathNameA returned %d for '%s', GLE=%d\n",
       retval, dst, GetLastError());
  }
}