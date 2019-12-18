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
typedef  int /*<<< orphan*/  VOID ;
typedef  char* LPCSTR ;

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  hdll ; 
 int /*<<< orphan*/ * pInitializePrintMonitorUI ; 

__attribute__((used)) static LPCSTR load_functions(void)
{
    LPCSTR  ptr;

    ptr = "localui.dll";
    hdll = LoadLibraryA(ptr);
    if (!hdll) return ptr;

    ptr = "InitializePrintMonitorUI";
    pInitializePrintMonitorUI = (VOID *) GetProcAddress(hdll, ptr);
    if (!pInitializePrintMonitorUI) return ptr;

    return NULL;
}