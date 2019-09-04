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

/* Variables and functions */
 int /*<<< orphan*/ * RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/ * strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static WCHAR *strdupW(const WCHAR* str)
{
    WCHAR*      ptr;

    if (!(ptr = RtlAllocateHeap(RtlGetProcessHeap(), 0, (strlenW(str) + 1) * sizeof(WCHAR))))
        return NULL;
    return strcpyW(ptr, str);
}