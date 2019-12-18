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
 int /*<<< orphan*/  MPR_GET_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WNetCachePassword ; 
 int /*<<< orphan*/  WNetEnumCachedPasswords ; 
 int /*<<< orphan*/  WNetGetCachedPassword ; 
 int /*<<< orphan*/  WNetRemoveCachedPassword ; 
 int /*<<< orphan*/  WNetUseConnectionA ; 

__attribute__((used)) static void InitFunctionPtrs(void)
{
    HMODULE hmpr = GetModuleHandleA("mpr.dll");

    MPR_GET_PROC(WNetCachePassword);
    MPR_GET_PROC(WNetGetCachedPassword);
    MPR_GET_PROC(WNetEnumCachedPasswords);
    MPR_GET_PROC(WNetRemoveCachedPassword);
    MPR_GET_PROC(WNetUseConnectionA);
}