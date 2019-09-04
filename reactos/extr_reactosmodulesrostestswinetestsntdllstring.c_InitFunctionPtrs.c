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
 void* pRtlCreateUnicodeStringFromAsciiz ; 
 void* pRtlFreeAnsiString ; 
 void* pRtlFreeUnicodeString ; 
 void* pRtlUnicodeStringToAnsiString ; 
 void* p__snprintf ; 
 void* p_atoi64 ; 
 void* p_bsearch ; 
 void* p_i64toa ; 
 void* p_i64tow ; 
 void* p_itoa ; 
 void* p_itow ; 
 void* p_ltoa ; 
 void* p_ltow ; 
 void* p_qsort ; 
 void* p_ui64toa ; 
 void* p_ui64tow ; 
 void* p_ultoa ; 
 void* p_ultow ; 
 void* p_wcschr ; 
 void* p_wcslwr ; 
 void* p_wcsrchr ; 
 void* p_wcsupr ; 
 void* p_wtoi ; 
 void* p_wtoi64 ; 
 void* p_wtol ; 
 void* patoi ; 
 void* patol ; 

__attribute__((used)) static void InitFunctionPtrs(void)
{
    hntdll = LoadLibraryA("ntdll.dll");
    ok(hntdll != 0, "LoadLibrary failed\n");
    if (hntdll) {
	pRtlUnicodeStringToAnsiString = (void *)GetProcAddress(hntdll, "RtlUnicodeStringToAnsiString");
	pRtlFreeAnsiString = (void *)GetProcAddress(hntdll, "RtlFreeAnsiString");
	pRtlCreateUnicodeStringFromAsciiz = (void *)GetProcAddress(hntdll, "RtlCreateUnicodeStringFromAsciiz");
	pRtlFreeUnicodeString = (void *)GetProcAddress(hntdll, "RtlFreeUnicodeString");

	patoi = (void *)GetProcAddress(hntdll, "atoi");
	patol = (void *)GetProcAddress(hntdll, "atol");
	p_atoi64 = (void *)GetProcAddress(hntdll, "_atoi64");
	p_itoa = (void *)GetProcAddress(hntdll, "_itoa");
	p_ltoa = (void *)GetProcAddress(hntdll, "_ltoa");
	p_ultoa = (void *)GetProcAddress(hntdll, "_ultoa");
	p_i64toa = (void *)GetProcAddress(hntdll, "_i64toa");
	p_ui64toa = (void *)GetProcAddress(hntdll, "_ui64toa");

	p_wtoi = (void *)GetProcAddress(hntdll, "_wtoi");
	p_wtol = (void *)GetProcAddress(hntdll, "_wtol");
	p_wtoi64 = (void *)GetProcAddress(hntdll, "_wtoi64");
	p_itow = (void *)GetProcAddress(hntdll, "_itow");
	p_ltow = (void *)GetProcAddress(hntdll, "_ltow");
	p_ultow = (void *)GetProcAddress(hntdll, "_ultow");
	p_i64tow = (void *)GetProcAddress(hntdll, "_i64tow");
	p_ui64tow = (void *)GetProcAddress(hntdll, "_ui64tow");

        p_wcslwr = (void *)GetProcAddress(hntdll, "_wcslwr");
        p_wcsupr = (void *)GetProcAddress(hntdll, "_wcsupr");

	p_wcschr= (void *)GetProcAddress(hntdll, "wcschr");
	p_wcsrchr= (void *)GetProcAddress(hntdll, "wcsrchr");
	p_qsort= (void *)GetProcAddress(hntdll, "qsort");
	p_bsearch= (void *)GetProcAddress(hntdll, "bsearch");

        p__snprintf = (void *)GetProcAddress(hntdll, "_snprintf");
    } /* if */
}