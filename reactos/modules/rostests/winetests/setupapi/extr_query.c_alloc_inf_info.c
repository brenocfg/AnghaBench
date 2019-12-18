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
typedef  int /*<<< orphan*/ * PSP_INF_INFORMATION ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupGetInfInformationA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PSP_INF_INFORMATION alloc_inf_info(LPCSTR filename, DWORD search, PDWORD size)
{
    PSP_INF_INFORMATION info;
    BOOL ret;

    ret = SetupGetInfInformationA(filename, search, NULL, 0, size);
    if (!ret)
        return NULL;

    info = HeapAlloc(GetProcessHeap(), 0, *size);
    return info;
}