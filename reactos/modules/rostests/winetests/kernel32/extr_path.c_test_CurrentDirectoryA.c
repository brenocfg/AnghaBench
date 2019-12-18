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
typedef  char* LPSTR ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int GetCurrentDirectoryA (int,char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* LONGDIR ; 
 int MAX_PATH ; 
 char* NONDIR_LONG ; 
 char* NONDIR_SHORT ; 
 char* SHORTDIR ; 
 int /*<<< orphan*/  SetCurrentDirectoryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 scalar_t__ lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  test_setdir (char*,char*,char*,int,char*) ; 

__attribute__((used)) static void test_CurrentDirectoryA(CHAR *origdir, CHAR *newdir)
{
  CHAR tmpstr[MAX_PATH],tmpstr1[MAX_PATH];
  char *buffer;
  DWORD len,len1;
/* Save the original directory, so that we can return to it at the end
   of the test
*/
  len=GetCurrentDirectoryA(MAX_PATH,origdir);
  ok(len!=0 && len < MAX_PATH,"GetCurrentDirectoryA failed\n");
/* Make sure that CetCurrentDirectoryA doesn't overwrite the buffer when the
   buffer size is too small to hold the current directory
*/
  lstrcpyA(tmpstr,"aaaaaaa");
  len1=GetCurrentDirectoryA(len,tmpstr);
  ok(len1==len+1, "GetCurrentDirectoryA returned %d instead of %d\n",len1,len+1);
  ok(lstrcmpiA(tmpstr,"aaaaaaa")==0,
     "GetCurrentDirectoryA should not have modified the buffer\n");

  buffer = HeapAlloc( GetProcessHeap(), 0, 2 * 65536 );
  SetLastError( 0xdeadbeef );
  strcpy( buffer, "foo" );
  len = GetCurrentDirectoryA( 32767, buffer );
  ok( len != 0 && len < MAX_PATH, "GetCurrentDirectoryA failed %u err %u\n", len, GetLastError() );
  if (len) ok( !strcmp( buffer, origdir ), "wrong result %s\n", buffer );
  SetLastError( 0xdeadbeef );
  strcpy( buffer, "foo" );
  len = GetCurrentDirectoryA( 32768, buffer );
  ok( len != 0 && len < MAX_PATH, "GetCurrentDirectoryA failed %u err %u\n", len, GetLastError() );
  if (len) ok( !strcmp( buffer, origdir ), "wrong result %s\n", buffer );
  SetLastError( 0xdeadbeef );
  strcpy( buffer, "foo" );
  len = GetCurrentDirectoryA( 65535, buffer );
  ok( (len != 0 && len < MAX_PATH) || broken(!len), /* nt4, win2k, xp */ "GetCurrentDirectoryA failed %u err %u\n", len, GetLastError() );
  if (len) ok( !strcmp( buffer, origdir ), "wrong result %s\n", buffer );
  SetLastError( 0xdeadbeef );
  strcpy( buffer, "foo" );
  len = GetCurrentDirectoryA( 65536, buffer );
  ok( (len != 0 && len < MAX_PATH) || broken(!len), /* nt4 */ "GetCurrentDirectoryA failed %u err %u\n", len, GetLastError() );
  if (len) ok( !strcmp( buffer, origdir ), "wrong result %s\n", buffer );
  SetLastError( 0xdeadbeef );
  strcpy( buffer, "foo" );
  len = GetCurrentDirectoryA( 2 * 65536, buffer );
  ok( (len != 0 && len < MAX_PATH) || broken(!len), /* nt4 */ "GetCurrentDirectoryA failed %u err %u\n", len, GetLastError() );
  if (len) ok( !strcmp( buffer, origdir ), "wrong result %s\n", buffer );
  HeapFree( GetProcessHeap(), 0, buffer );

/* Check for crash prevention on swapped args. Crashes all but Win9x.
*/
  if (0)
  {
      GetCurrentDirectoryA( 42, (LPSTR)(MAX_PATH + 42) );
  }

/* SetCurrentDirectoryA shouldn't care whether the string has a
   trailing '\\' or not
*/
  sprintf(tmpstr,"%s\\",newdir);
  test_setdir(origdir,tmpstr,newdir,1,"check 1");
  test_setdir(origdir,newdir,NULL,1,"check 2");
/* Set the directory to the working area.  We just tested that this works,
   so why check it again.
*/
  SetCurrentDirectoryA(newdir);
/* Check that SetCurrentDirectory fails when a nonexistent dir is specified */
  sprintf(tmpstr,"%s\\%s\\%s",newdir,SHORTDIR,NONDIR_SHORT);
  test_setdir(newdir,tmpstr,NULL,0,"check 3");
/* Check that SetCurrentDirectory fails for a nonexistent lond directory */
  sprintf(tmpstr,"%s\\%s\\%s",newdir,SHORTDIR,NONDIR_LONG);
  test_setdir(newdir,tmpstr,NULL,0,"check 4");
/* Check that SetCurrentDirectory passes with a long directory */
  sprintf(tmpstr,"%s\\%s",newdir,LONGDIR);
  test_setdir(newdir,tmpstr,NULL,1,"check 5");
/* Check that SetCurrentDirectory passes with a short relative directory */
  sprintf(tmpstr,"%s",SHORTDIR);
  sprintf(tmpstr1,"%s\\%s",newdir,SHORTDIR);
  test_setdir(newdir,tmpstr,tmpstr1,1,"check 6");
/* starting with a '.' */
  sprintf(tmpstr,".\\%s",SHORTDIR);
  test_setdir(newdir,tmpstr,tmpstr1,1,"check 7");
/* Check that SetCurrentDirectory passes with a short relative directory */
  sprintf(tmpstr,"%s",LONGDIR);
  sprintf(tmpstr1,"%s\\%s",newdir,LONGDIR);
  test_setdir(newdir,tmpstr,tmpstr1,1,"check 8");
/* starting with a '.' */
  sprintf(tmpstr,".\\%s",LONGDIR);
  test_setdir(newdir,tmpstr,tmpstr1,1,"check 9");
/* change to root without a trailing backslash. The function call succeeds
   but the directory is not changed.
*/
  sprintf(tmpstr, "%c:", newdir[0]);
  test_setdir(newdir,tmpstr,newdir,1,"check 10");
/* works however with a trailing backslash */
  sprintf(tmpstr, "%c:\\", newdir[0]);
  test_setdir(newdir,tmpstr,NULL,1,"check 11");
}