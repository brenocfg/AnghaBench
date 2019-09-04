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
 int /*<<< orphan*/  GET_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  GetProductInfo ; 
 int /*<<< orphan*/  RtlGetVersion ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hmod;

    hmod = GetModuleHandleA("kernel32.dll");

    GET_PROC(GetProductInfo);

    hmod = GetModuleHandleA("ntdll.dll");

    GET_PROC(RtlGetVersion);
}