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
typedef  scalar_t__ LPSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ ) ; 

DWORD
UnicodeToAnsi(LPCWSTR lpSrcStr,
              LPSTR *lpDstStr)
{
    INT length;
    INT ret = 0;

    length = wcslen(lpSrcStr) + 1;

    *lpDstStr = (LPSTR)HeapAlloc(GetProcessHeap(), 0, length);
    if (*lpDstStr)
    {
        ret = WideCharToMultiByte(CP_ACP,
                                  0,
                                  lpSrcStr,
                                  -1,
                                  *lpDstStr,
                                  length,
                                  NULL,
                                  NULL);
    }

    return ret;
}