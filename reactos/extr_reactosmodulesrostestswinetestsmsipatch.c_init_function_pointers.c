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
 void* pMsiApplyPatchA ; 
 void* pMsiEnumPatchesExA ; 
 void* pMsiGetPatchInfoExA ; 
 void* pOpenProcessToken ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void init_function_pointers( void )
{
    HMODULE hmsi = GetModuleHandleA( "msi.dll" );
    HMODULE hadvapi32 = GetModuleHandleA( "advapi32.dll" );

#define GET_PROC( mod, func ) \
    p ## func = (void *)GetProcAddress( mod, #func ); \
    if (!p ## func) \
        trace( "GetProcAddress(%s) failed\n", #func );

    GET_PROC( hmsi, MsiApplyPatchA );
    GET_PROC( hmsi, MsiGetPatchInfoExA );
    GET_PROC( hmsi, MsiEnumPatchesExA );

    GET_PROC( hadvapi32, OpenProcessToken );
#undef GET_PROC
}