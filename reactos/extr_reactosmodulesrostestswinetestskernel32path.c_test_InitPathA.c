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
typedef  int UINT ;
typedef  int INT ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW ; 
 int CloseHandle (scalar_t__) ; 
 int CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_ALREADY_EXISTS ; 
 int /*<<< orphan*/  ERROR_DIRECTORY ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetCurrentDirectoryA (int,char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetLogicalDrives () ; 
 int GetTempFileNameA (char*,char*,int,char*) ; 
 scalar_t__ GetTempPathA (scalar_t__,char*) ; 
 int HAS_TRAIL_SLASH_A (char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 char* LONGDIR ; 
 char* LONGFILE ; 
 int MAX_PATH ; 
 char NOT_A_VALID_DRIVE ; 
 char* SHORTDIR ; 
 char* SHORTFILE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 scalar_t__ lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_InitPathA(CHAR *newdir, CHAR *curDrive, CHAR *otherDrive)
{
  CHAR tmppath[MAX_PATH], /*path to TEMP */
       tmpstr[MAX_PATH],
       tmpstr1[MAX_PATH],
       invalid_dir[MAX_PATH];

  DWORD len,len1,drives;
  INT id;
  HANDLE hndl;
  BOOL bRes;
  UINT unique;

  *curDrive = *otherDrive = NOT_A_VALID_DRIVE;

/* Get the current drive letter */
  if( GetCurrentDirectoryA( MAX_PATH, tmpstr))
    *curDrive = tmpstr[0];
  else
    trace( "Unable to discover current drive, some tests will not be conducted.\n");

/* Test GetTempPathA */
  len=GetTempPathA(MAX_PATH,tmppath);
  ok(len!=0 && len < MAX_PATH,"GetTempPathA failed\n");
  ok(HAS_TRAIL_SLASH_A(tmppath),
     "GetTempPathA returned a path that did not end in '\\'\n");
  lstrcpyA(tmpstr,"aaaaaaaa");
  len1=GetTempPathA(len,tmpstr);
  ok(len1==len+1 || broken(len1 == len), /* WinME */
     "GetTempPathA should return string length %d instead of %d\n",len+1,len1);

/* Test GetTmpFileNameA */
  ok((id=GetTempFileNameA(tmppath,"path",0,newdir)),"GetTempFileNameA failed\n");
  sprintf(tmpstr,"pat%.4x.tmp",id & 0xffff);
  sprintf(tmpstr1,"pat%x.tmp",id & 0xffff);
  ok(lstrcmpiA(newdir+lstrlenA(tmppath),tmpstr)==0 ||
     lstrcmpiA(newdir+lstrlenA(tmppath),tmpstr1)==0,
     "GetTempFileNameA returned '%s' which doesn't match '%s' or '%s'. id=%x\n",
     newdir,tmpstr,tmpstr1,id);
  ok(DeleteFileA(newdir),"Couldn't delete the temporary file we just created\n");     

  id=GetTempFileNameA(tmppath,NULL,0,newdir);
/* Windows 95, 98 return 0==id, while Windows 2000, XP return 0!=id */
  if (id)
  {
    sprintf(tmpstr,"%.4x.tmp",id & 0xffff);
    sprintf(tmpstr1,"%x.tmp",id & 0xffff);
    ok(lstrcmpiA(newdir+lstrlenA(tmppath),tmpstr)==0 ||
       lstrcmpiA(newdir+lstrlenA(tmppath),tmpstr1)==0,
       "GetTempFileNameA returned '%s' which doesn't match '%s' or '%s'. id=%x\n",
       newdir,tmpstr,tmpstr1,id);
    ok(DeleteFileA(newdir),"Couldn't delete the temporary file we just created\n");
  }

  for(unique=0;unique<3;unique++) {
    /* Nonexistent path */
    sprintf(invalid_dir, "%s\\%s",tmppath,"non_existent_dir_1jwj3y32nb3");
    SetLastError(0xdeadbeef);
    ok(!GetTempFileNameA(invalid_dir,"tfn",unique,newdir),"GetTempFileNameA should have failed\n");
    ok(GetLastError()==ERROR_DIRECTORY || broken(GetLastError()==ERROR_PATH_NOT_FOUND)/*win98*/,
    "got %d, expected ERROR_DIRECTORY\n", GetLastError());

    /* Check return value for unique !=0 */
    if(unique) {
      ok((GetTempFileNameA(tmppath,"tfn",unique,newdir) == unique),"GetTempFileNameA unexpectedly failed\n");
      /* if unique != 0, the actual temp files are not created: */
      ok(!DeleteFileA(newdir) && GetLastError() == ERROR_FILE_NOT_FOUND,"Deleted a file that shouldn't exist!\n");
    }
  }

/* Find first valid drive letter that is neither newdir[0] nor curDrive */
  drives = GetLogicalDrives() & ~(1<<(newdir[0]-'A'));
  if( *curDrive != NOT_A_VALID_DRIVE)
    drives &= ~(1<<(*curDrive-'A'));
  if( drives)
    for( *otherDrive='A'; (drives & 1) == 0; drives>>=1, (*otherDrive)++);
  else
    trace( "Could not find alternative drive, some tests will not be conducted.\n");

/* Do some CreateDirectoryA tests */
/* It would be nice to do test the SECURITY_ATTRIBUTES, but I don't
   really understand how they work.
   More formal tests should be done along with CreateFile tests
*/
  ok((id=GetTempFileNameA(tmppath,"path",0,newdir)),"GetTempFileNameA failed\n");
  ok(CreateDirectoryA(newdir,NULL)==0,
     "CreateDirectoryA succeeded even though a file of the same name exists\n");
  ok(DeleteFileA(newdir),"Couldn't delete the temporary file we just created\n");
  ok(CreateDirectoryA(newdir,NULL),"CreateDirectoryA failed\n");
/* Create some files to test other functions.  Note, we will test CreateFileA
   at some later point
*/
  sprintf(tmpstr,"%s\\%s",newdir,SHORTDIR);
  ok(CreateDirectoryA(tmpstr,NULL),"CreateDirectoryA failed\n");
  sprintf(tmpstr,"%s\\%s",newdir,LONGDIR);
  ok(CreateDirectoryA(tmpstr,NULL),"CreateDirectoryA failed\n");
  sprintf(tmpstr,"%c:", *curDrive);
  bRes = CreateDirectoryA(tmpstr,NULL);
  ok(!bRes && (GetLastError() == ERROR_ACCESS_DENIED  ||
               GetLastError() == ERROR_ALREADY_EXISTS),
     "CreateDirectoryA(\"%s\" should have failed (%d)\n", tmpstr, GetLastError());
  sprintf(tmpstr,"%c:\\", *curDrive);
  bRes = CreateDirectoryA(tmpstr,NULL);
  ok(!bRes && (GetLastError() == ERROR_ACCESS_DENIED  ||
               GetLastError() == ERROR_ALREADY_EXISTS),
     "CreateDirectoryA(\"%s\" should have failed (%d)\n", tmpstr, GetLastError());
  sprintf(tmpstr,"%s\\%s\\%s",newdir,SHORTDIR,SHORTFILE);
  hndl=CreateFileA(tmpstr,GENERIC_WRITE,0,NULL,
                   CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
  ok(hndl!=INVALID_HANDLE_VALUE,"CreateFileA failed\n");
  ok(CloseHandle(hndl),"CloseHandle failed\n");
  sprintf(tmpstr,"%s\\%s\\%s",newdir,SHORTDIR,LONGFILE);
  hndl=CreateFileA(tmpstr,GENERIC_WRITE,0,NULL,
                   CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
  ok(hndl!=INVALID_HANDLE_VALUE,"CreateFileA failed\n");
  ok(CloseHandle(hndl),"CloseHandle failed\n");
  sprintf(tmpstr,"%s\\%s\\%s",newdir,LONGDIR,SHORTFILE);
  hndl=CreateFileA(tmpstr,GENERIC_WRITE,0,NULL,
                   CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
  ok(hndl!=INVALID_HANDLE_VALUE,"CreateFileA failed\n");
  ok(CloseHandle(hndl),"CloseHandle failed\n");
  sprintf(tmpstr,"%s\\%s\\%s",newdir,LONGDIR,LONGFILE);
  hndl=CreateFileA(tmpstr,GENERIC_WRITE,0,NULL,
                   CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
  ok(hndl!=INVALID_HANDLE_VALUE,"CreateFileA failed\n");
  ok(CloseHandle(hndl),"CloseHandle failed\n");
}