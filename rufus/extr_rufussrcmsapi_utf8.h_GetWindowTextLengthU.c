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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetWindowTextLengthW (int /*<<< orphan*/ ) ; 
 int GetWindowTextW (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  sfree (char*) ; 
 scalar_t__ strlen (char*) ; 
 char* wchar_to_utf8 (char*) ; 

__attribute__((used)) static __inline int GetWindowTextLengthU(HWND hWnd)
{
	int ret = 0;
	DWORD err = ERROR_INVALID_DATA;
	wchar_t* wbuf = NULL;
	char* buf = NULL;

	ret = GetWindowTextLengthW(hWnd);
	err = GetLastError();
	if (ret == 0) goto out;
	wbuf = calloc(ret, sizeof(wchar_t));
	err = GetLastError();
	if (wbuf == NULL) {
		err = ERROR_OUTOFMEMORY; ret = 0; goto out;
	}
	ret = GetWindowTextW(hWnd, wbuf, ret);
	err = GetLastError();
	if (ret == 0) goto out;
	buf = wchar_to_utf8(wbuf);
	err = GetLastError();
	if (buf == NULL) {
		err = ERROR_OUTOFMEMORY; ret = 0; goto out;
	}
	ret = (int)strlen(buf) + 2;	// GetDlgItemText seems to add a character
	err = GetLastError();
out:
	sfree(wbuf);
	sfree(buf);
	SetLastError(err);
	return ret;
}