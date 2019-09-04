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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_MULTI_SZ ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ g_fFontBold ; 
 scalar_t__ g_fRandomizeMessages ; 
 scalar_t__ g_nDensity ; 
 scalar_t__ g_nFontSize ; 
 scalar_t__ g_nMatrixSpeed ; 
 scalar_t__ g_nMessageSpeed ; 
 int g_nNumMessages ; 
 scalar_t__ g_szFontName ; 
 scalar_t__* g_szMessages ; 
 int /*<<< orphan*/  lstrcpyn (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int lstrlen (scalar_t__) ; 
 int /*<<< orphan*/ * malloc (int) ; 

void SaveSettings()
{
	HKEY hkey;
	TCHAR *hugechar = malloc(4096 * sizeof(TCHAR));
	TCHAR *msgptr = hugechar;
	int totallen = 0;
	int i,len;
	LONG value;

	if(hugechar == 0)
		return;

	ZeroMemory(hugechar, 4096 * sizeof(TCHAR));
	msgptr = hugechar;

	RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\Catch22\\Matrix Screen Saver"), 0,
		_T(""), 0, KEY_WRITE, NULL, &hkey, NULL);

	value = g_nMessageSpeed;
	RegSetValueEx(hkey, _T("MessageSpeed"), 0, REG_DWORD, (BYTE *)&value, sizeof value);

	value = g_nMatrixSpeed;
	RegSetValueEx(hkey, _T("MatrixSpeed"), 0, REG_DWORD, (BYTE *)&value, sizeof value);

	value = g_nDensity;
	RegSetValueEx(hkey, _T("Density"), 0, REG_DWORD, (BYTE *)&value, sizeof value);

	value = g_nFontSize;
	RegSetValueEx(hkey, _T("FontSize"), 0, REG_DWORD, (BYTE *)&value, sizeof value);

	value = g_fRandomizeMessages;
	RegSetValueEx(hkey, _T("Randomize"), 0, REG_DWORD, (BYTE *)&value, sizeof value);

	value = g_fFontBold;
	RegSetValueEx(hkey, _T("FontBold"), 0, REG_DWORD, (BYTE *)&value, sizeof value);

	RegSetValueEx(hkey, _T("FontName"), 0, REG_SZ, (BYTE *)g_szFontName, lstrlen(g_szFontName) * sizeof(TCHAR));

	for(i = 0; i < g_nNumMessages; i++)
	{
		len = lstrlen(g_szMessages[i]);

		if(len > 0 && totallen+len < 4096)
		{
			lstrcpyn(msgptr, g_szMessages[i], 4096-totallen);
			totallen += len + 1;
			msgptr += len + 1;
		}
	}

	//*msgptr = _T('\0');
	totallen++;

	RegSetValueEx(hkey, _T("Messages"), 0, REG_MULTI_SZ, (BYTE *)hugechar, totallen * sizeof(TCHAR));
	RegCloseKey(hkey);

	free(hugechar);
}