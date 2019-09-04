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
struct symt {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 char* symt_get_name (struct symt const*) ; 

WCHAR* symt_get_nameW(const struct symt* sym)
{
    const char* name = symt_get_name(sym);
    WCHAR* nameW;
    DWORD sz;

    if (!name) return NULL;
    sz = MultiByteToWideChar(CP_ACP, 0, name, -1, NULL, 0);
    if ((nameW = HeapAlloc(GetProcessHeap(), 0, sz * sizeof(WCHAR))))
        MultiByteToWideChar(CP_ACP, 0, name, -1, nameW, sz);
    return nameW;
}