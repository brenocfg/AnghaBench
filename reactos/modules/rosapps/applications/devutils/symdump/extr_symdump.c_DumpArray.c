#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  dwModuleBase; int /*<<< orphan*/  hProcess; } ;
typedef  TYPE_1__* PENUMINFO ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DumpType (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SymGetTypeInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI_GET_TYPE ; 

VOID
DumpArray(DWORD dwTypeIndex, PENUMINFO pei, INT indent)
{
	DWORD dwTypeId;

	SymGetTypeInfo(pei->hProcess, pei->dwModuleBase, dwTypeIndex, TI_GET_TYPE, &dwTypeId);
	DumpType(dwTypeId, pei, indent, FALSE);
}