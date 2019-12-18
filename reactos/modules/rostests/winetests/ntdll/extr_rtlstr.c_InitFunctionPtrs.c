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
 void* pRtlAnsiStringToUnicodeString ; 
 void* pRtlAppendAsciizToString ; 
 void* pRtlAppendStringToString ; 
 void* pRtlAppendUnicodeStringToString ; 
 void* pRtlAppendUnicodeToString ; 
 void* pRtlCharToInteger ; 
 void* pRtlCompareUnicodeString ; 
 void* pRtlCompareUnicodeStrings ; 
 void* pRtlCopyString ; 
 void* pRtlCreateUnicodeString ; 
 void* pRtlCreateUnicodeStringFromAsciiz ; 
 void* pRtlDowncaseUnicodeString ; 
 void* pRtlDuplicateUnicodeString ; 
 void* pRtlEqualUnicodeString ; 
 void* pRtlFindCharInUnicodeString ; 
 void* pRtlFreeAnsiString ; 
 void* pRtlFreeUnicodeString ; 
 void* pRtlGUIDFromString ; 
 void* pRtlHashUnicodeString ; 
 void* pRtlInitAnsiString ; 
 void* pRtlInitString ; 
 void* pRtlInitUnicodeString ; 
 void* pRtlInitUnicodeStringEx ; 
 void* pRtlIntegerToChar ; 
 void* pRtlIntegerToUnicodeString ; 
 void* pRtlIsTextUnicode ; 
 void* pRtlMultiAppendUnicodeStringBuffer ; 
 void* pRtlStringFromGUID ; 
 void* pRtlUTF8ToUnicodeN ; 
 void* pRtlUnicodeStringToAnsiString ; 
 void* pRtlUnicodeStringToInteger ; 
 void* pRtlUnicodeToUTF8N ; 
 void* pRtlUpcaseUnicodeChar ; 
 void* pRtlUpcaseUnicodeString ; 
 void* pRtlUpperChar ; 
 void* pRtlUpperString ; 
 void* pRtlValidateUnicodeString ; 

__attribute__((used)) static void InitFunctionPtrs(void)
{
    hntdll = LoadLibraryA("ntdll.dll");
    ok(hntdll != 0, "LoadLibrary failed\n");
    if (hntdll) {
	pRtlAnsiStringToUnicodeString = (void *)GetProcAddress(hntdll, "RtlAnsiStringToUnicodeString");
	pRtlAppendAsciizToString = (void *)GetProcAddress(hntdll, "RtlAppendAsciizToString");
	pRtlAppendStringToString = (void *)GetProcAddress(hntdll, "RtlAppendStringToString");
	pRtlAppendUnicodeStringToString = (void *)GetProcAddress(hntdll, "RtlAppendUnicodeStringToString");
	pRtlAppendUnicodeToString = (void *)GetProcAddress(hntdll, "RtlAppendUnicodeToString");
	pRtlCharToInteger = (void *)GetProcAddress(hntdll, "RtlCharToInteger");
	pRtlCompareUnicodeString = (void *)GetProcAddress(hntdll, "RtlCompareUnicodeString");
	pRtlCompareUnicodeStrings = (void *)GetProcAddress(hntdll, "RtlCompareUnicodeStrings");
	pRtlCopyString = (void *)GetProcAddress(hntdll, "RtlCopyString");
	pRtlCreateUnicodeString = (void *)GetProcAddress(hntdll, "RtlCreateUnicodeString");
	pRtlCreateUnicodeStringFromAsciiz = (void *)GetProcAddress(hntdll, "RtlCreateUnicodeStringFromAsciiz");
	pRtlDowncaseUnicodeString = (void *)GetProcAddress(hntdll, "RtlDowncaseUnicodeString");
	pRtlDuplicateUnicodeString = (void *)GetProcAddress(hntdll, "RtlDuplicateUnicodeString");
	pRtlEqualUnicodeString = (void *)GetProcAddress(hntdll, "RtlEqualUnicodeString");
	pRtlFindCharInUnicodeString = (void *)GetProcAddress(hntdll, "RtlFindCharInUnicodeString");
	pRtlFreeAnsiString = (void *)GetProcAddress(hntdll, "RtlFreeAnsiString");
	pRtlFreeUnicodeString = (void *)GetProcAddress(hntdll, "RtlFreeUnicodeString");
	pRtlInitAnsiString = (void *)GetProcAddress(hntdll, "RtlInitAnsiString");
	pRtlInitString = (void *)GetProcAddress(hntdll, "RtlInitString");
	pRtlInitUnicodeString = (void *)GetProcAddress(hntdll, "RtlInitUnicodeString");
	pRtlInitUnicodeStringEx = (void *)GetProcAddress(hntdll, "RtlInitUnicodeStringEx");
	pRtlIntegerToChar = (void *)GetProcAddress(hntdll, "RtlIntegerToChar");
	pRtlIntegerToUnicodeString = (void *)GetProcAddress(hntdll, "RtlIntegerToUnicodeString");
	pRtlMultiAppendUnicodeStringBuffer = (void *)GetProcAddress(hntdll, "RtlMultiAppendUnicodeStringBuffer");
	pRtlUnicodeStringToAnsiString = (void *)GetProcAddress(hntdll, "RtlUnicodeStringToAnsiString");
	pRtlUnicodeStringToInteger = (void *)GetProcAddress(hntdll, "RtlUnicodeStringToInteger");
	pRtlUpcaseUnicodeChar = (void *)GetProcAddress(hntdll, "RtlUpcaseUnicodeChar");
	pRtlUpcaseUnicodeString = (void *)GetProcAddress(hntdll, "RtlUpcaseUnicodeString");
	pRtlUpperChar = (void *)GetProcAddress(hntdll, "RtlUpperChar");
	pRtlUpperString = (void *)GetProcAddress(hntdll, "RtlUpperString");
	pRtlValidateUnicodeString = (void *)GetProcAddress(hntdll, "RtlValidateUnicodeString");
	pRtlGUIDFromString = (void *)GetProcAddress(hntdll, "RtlGUIDFromString");
	pRtlStringFromGUID = (void *)GetProcAddress(hntdll, "RtlStringFromGUID");
	pRtlIsTextUnicode = (void *)GetProcAddress(hntdll, "RtlIsTextUnicode");
        pRtlHashUnicodeString = (void*)GetProcAddress(hntdll, "RtlHashUnicodeString");
        pRtlUnicodeToUTF8N = (void*)GetProcAddress(hntdll, "RtlUnicodeToUTF8N");
        pRtlUTF8ToUnicodeN = (void*)GetProcAddress(hntdll, "RtlUTF8ToUnicodeN");
    }
}