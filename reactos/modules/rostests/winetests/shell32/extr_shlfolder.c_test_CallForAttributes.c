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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPSHELLFOLDER ;
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  IMalloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IShellFolder_GetAttributesOf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IShellFolder_ParseDisplayName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ ) ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SFGAO_FILESYSTEM ; 
 scalar_t__ SFGAO_GHOSTED ; 
 scalar_t__ SFGAO_ISSLOW ; 
 scalar_t__ SHGetDesktopFolder (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ppM ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_CallForAttributes(void)
{
    HKEY hKey;
    LONG lResult;
    HRESULT hr;
    DWORD dwSize;
    LPSHELLFOLDER psfDesktop;
    LPITEMIDLIST pidlMyDocuments;
    DWORD dwAttributes, dwCallForAttributes, dwOrigAttributes, dwOrigCallForAttributes;
    static const WCHAR wszAttributes[] = { 'A','t','t','r','i','b','u','t','e','s',0 };
    static const WCHAR wszCallForAttributes[] = { 
        'C','a','l','l','F','o','r','A','t','t','r','i','b','u','t','e','s',0 };
    static const WCHAR wszMyDocumentsKey[] = {
        'C','L','S','I','D','\\','{','4','5','0','D','8','F','B','A','-','A','D','2','5','-',
        '1','1','D','0','-','9','8','A','8','-','0','8','0','0','3','6','1','B','1','1','0','3','}',
        '\\','S','h','e','l','l','F','o','l','d','e','r',0 };
    WCHAR wszMyDocuments[] = {
        ':',':','{','4','5','0','D','8','F','B','A','-','A','D','2','5','-','1','1','D','0','-',
        '9','8','A','8','-','0','8','0','0','3','6','1','B','1','1','0','3','}',0 };
    
    /* For the root of a namespace extension, the attributes are not queried by binding
     * to the object and calling GetAttributesOf. Instead, the attributes are read from 
     * the registry value HKCR/CLSID/{...}/ShellFolder/Attributes. This is documented on MSDN.
     *
     * The MyDocuments shellfolder on WinXP has a HKCR/CLSID/{...}/ShellFolder/CallForAttributes
     * value. It seems that if the folder is queried for one of the flags set in CallForAttributes,
     * the shell does bind to the folder object and calls GetAttributesOf. This is not documented
     * on MSDN. This test is meant to document the observed behaviour on WinXP SP2.
     */
    hr = SHGetDesktopFolder(&psfDesktop);
    ok (hr == S_OK, "SHGetDesktopFolder failed! hr = %08x\n", hr);
    if (hr != S_OK) return;

    hr = IShellFolder_ParseDisplayName(psfDesktop, NULL, NULL, wszMyDocuments, NULL,
                                       &pidlMyDocuments, NULL);
    ok (hr == S_OK,
        "Desktop's ParseDisplayName failed to parse MyDocuments's CLSID! hr = %08x\n", hr);
    if (hr != S_OK) {
        IShellFolder_Release(psfDesktop);
        return;
    }

    dwAttributes = 0xffffffff;
    hr = IShellFolder_GetAttributesOf(psfDesktop, 1, 
                                      (LPCITEMIDLIST*)&pidlMyDocuments, &dwAttributes);
    ok (hr == S_OK, "Desktop->GetAttributesOf(MyDocuments) failed! hr = %08x\n", hr);

    /* We need the following setup (as observed on WinXP SP2), for the tests to make sense. */
    ok (dwAttributes & SFGAO_FILESYSTEM, "SFGAO_FILESYSTEM attribute is not set for MyDocuments!\n");
    ok (!(dwAttributes & SFGAO_ISSLOW), "SFGAO_ISSLOW attribute is set for MyDocuments!\n");
    ok (!(dwAttributes & SFGAO_GHOSTED), "SFGAO_GHOSTED attribute is set for MyDocuments!\n");

    /* We don't have the MyDocuments shellfolder in wine yet, and thus we don't have the registry
     * key. So the test will return at this point, if run on wine. 
     */
    lResult = RegOpenKeyExW(HKEY_CLASSES_ROOT, wszMyDocumentsKey, 0, KEY_WRITE|KEY_READ, &hKey);
    ok (lResult == ERROR_SUCCESS ||
        lResult == ERROR_ACCESS_DENIED,
        "RegOpenKeyEx failed! result: %08x\n", lResult);
    if (lResult != ERROR_SUCCESS) {
        if (lResult == ERROR_ACCESS_DENIED)
            skip("Not enough rights to open the registry key\n");
        IMalloc_Free(ppM, pidlMyDocuments);
        IShellFolder_Release(psfDesktop);
        return;
    }
    
    /* Query MyDocuments' Attributes value, to be able to restore it later. */
    dwSize = sizeof(DWORD);
    lResult = RegQueryValueExW(hKey, wszAttributes, NULL, NULL, (LPBYTE)&dwOrigAttributes, &dwSize);
    ok (lResult == ERROR_SUCCESS, "RegQueryValueEx failed! result: %08x\n", lResult);
    if (lResult != ERROR_SUCCESS) {
        RegCloseKey(hKey);
        IMalloc_Free(ppM, pidlMyDocuments);
        IShellFolder_Release(psfDesktop);
        return;
    }

    /* Query MyDocuments' CallForAttributes value, to be able to restore it later. */
    dwSize = sizeof(DWORD);
    lResult = RegQueryValueExW(hKey, wszCallForAttributes, NULL, NULL, 
                              (LPBYTE)&dwOrigCallForAttributes, &dwSize);
    ok (lResult == ERROR_SUCCESS, "RegQueryValueEx failed! result: %08x\n", lResult);
    if (lResult != ERROR_SUCCESS) {
        RegCloseKey(hKey);
        IMalloc_Free(ppM, pidlMyDocuments);
        IShellFolder_Release(psfDesktop);
        return;
    }
    
    /* Define via the Attributes value that MyDocuments attributes are SFGAO_ISSLOW and 
     * SFGAO_GHOSTED and that MyDocuments should be called for the SFGAO_ISSLOW and
     * SFGAO_FILESYSTEM attributes. */
    dwAttributes = SFGAO_ISSLOW|SFGAO_GHOSTED;
    RegSetValueExW(hKey, wszAttributes, 0, REG_DWORD, (LPBYTE)&dwAttributes, sizeof(DWORD));
    dwCallForAttributes = SFGAO_ISSLOW|SFGAO_FILESYSTEM;
    RegSetValueExW(hKey, wszCallForAttributes, 0, REG_DWORD, 
                   (LPBYTE)&dwCallForAttributes, sizeof(DWORD));

    /* Although it is not set in CallForAttributes, the SFGAO_GHOSTED flag is reset by 
     * GetAttributesOf. It seems that once there is a single attribute queried, for which
     * CallForAttributes is set, all flags are taken from the GetAttributesOf call and
     * the flags in Attributes are ignored. 
     */
    dwAttributes = SFGAO_ISSLOW|SFGAO_GHOSTED|SFGAO_FILESYSTEM;
    hr = IShellFolder_GetAttributesOf(psfDesktop, 1, 
                                      (LPCITEMIDLIST*)&pidlMyDocuments, &dwAttributes);
    ok (hr == S_OK, "Desktop->GetAttributesOf(MyDocuments) failed! hr = %08x\n", hr);
    if (hr == S_OK)
        ok (dwAttributes == SFGAO_FILESYSTEM, 
            "Desktop->GetAttributes(MyDocuments) returned unexpected attributes: %08x\n", 
            dwAttributes);

    /* Restore MyDocuments' original Attributes and CallForAttributes registry values */
    RegSetValueExW(hKey, wszAttributes, 0, REG_DWORD, (LPBYTE)&dwOrigAttributes, sizeof(DWORD));
    RegSetValueExW(hKey, wszCallForAttributes, 0, REG_DWORD, 
                   (LPBYTE)&dwOrigCallForAttributes, sizeof(DWORD));
    RegCloseKey(hKey);
    IMalloc_Free(ppM, pidlMyDocuments);
    IShellFolder_Release(psfDesktop);
}