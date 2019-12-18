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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  pwszPortName; } ;
typedef  scalar_t__ PPORT_INFO_1W ;
typedef  int /*<<< orphan*/  PORT_INFO_1W ;
typedef  TYPE_1__* PLOCALMON_PORT ;
typedef  int* PDWORD ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PackStrings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwPortInfo1Offsets ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_LocalmonGetPortLevel1(PLOCALMON_PORT pPort, PPORT_INFO_1W* ppPortInfo, PBYTE* ppPortInfoEnd, PDWORD pcbNeeded)
{
    DWORD cbPortName;
    PCWSTR pwszStrings[1];

    // Calculate the string lengths.
    if (!ppPortInfo)
    {
        cbPortName = (wcslen(pPort->pwszPortName) + 1) * sizeof(WCHAR);

        *pcbNeeded += sizeof(PORT_INFO_1W) + cbPortName;
        return;
    }

    // Set the pName field.
    pwszStrings[0] = pPort->pwszPortName;

    // Copy the structure and advance to the next one in the output buffer.
    *ppPortInfoEnd = PackStrings(pwszStrings, (PBYTE)(*ppPortInfo), dwPortInfo1Offsets, *ppPortInfoEnd);
    (*ppPortInfo)++;
}