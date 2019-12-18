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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetEnvironmentVariableW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* wchar_to_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 int /*<<< orphan*/  wfree (char const*) ; 
 int /*<<< orphan*/  wvarname ; 

__attribute__((used)) static __inline char* getenvU(const char* varname)
{
	wconvert(varname);
	char* ret = NULL;
	wchar_t* wbuf = NULL;
	// _wgetenv() is *BROKEN* in MS compilers => use GetEnvironmentVariableW()
	DWORD dwSize = GetEnvironmentVariableW(wvarname, wbuf, 0);
	wbuf = calloc(dwSize, sizeof(wchar_t));
	if (wbuf == NULL) {
		wfree(varname);
		return NULL;
	}
	dwSize = GetEnvironmentVariableW(wvarname, wbuf, dwSize);
	if (dwSize != 0)
		ret = wchar_to_utf8(wbuf);
	free(wbuf);
	wfree(varname);
	return ret;
}