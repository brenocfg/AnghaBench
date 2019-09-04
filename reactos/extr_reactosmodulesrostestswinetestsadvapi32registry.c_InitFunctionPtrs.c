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
 int /*<<< orphan*/  ADVAPI32_GET_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RegCopyTreeA ; 
 int /*<<< orphan*/  RegDeleteKeyExA ; 
 int /*<<< orphan*/  RegDeleteKeyValueA ; 
 int /*<<< orphan*/  RegDeleteTreeA ; 
 int /*<<< orphan*/  RegGetValueA ; 
 int /*<<< orphan*/  RegSetKeyValueW ; 
 void* pIsWow64Process ; 
 void* pNtDeleteKey ; 
 void* pRtlFormatCurrentUserKeyPath ; 
 void* pRtlFreeUnicodeString ; 

__attribute__((used)) static void InitFunctionPtrs(void)
{
    HMODULE hntdll = GetModuleHandleA("ntdll.dll");
    HMODULE hkernel32 = GetModuleHandleA("kernel32.dll");
    HMODULE hadvapi32 = GetModuleHandleA("advapi32.dll");

    /* This function was introduced with Windows 2003 SP1 */
    ADVAPI32_GET_PROC(RegGetValueA);
    ADVAPI32_GET_PROC(RegCopyTreeA);
    ADVAPI32_GET_PROC(RegDeleteTreeA);
    ADVAPI32_GET_PROC(RegDeleteKeyExA);
    ADVAPI32_GET_PROC(RegDeleteKeyValueA);
    ADVAPI32_GET_PROC(RegSetKeyValueW);

    pIsWow64Process = (void *)GetProcAddress( hkernel32, "IsWow64Process" );
    pRtlFormatCurrentUserKeyPath = (void *)GetProcAddress( hntdll, "RtlFormatCurrentUserKeyPath" );
    pRtlFreeUnicodeString = (void *)GetProcAddress(hntdll, "RtlFreeUnicodeString");
    pNtDeleteKey = (void *)GetProcAddress( hntdll, "NtDeleteKey" );
}