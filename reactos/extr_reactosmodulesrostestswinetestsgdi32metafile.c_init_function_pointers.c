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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GDI_GET_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  GetRelAbs ; 
 int /*<<< orphan*/  SetDCBrushColor ; 
 int /*<<< orphan*/  SetDCPenColor ; 
 int /*<<< orphan*/  SetRelAbs ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pGetRelAbs ; 
 int /*<<< orphan*/ * pSetRelAbs ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hGDI;

    pGetRelAbs = NULL;
    pSetRelAbs = NULL;

    hGDI = GetModuleHandleA("gdi32.dll");
    assert(hGDI);
    GDI_GET_PROC(GetRelAbs);
    GDI_GET_PROC(SetRelAbs);
    GDI_GET_PROC(SetDCBrushColor);
    GDI_GET_PROC(SetDCPenColor);
}