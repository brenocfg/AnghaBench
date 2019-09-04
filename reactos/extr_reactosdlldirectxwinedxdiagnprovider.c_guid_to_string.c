#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * Data4; int /*<<< orphan*/  Data3; int /*<<< orphan*/  Data2; int /*<<< orphan*/  Data1; } ;
typedef  TYPE_1__* REFGUID ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  szGUIDFmt ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPWSTR guid_to_string(LPWSTR lpwstr, REFGUID lpcguid)
{
    wsprintfW(lpwstr, szGUIDFmt, lpcguid->Data1, lpcguid->Data2,
        lpcguid->Data3, lpcguid->Data4[0], lpcguid->Data4[1],
        lpcguid->Data4[2], lpcguid->Data4[3], lpcguid->Data4[4],
        lpcguid->Data4[5], lpcguid->Data4[6], lpcguid->Data4[7]);

    return lpwstr;
}