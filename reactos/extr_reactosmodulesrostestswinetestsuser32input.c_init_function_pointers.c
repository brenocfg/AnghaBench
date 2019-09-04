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
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 void* pGetMouseMovePointsEx ; 
 void* pGetRawInputDeviceList ; 
 void* pGetWindowRgnBox ; 
 void* pSendInput ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hdll = GetModuleHandleA("user32");

#define GET_PROC(func) \
    p ## func = (void*)GetProcAddress(hdll, #func); \
    if(!p ## func) \
      trace("GetProcAddress(%s) failed\n", #func);

    GET_PROC(SendInput)
    GET_PROC(GetMouseMovePointsEx)
    GET_PROC(GetRawInputDeviceList)
    GET_PROC(GetWindowRgnBox)

#undef GET_PROC
}