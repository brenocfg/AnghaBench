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
typedef  int /*<<< orphan*/  str ;
typedef  char WCHAR ;
typedef  int UINT ;
typedef  char* LPWSTR ;
typedef  char const* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ HMMIO ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int GetModuleFileNameW (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GetProfileStringW (char const*,char const*,char const*,char*,int) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int MMIO_ALLOCBUF ; 
 int MMIO_DENYWRITE ; 
 int MMIO_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegOpenKeyW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int SND_APPLICATION ; 
 int SND_NODEFAULT ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int lstrlenW (char*) ; 
 scalar_t__ mmioOpenW (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HMMIO	get_mmioFromProfile(UINT uFlags, LPCWSTR lpszName)
{
    WCHAR	str[128];
    LPWSTR	ptr;
    HMMIO  	hmmio;
    HKEY        hRegSnd, hRegApp, hScheme, hSnd;
    DWORD       err, type, count;

    static const WCHAR  wszSounds[] = {'S','o','u','n','d','s',0};
    static const WCHAR  wszDefault[] = {'D','e','f','a','u','l','t',0};
    static const WCHAR  wszKey[] = {'A','p','p','E','v','e','n','t','s','\\',
                                    'S','c','h','e','m','e','s','\\',
                                    'A','p','p','s',0};
    static const WCHAR  wszDotDefault[] = {'.','D','e','f','a','u','l','t',0};
    static const WCHAR  wszDotCurrent[] = {'.','C','u','r','r','e','n','t',0};
    static const WCHAR  wszNull[] = {0};

    TRACE("searching in SystemSound list for %s\n", debugstr_w(lpszName));
    GetProfileStringW(wszSounds, lpszName, wszNull, str, sizeof(str)/sizeof(str[0]));
    if (lstrlenW(str) == 0)
    {
	if (uFlags & SND_NODEFAULT) goto next;
	GetProfileStringW(wszSounds, wszDefault, wszNull, str, sizeof(str)/sizeof(str[0]));
	if (lstrlenW(str) == 0) goto next;
    }
    for (ptr = str; *ptr && *ptr != ','; ptr++);
    if (*ptr) *ptr = 0;
    hmmio = mmioOpenW(str, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_DENYWRITE);
    if (hmmio != 0) return hmmio;
 next:
    /* we look up the registry under
     *      HKCU\AppEvents\Schemes\Apps\.Default
     *      HKCU\AppEvents\Schemes\Apps\<AppName>
     */
    if (RegOpenKeyW(HKEY_CURRENT_USER, wszKey, &hRegSnd) != 0) goto none;
    if (uFlags & SND_APPLICATION)
    {
        DWORD len;

        err = 1; /* error */
        len = GetModuleFileNameW(0, str, sizeof(str)/sizeof(str[0]));
        if (len > 0 && len < sizeof(str)/sizeof(str[0]))
        {
            for (ptr = str + lstrlenW(str) - 1; ptr >= str; ptr--)
            {
                if (*ptr == '.') *ptr = 0;
                if (*ptr == '\\')
                {
                    err = RegOpenKeyW(hRegSnd, ptr+1, &hRegApp);
                    break;
                }
            }
        }
    }
    else
    {
        err = RegOpenKeyW(hRegSnd, wszDotDefault, &hRegApp);
    }
    RegCloseKey(hRegSnd);
    if (err != 0) goto none;
    err = RegOpenKeyW(hRegApp, lpszName, &hScheme);
    RegCloseKey(hRegApp);
    if (err != 0) goto none;
    /* what's the difference between .Current and .Default ? */
    err = RegOpenKeyW(hScheme, wszDotDefault, &hSnd);
    if (err != 0)
    {
        err = RegOpenKeyW(hScheme, wszDotCurrent, &hSnd);
        RegCloseKey(hScheme);
        if (err != 0)
            goto none;
    }
    count = sizeof(str);
    err = RegQueryValueExW(hSnd, NULL, 0, &type, (LPBYTE)str, &count);
    RegCloseKey(hSnd);
    if (err != 0 || !*str) goto none;
    hmmio = mmioOpenW(str, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_DENYWRITE);
    if (hmmio) return hmmio;
 none:
    WARN("can't find SystemSound=%s !\n", debugstr_w(lpszName));
    return 0;
}