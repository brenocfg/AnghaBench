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

/* Variables and functions */
 scalar_t__ GetProcAddress (scalar_t__,char*) ; 
 scalar_t__ LoadLibraryA (char*) ; 
 scalar_t__ hntdll ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 void* pNtAddAtom ; 
 void* pNtQueryInformationAtom ; 
 void* pRtlAddAtomToAtomTable ; 
 void* pRtlCreateAtomTable ; 
 void* pRtlDeleteAtomFromAtomTable ; 
 void* pRtlDestroyAtomTable ; 
 void* pRtlEmptyAtomTable ; 
 void* pRtlLookupAtomInAtomTable ; 
 void* pRtlPinAtomInAtomTable ; 
 void* pRtlQueryAtomInAtomTable ; 

__attribute__((used)) static void InitFunctionPtr(void)
{
    hntdll = LoadLibraryA("ntdll.dll");
    ok(hntdll != 0, "Unable to load ntdll.dll\n");

    if (hntdll)
    {
        pRtlCreateAtomTable = (void *)GetProcAddress(hntdll, "RtlCreateAtomTable");
        pRtlDestroyAtomTable = (void *)GetProcAddress(hntdll, "RtlDestroyAtomTable");
        pRtlEmptyAtomTable = (void *)GetProcAddress(hntdll, "RtlEmptyAtomTable");
        pRtlAddAtomToAtomTable = (void *)GetProcAddress(hntdll, "RtlAddAtomToAtomTable");
        pRtlDeleteAtomFromAtomTable = (void *)GetProcAddress(hntdll, "RtlDeleteAtomFromAtomTable");
        pRtlLookupAtomInAtomTable = (void *)GetProcAddress(hntdll, "RtlLookupAtomInAtomTable");
        pRtlPinAtomInAtomTable = (void *)GetProcAddress(hntdll, "RtlPinAtomInAtomTable");
        pRtlQueryAtomInAtomTable = (void *)GetProcAddress(hntdll, "RtlQueryAtomInAtomTable");

        pNtAddAtom = (void *)GetProcAddress(hntdll, "NtAddAtom");
        pNtQueryInformationAtom = (void *)GetProcAddress(hntdll, "NtQueryInformationAtom");
    }
}