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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/ * CRYPT_Alloc (unsigned int) ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 unsigned int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int min (unsigned int,int) ; 

__attribute__((used)) static inline BOOL CRYPT_ANSIToUnicode(LPCSTR str, LPWSTR* wstr, int wstrsize)
{
	unsigned int wcount;

	if (!str)
	{
		*wstr = NULL;
		return TRUE;
	}
	wcount = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	if (wstrsize == -1)
		*wstr = CRYPT_Alloc(wcount * sizeof(WCHAR));
	else
		wcount = min( wcount, wstrsize/sizeof(WCHAR) );
	if (*wstr)
	{
		MultiByteToWideChar(CP_ACP, 0, str, -1, *wstr, wcount);
		return TRUE;
	}
	SetLastError(ERROR_NOT_ENOUGH_MEMORY);
	return FALSE;
}