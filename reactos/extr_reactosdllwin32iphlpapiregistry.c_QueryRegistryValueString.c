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
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * QueryRegistryValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/ * TerminateReadString (int /*<<< orphan*/ *,scalar_t__) ; 

PWCHAR QueryRegistryValueString( HANDLE RegHandle, PWCHAR ValueName )
{
    PWCHAR String, TerminatedString;
    DWORD Type, Length;
    
    String = QueryRegistryValue(RegHandle, ValueName, &Type, &Length);
    if (!String) return NULL;
    if (Type != REG_SZ)
    {
        DbgPrint("Type mismatch for %S (%d != %d)\n", ValueName, Type, REG_SZ);
        //HeapFree(GetProcessHeap(), 0, String);
        //return NULL;
    }
    
    TerminatedString = TerminateReadString(String, Length);
    HeapFree(GetProcessHeap(), 0, String);
    if (!TerminatedString) return NULL;
    
    return TerminatedString;
}