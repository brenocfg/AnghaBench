#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mypath ;
typedef  int /*<<< orphan*/  mydir ;
struct TYPE_5__ {char* description; char* workdir; char* path; char* arguments; char* icon; int icon_id; int hotkey; void* showcmd; int /*<<< orphan*/ * pidl; } ;
typedef  TYPE_1__ lnk_desc_t ;
typedef  int /*<<< orphan*/  desc ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DeleteFileA (char*) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 int GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 void* SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SearchPathA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_lnk (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  create_lnk (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pGetLongPathNameA (char*,char*,int) ; 
 int pGetShortPathNameA (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_load_save(void)
{
    WCHAR lnkfile[MAX_PATH];
    char lnkfileA[MAX_PATH];
    static const char lnkfileA_name[] = "\\test.lnk";

    lnk_desc_t desc;
    char mypath[MAX_PATH];
    char mydir[MAX_PATH];
    char realpath[MAX_PATH];
    char* p;
    HANDLE hf;
    DWORD r;

    if (!pGetLongPathNameA)
    {
        win_skip("GetLongPathNameA is not available\n");
        return;
    }

    /* Don't used a fixed path for the test.lnk file */
    GetTempPathA(MAX_PATH, lnkfileA);
    lstrcatA(lnkfileA, lnkfileA_name);
    MultiByteToWideChar(CP_ACP, 0, lnkfileA, -1, lnkfile, MAX_PATH);

    /* Save an empty .lnk file */
    memset(&desc, 0, sizeof(desc));
    create_lnk(lnkfile, &desc, 0);

    /* It should come back as a bunch of empty strings */
    desc.description="";
    desc.workdir="";
    desc.path="";
    desc.arguments="";
    desc.icon="";
    check_lnk(lnkfile, &desc, 0x0);

    /* Point a .lnk file to nonexistent files */
    desc.description="";
    desc.workdir="c:\\Nonexitent\\work\\directory";
    desc.path="c:\\nonexistent\\path";
    desc.pidl=NULL;
    desc.arguments="";
    desc.showcmd=0;
    desc.icon="c:\\nonexistent\\icon\\file";
    desc.icon_id=1234;
    desc.hotkey=0;
    create_lnk(lnkfile, &desc, 0);
    check_lnk(lnkfile, &desc, 0x0);

    r=GetModuleFileNameA(NULL, mypath, sizeof(mypath));
    ok(r<sizeof(mypath), "GetModuleFileName failed (%d)\n", r);
    strcpy(mydir, mypath);
    p=strrchr(mydir, '\\');
    if (p)
        *p='\0';

    /* IShellLink returns path in long form */
    if (!pGetLongPathNameA(mypath, realpath, MAX_PATH)) strcpy( realpath, mypath );

    /* Overwrite the existing lnk file and point it to existing files */
    desc.description="test 2";
    desc.workdir=mydir;
    desc.path=realpath;
    desc.pidl=NULL;
    desc.arguments="/option1 /option2 \"Some string\"";
    desc.showcmd=SW_SHOWNORMAL;
    desc.icon=mypath;
    desc.icon_id=0;
    desc.hotkey=0x1234;
    create_lnk(lnkfile, &desc, 0);
    check_lnk(lnkfile, &desc, 0x0);

    /* Test omitting .exe from an absolute path */
    p=strrchr(realpath, '.');
    if (p)
        *p='\0';

    desc.description="absolute path without .exe";
    desc.workdir=mydir;
    desc.path=realpath;
    desc.pidl=NULL;
    desc.arguments="/option1 /option2 \"Some string\"";
    desc.showcmd=SW_SHOWNORMAL;
    desc.icon=mypath;
    desc.icon_id=0;
    desc.hotkey=0x1234;
    create_lnk(lnkfile, &desc, 0);
    strcat(realpath, ".exe");
    check_lnk(lnkfile, &desc, 0x4);

    /* Overwrite the existing lnk file and test link to a command on the path */
    desc.description="command on path";
    desc.workdir=mypath;
    desc.path="rundll32.exe";
    desc.pidl=NULL;
    desc.arguments="/option1 /option2 \"Some string\"";
    desc.showcmd=SW_SHOWNORMAL;
    desc.icon=mypath;
    desc.icon_id=0;
    desc.hotkey=0x1234;
    create_lnk(lnkfile, &desc, 0);
    /* Check that link is created to proper location */
    SearchPathA( NULL, desc.path, NULL, MAX_PATH, realpath, NULL);
    desc.path=realpath;
    check_lnk(lnkfile, &desc, 0x0);

    /* Test omitting .exe from a command on the path */
    desc.description="command on path without .exe";
    desc.workdir=mypath;
    desc.path="rundll32";
    desc.pidl=NULL;
    desc.arguments="/option1 /option2 \"Some string\"";
    desc.showcmd=SW_SHOWNORMAL;
    desc.icon=mypath;
    desc.icon_id=0;
    desc.hotkey=0x1234;
    create_lnk(lnkfile, &desc, 0);
    /* Check that link is created to proper location */
    SearchPathA( NULL, "rundll32", NULL, MAX_PATH, realpath, NULL);
    desc.path=realpath;
    check_lnk(lnkfile, &desc, 0x4);

    /* Create a temporary non-executable file */
    r=GetTempPathA(sizeof(mypath), mypath);
    ok(r<sizeof(mypath), "GetTempPath failed (%d), err %d\n", r, GetLastError());
    r=pGetLongPathNameA(mypath, mydir, sizeof(mydir));
    ok(r<sizeof(mydir), "GetLongPathName failed (%d), err %d\n", r, GetLastError());
    p=strrchr(mydir, '\\');
    if (p)
        *p='\0';

    strcpy(mypath, mydir);
    strcat(mypath, "\\test.txt");
    hf = CreateFileA(mypath, GENERIC_WRITE, 0, NULL,
                     CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    CloseHandle(hf);

    /* Overwrite the existing lnk file and test link to an existing non-executable file */
    desc.description="non-executable file";
    desc.workdir=mydir;
    desc.path=mypath;
    desc.pidl=NULL;
    desc.arguments="";
    desc.showcmd=SW_SHOWNORMAL;
    desc.icon=mypath;
    desc.icon_id=0;
    desc.hotkey=0x1234;
    create_lnk(lnkfile, &desc, 0);
    check_lnk(lnkfile, &desc, 0x0);

    r=pGetShortPathNameA(mydir, mypath, sizeof(mypath));
    ok(r<sizeof(mypath), "GetShortPathName failed (%d), err %d\n", r, GetLastError());

    strcpy(realpath, mypath);
    strcat(realpath, "\\test.txt");
    strcat(mypath, "\\\\test.txt");

    /* Overwrite the existing lnk file and test link to a short path with double backslashes */
    desc.description="non-executable file";
    desc.workdir=mydir;
    desc.path=mypath;
    desc.pidl=NULL;
    desc.arguments="";
    desc.showcmd=SW_SHOWNORMAL;
    desc.icon=mypath;
    desc.icon_id=0;
    desc.hotkey=0x1234;
    create_lnk(lnkfile, &desc, 0);
    desc.path=realpath;
    check_lnk(lnkfile, &desc, 0x0);

    r = DeleteFileA(mypath);
    ok(r, "failed to delete file %s (%d)\n", mypath, GetLastError());

    /* Create a temporary .bat file */
    strcpy(mypath, mydir);
    strcat(mypath, "\\test.bat");
    hf = CreateFileA(mypath, GENERIC_WRITE, 0, NULL,
                     CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    CloseHandle(hf);

    strcpy(realpath, mypath);

    p=strrchr(mypath, '.');
    if (p)
        *p='\0';

    /* Try linking to the .bat file without the extension */
    desc.description="batch file";
    desc.workdir=mydir;
    desc.path=mypath;
    desc.pidl=NULL;
    desc.arguments="";
    desc.showcmd=SW_SHOWNORMAL;
    desc.icon=mypath;
    desc.icon_id=0;
    desc.hotkey=0x1234;
    create_lnk(lnkfile, &desc, 0);
    desc.path = realpath;
    check_lnk(lnkfile, &desc, 0x4);

    r = DeleteFileA(realpath);
    ok(r, "failed to delete file %s (%d)\n", realpath, GetLastError());

    /* FIXME: Also test saving a .lnk pointing to a pidl that cannot be
     * represented as a path.
     */

    /* DeleteFileW is not implemented on Win9x */
    r=DeleteFileA(lnkfileA);
    ok(r, "failed to delete link '%s' (%d)\n", lnkfileA, GetLastError());
}