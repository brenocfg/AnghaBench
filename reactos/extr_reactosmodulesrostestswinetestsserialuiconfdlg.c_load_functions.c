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
 int /*<<< orphan*/ * pCommConfigDialogA ; 
 int /*<<< orphan*/ * pCommConfigDialogW ; 
 int /*<<< orphan*/ * pGetDefaultCommConfigA ; 
 int /*<<< orphan*/ * pGetDefaultCommConfigW ; 

__attribute__((used)) static LPCSTR load_functions(void)
{
    LPCSTR ptr;

    ptr = "serialui.dll";
    hdll = LoadLibraryA(ptr);
    if (!hdll) return ptr;

    ptr = "drvCommConfigDialogA";
    pCommConfigDialogA = (VOID *) GetProcAddress(hdll, ptr);
    if (!pCommConfigDialogA) return ptr;

    ptr = "drvCommConfigDialogW";
    pCommConfigDialogW = (VOID *) GetProcAddress(hdll, ptr);
    if (!pCommConfigDialogW) return ptr;

    ptr = "drvGetDefaultCommConfigA";
    pGetDefaultCommConfigA = (VOID *) GetProcAddress(hdll, ptr);
    if (!pGetDefaultCommConfigA) return ptr;

    ptr = "drvGetDefaultCommConfigW";
    pGetDefaultCommConfigW = (VOID *) GetProcAddress(hdll, ptr);
    if (!pGetDefaultCommConfigW) return ptr;


    return NULL;
}