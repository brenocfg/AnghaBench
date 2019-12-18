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
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IEnumIDList ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IEnumIDList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ShellFolder ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pSHIShellFolder_EnumObjects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SHIShellFolder_EnumObjects(void)
{
    IEnumIDList *enm;
    HRESULT hres;
    IShellFolder *folder;

    if(!pSHIShellFolder_EnumObjects){ /* win7 and later */
        win_skip("SHIShellFolder_EnumObjects not available\n");
        return;
    }

    if(0){
        /* NULL object crashes on Windows */
        pSHIShellFolder_EnumObjects(NULL, NULL, 0, NULL);
    }

    /* SHIShellFolder_EnumObjects doesn't QI the object for IShellFolder */
    enm = (IEnumIDList*)0xdeadbeef;
    hres = pSHIShellFolder_EnumObjects(&ShellFolder, NULL, 0, &enm);
    ok(hres == S_OK, "SHIShellFolder_EnumObjects failed: 0x%08x\n", hres);
    ok(enm == (IEnumIDList*)0xcafebabe, "Didn't get expected enumerator location, instead: %p\n", enm);

    /* SHIShellFolder_EnumObjects isn't strict about the IShellFolder object */
    hres = SHGetDesktopFolder(&folder);
    ok(hres == S_OK, "SHGetDesktopFolder failed: 0x%08x\n", hres);

    enm = NULL;
    hres = pSHIShellFolder_EnumObjects(folder, NULL, 0, &enm);
    ok(hres == S_OK, "SHIShellFolder_EnumObjects failed: 0x%08x\n", hres);
    ok(enm != NULL, "Didn't get an enumerator\n");
    if(enm)
        IEnumIDList_Release(enm);

    IShellFolder_Release(folder);
}