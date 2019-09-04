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
typedef  int /*<<< orphan*/  LPSTR ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCR_RegGetIconA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

BOOL HCR_GetIconA(LPCSTR szClass, LPSTR szDest, LPCSTR szName, DWORD len, int* picon_idx)
{
	HKEY	hkey;
	char	sTemp[MAX_PATH];
	BOOL	ret = FALSE;

	TRACE("%s\n",szClass );

	sprintf(sTemp, "%s\\DefaultIcon",szClass);

	if (!RegOpenKeyExA(HKEY_CLASSES_ROOT, sTemp, 0, KEY_READ, &hkey))
	{
	  ret = HCR_RegGetIconA(hkey, szDest, szName, len, picon_idx);
	  RegCloseKey(hkey);
	}
	TRACE("-- %s %i\n", szDest, *picon_idx);
	return ret;
}