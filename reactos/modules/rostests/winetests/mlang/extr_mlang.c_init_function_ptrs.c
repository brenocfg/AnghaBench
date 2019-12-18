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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* pConvertINetMultiByteToUnicode ; 
 void* pConvertINetUnicodeToMultiByte ; 
 void* pGetCPInfoExA ; 
 void* pLcidToRfc1766A ; 
 void* pRfc1766ToLcidA ; 

__attribute__((used)) static BOOL init_function_ptrs(void)
{
    HMODULE hMlang;

    hMlang = GetModuleHandleA("mlang.dll");
    pConvertINetMultiByteToUnicode = (void *)GetProcAddress(hMlang, "ConvertINetMultiByteToUnicode");
    pConvertINetUnicodeToMultiByte = (void *)GetProcAddress(hMlang, "ConvertINetUnicodeToMultiByte");
    pRfc1766ToLcidA = (void *)GetProcAddress(hMlang, "Rfc1766ToLcidA");
    pLcidToRfc1766A = (void *)GetProcAddress(hMlang, "LcidToRfc1766A");

    pGetCPInfoExA = (void *)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetCPInfoExA");

    return TRUE;
}