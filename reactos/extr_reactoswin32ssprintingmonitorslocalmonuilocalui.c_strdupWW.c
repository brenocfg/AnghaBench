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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lstrcatW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (scalar_t__,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPWSTR strdupWW(LPCWSTR pPrefix, LPCWSTR pSuffix)
{
    LPWSTR  ptr;
    DWORD   len;

    len = lstrlenW(pPrefix) + (pSuffix ? lstrlenW(pSuffix) : 0) + 1;
    ptr = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
    if (ptr) {
        lstrcpyW(ptr, pPrefix);
        if (pSuffix) lstrcatW(ptr, pSuffix);
    }
    return ptr;
}