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
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

DWORD
AnsiToUnicode(LPCSTR lpSrcStr,
              LPWSTR *lpDstStr)
{
    INT length;
    INT ret = 0;

    length = strlen(lpSrcStr) + 1;

    *lpDstStr = (LPWSTR)HeapAlloc(GetProcessHeap(), 0, length * sizeof(WCHAR));
    if (*lpDstStr)
    {
        ret = MultiByteToWideChar(CP_ACP,
                                  0,
                                  lpSrcStr,
                                  -1,
                                  *lpDstStr,
                                  length);
    }

    return ret;
}