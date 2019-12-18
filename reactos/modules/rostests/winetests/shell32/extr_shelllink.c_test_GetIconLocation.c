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
typedef  int /*<<< orphan*/  mypath ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellLinkW ;
typedef  int /*<<< orphan*/  IShellLinkA ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ShellLink ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 int /*<<< orphan*/  IID_IShellLinkA ; 
 int /*<<< orphan*/  IID_IShellLinkW ; 
 int INFOTIPSIZE ; 
 int IShellLinkA_GetIconLocation (int /*<<< orphan*/ *,char*,int,int*) ; 
 int IShellLinkA_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellLinkA_Release (int /*<<< orphan*/ *) ; 
 int IShellLinkA_SetIDList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IShellLinkA_SetIconLocation (int /*<<< orphan*/ *,char const*,int) ; 
 int IShellLinkA_SetPath (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  IShellLinkW_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int SUCCEEDED (int) ; 
 int S_FALSE ; 
 int S_OK ; 
 scalar_t__ lstrcmpiA (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pILFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_to_pidl (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_GetIconLocation(void)
{
    IShellLinkW *slW;
    IShellLinkA *sl;
    const char *str;
    char buffer[INFOTIPSIZE], mypath[MAX_PATH];
    int i;
    HRESULT r;
    LPITEMIDLIST pidl;

    r = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
            &IID_IShellLinkA, (LPVOID*)&sl);
    ok(r == S_OK, "no IID_IShellLinkA (0x%08x)\n", r);
    if(r != S_OK)
        return;

    i = 0xdeadbeef;
    strcpy(buffer, "garbage");
    r = IShellLinkA_GetIconLocation(sl, buffer, sizeof(buffer), &i);
    ok(r == S_OK, "GetIconLocation failed (0x%08x)\n", r);
    ok(*buffer == '\0', "GetIconLocation returned '%s'\n", buffer);
    ok(i == 0, "GetIconLocation returned %d\n", i);

    str = "c:\\some\\path";
    r = IShellLinkA_SetPath(sl, str);
    ok(r == S_FALSE || r == S_OK, "SetPath failed (0x%08x)\n", r);

    i = 0xdeadbeef;
    strcpy(buffer, "garbage");
    r = IShellLinkA_GetIconLocation(sl, buffer, sizeof(buffer), &i);
    ok(r == S_OK, "GetIconLocation failed (0x%08x)\n", r);
    ok(*buffer == '\0', "GetIconLocation returned '%s'\n", buffer);
    ok(i == 0, "GetIconLocation returned %d\n", i);

    GetWindowsDirectoryA(mypath, sizeof(mypath) - 12);
    strcat(mypath, "\\regedit.exe");
    pidl = path_to_pidl(mypath);
    r = IShellLinkA_SetIDList(sl, pidl);
    ok(r == S_OK, "SetPath failed (0x%08x)\n", r);
    pILFree(pidl);

    i = 0xdeadbeef;
    strcpy(buffer, "garbage");
    r = IShellLinkA_GetIconLocation(sl, buffer, sizeof(buffer), &i);
    ok(r == S_OK, "GetIconLocation failed (0x%08x)\n", r);
    ok(*buffer == '\0', "GetIconLocation returned '%s'\n", buffer);
    ok(i == 0, "GetIconLocation returned %d\n", i);

    str = "c:\\nonexistent\\file";
    r = IShellLinkA_SetIconLocation(sl, str, 0xbabecafe);
    ok(r == S_OK, "SetIconLocation failed (0x%08x)\n", r);

    i = 0xdeadbeef;
    r = IShellLinkA_GetIconLocation(sl, buffer, sizeof(buffer), &i);
    ok(r == S_OK, "GetIconLocation failed (0x%08x)\n", r);
    ok(lstrcmpiA(buffer,str) == 0, "GetIconLocation returned '%s'\n", buffer);
    ok(i == 0xbabecafe, "GetIconLocation returned %#x.\n", i);

    r = IShellLinkA_SetIconLocation(sl, NULL, 0xcafefe);
    ok(r == S_OK, "SetIconLocation failed (0x%08x)\n", r);

    i = 0xdeadbeef;
    r = IShellLinkA_GetIconLocation(sl, buffer, sizeof(buffer), &i);
    ok(r == S_OK, "GetIconLocation failed (0x%08x)\n", r);
    ok(!*buffer, "GetIconLocation returned '%s'\n", buffer);
    ok(i == 0xcafefe, "GetIconLocation returned %#x.\n", i);

    r = IShellLinkA_QueryInterface(sl, &IID_IShellLinkW, (void **)&slW);
    ok(SUCCEEDED(r), "Failed to get IShellLinkW, hr %#x.\n", r);

    str = "c:\\nonexistent\\file";
    r = IShellLinkA_SetIconLocation(sl, str, 0xbabecafe);
    ok(r == S_OK, "SetIconLocation failed (0x%08x)\n", r);

    r = IShellLinkA_SetIconLocation(sl, NULL, 0xcafefe);
    ok(r == S_OK, "SetIconLocation failed (0x%08x)\n", r);

    i = 0xdeadbeef;
    r = IShellLinkA_GetIconLocation(sl, buffer, sizeof(buffer), &i);
    ok(r == S_OK, "GetIconLocation failed (0x%08x)\n", r);
    ok(!*buffer, "GetIconLocation returned '%s'\n", buffer);
    ok(i == 0xcafefe, "GetIconLocation returned %#x.\n", i);

    IShellLinkW_Release(slW);
    IShellLinkA_Release(sl);
}