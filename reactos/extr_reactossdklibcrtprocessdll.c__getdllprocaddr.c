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
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/ * FARPROC ;

/* Variables and functions */
 int /*<<< orphan*/ * GetProcAddress (int /*<<< orphan*/ ,char*) ; 

FARPROC _getdllprocaddr(intptr_t hModule, char* lpProcName, intptr_t iOrdinal)
{
	if (lpProcName != NULL)
		return GetProcAddress((HMODULE) hModule, lpProcName);
	else
		return GetProcAddress((HMODULE) hModule, (LPSTR)iOrdinal);
   	return (NULL);
}