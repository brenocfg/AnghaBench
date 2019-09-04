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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CharUpperBuffW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utf8_to_wchar_no_alloc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wchar_to_utf8_no_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline DWORD CharUpperBuffU(char* lpString, DWORD len)
{
	DWORD ret;
	wchar_t *wlpString = calloc(len, sizeof(wchar_t));
	if (wlpString == NULL)
		return 0;
	utf8_to_wchar_no_alloc(lpString, wlpString, len);
	ret = CharUpperBuffW(wlpString, len);
	wchar_to_utf8_no_alloc(wlpString, lpString, len);
	free(wlpString);
	return ret;
}