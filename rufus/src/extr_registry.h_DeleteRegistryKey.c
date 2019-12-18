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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int KEY_CREATE_SUB_KEY ; 
 int KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteKeyA (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 char* WindowsErrorString () ; 
 int /*<<< orphan*/  uprintf (char*,char const*,char*) ; 

__attribute__((used)) static __inline BOOL DeleteRegistryKey(HKEY key_root, const char* key_name)
{
	HKEY hSoftware = NULL;
	LONG s;

	if (RegOpenKeyExA(key_root, "SOFTWARE", 0, KEY_READ|KEY_CREATE_SUB_KEY, &hSoftware) != ERROR_SUCCESS) {
		return FALSE;
	}

	s = RegDeleteKeyA(hSoftware, key_name);
	if ((s != ERROR_SUCCESS) && (s != ERROR_FILE_NOT_FOUND)) {
		SetLastError(s);
		uprintf("Failed to delete registry key HKCU\\Software\\%s: %s", key_name,
			(s == ERROR_ACCESS_DENIED)?"Key is not empty":WindowsErrorString());
	}
	RegCloseKey(hSoftware);
	return ((s == ERROR_SUCCESS) || (s == ERROR_FILE_NOT_FOUND));
}