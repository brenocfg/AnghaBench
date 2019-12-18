#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {scalar_t__ pwszPortName; } ;
struct TYPE_5__ {int fPortType; scalar_t__ Reserved; } ;
typedef  scalar_t__ PWSTR ;
typedef  TYPE_1__* PPORT_INFO_2W ;
typedef  int /*<<< orphan*/  PORT_INFO_2W ;
typedef  TYPE_2__* PLOCALMON_PORT ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  scalar_t__ PCWSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 int PORT_TYPE_READ ; 
 int PORT_TYPE_WRITE ; 
 int /*<<< orphan*/  PackStrings (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cbLocalMonitor ; 
 scalar_t__ cbLocalPort ; 
 int /*<<< orphan*/  dwPortInfo2Offsets ; 
 scalar_t__ pwszLocalMonitor ; 
 scalar_t__ pwszLocalPort ; 
 int wcslen (scalar_t__) ; 

__attribute__((used)) static void
_LocalmonGetPortLevel2(PLOCALMON_PORT pPort, PPORT_INFO_2W* ppPortInfo, PBYTE* ppPortInfoEnd, PDWORD pcbNeeded)
{
    DWORD cbPortName;
    PCWSTR pwszStrings[3];

    // Calculate the string lengths.
    if (!ppPortInfo)
    {
        cbPortName = (wcslen(pPort->pwszPortName) + 1) * sizeof(WCHAR);

        *pcbNeeded += sizeof(PORT_INFO_2W) + cbPortName + cbLocalMonitor + cbLocalPort;
        return;
    }

    // All local ports are writable and readable.
    (*ppPortInfo)->fPortType = PORT_TYPE_WRITE | PORT_TYPE_READ;
    (*ppPortInfo)->Reserved = 0;

    // Set the pPortName field.
    pwszStrings[0] = pPort->pwszPortName;

    // Set the pMonitorName field.
    pwszStrings[1] = (PWSTR)pwszLocalMonitor;

    // Set the pDescription field.
    pwszStrings[2] = (PWSTR)pwszLocalPort;

    // Copy the structure and advance to the next one in the output buffer.
    *ppPortInfoEnd = PackStrings(pwszStrings, (PBYTE)(*ppPortInfo), dwPortInfo2Offsets, *ppPortInfoEnd);
    (*ppPortInfo)++;
}