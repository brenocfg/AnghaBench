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
typedef  int /*<<< orphan*/  systemDirx86 ;
typedef  int /*<<< orphan*/  systemDir ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_SYSTEM ; 
 int /*<<< orphan*/  CSIDL_SYSTEMX86 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSystemDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  myPathRemoveBackslashA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,char*,char*) ; 
 int /*<<< orphan*/  pGetSystemWow64DirectoryA (char*,int) ; 
 scalar_t__ pSHGetSpecialFolderPathA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void testSystemDir(void)
{
    char systemShellPath[MAX_PATH], systemDir[MAX_PATH], systemDirx86[MAX_PATH];

    if (!pSHGetSpecialFolderPathA) return;

    GetSystemDirectoryA(systemDir, sizeof(systemDir));
    myPathRemoveBackslashA(systemDir);
    if (pSHGetSpecialFolderPathA(NULL, systemShellPath, CSIDL_SYSTEM, FALSE))
    {
        myPathRemoveBackslashA(systemShellPath);
        ok(!lstrcmpiA(systemDir, systemShellPath),
         "GetSystemDirectory returns %s SHGetSpecialFolderPath returns %s\n",
         systemDir, systemShellPath);
    }

    if (!pGetSystemWow64DirectoryA || !pGetSystemWow64DirectoryA(systemDirx86, sizeof(systemDirx86)))
        GetSystemDirectoryA(systemDirx86, sizeof(systemDirx86));
    myPathRemoveBackslashA(systemDirx86);
    if (pSHGetSpecialFolderPathA(NULL, systemShellPath, CSIDL_SYSTEMX86, FALSE))
    {
        myPathRemoveBackslashA(systemShellPath);
        ok(!lstrcmpiA(systemDirx86, systemShellPath) || broken(!lstrcmpiA(systemDir, systemShellPath)),
         "GetSystemDirectory returns %s SHGetSpecialFolderPath returns %s\n",
         systemDir, systemShellPath);
    }
}