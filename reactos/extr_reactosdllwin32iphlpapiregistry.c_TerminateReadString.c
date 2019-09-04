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
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UNICODE_NULL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

PWCHAR TerminateReadString(PWCHAR String, DWORD Length)
{
    PWCHAR TerminatedString;
    
    TerminatedString = HeapAlloc(GetProcessHeap(), 0, Length + sizeof(WCHAR));
    if (TerminatedString == NULL)
        return NULL;

    memcpy(TerminatedString, String, Length);

    TerminatedString[Length / sizeof(WCHAR)] = UNICODE_NULL;
    
    return TerminatedString;
}