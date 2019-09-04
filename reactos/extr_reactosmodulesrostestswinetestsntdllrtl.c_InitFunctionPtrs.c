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
 scalar_t__ hkernel32 ; 
 scalar_t__ hntdll ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 void* pIsWow64Process ; 
 void* pLdrAddRefDll ; 
 void* pLdrEnumerateLoadedModules ; 
 void* pLdrLockLoaderLock ; 
 void* pLdrProcessRelocationBlock ; 
 void* pLdrRegisterDllNotification ; 
 void* pLdrUnlockLoaderLock ; 
 void* pLdrUnregisterDllNotification ; 
 void* pRtlAbsoluteToSelfRelativeSD ; 
 void* pRtlAllocateAndInitializeSid ; 
 void* pRtlAllocateHandle ; 
 void* pRtlAreAllAccessesGranted ; 
 void* pRtlAreAnyAccessesGranted ; 
 void* pRtlCompareMemory ; 
 void* pRtlCompareMemoryUlong ; 
 void* pRtlCompressBuffer ; 
 void* pRtlComputeCrc32 ; 
 void* pRtlDecompressBuffer ; 
 void* pRtlDecompressFragment ; 
 void* pRtlDeleteTimer ; 
 void* pRtlDestroyHandleTable ; 
 void* pRtlFillMemory ; 
 void* pRtlFillMemoryUlong ; 
 void* pRtlFreeHandle ; 
 void* pRtlFreeSid ; 
 void* pRtlGetCompressionWorkSpaceSize ; 
 void* pRtlGetThreadErrorMode ; 
 void* pRtlInitializeCriticalSectionEx ; 
 void* pRtlInitializeHandleTable ; 
 void* pRtlIpv4AddressToStringA ; 
 void* pRtlIpv4AddressToStringExA ; 
 void* pRtlIpv4StringToAddressA ; 
 void* pRtlIpv4StringToAddressExA ; 
 void* pRtlIpv6AddressToStringA ; 
 void* pRtlIpv6AddressToStringExA ; 
 void* pRtlIpv6StringToAddressA ; 
 void* pRtlIpv6StringToAddressExA ; 
 void* pRtlIpv6StringToAddressExW ; 
 void* pRtlIpv6StringToAddressW ; 
 void* pRtlIsCriticalSectionLocked ; 
 void* pRtlIsCriticalSectionLockedByThread ; 
 void* pRtlIsValidIndexHandle ; 
 void* pRtlMakeSelfRelativeSD ; 
 void* pRtlMoveMemory ; 
 void* pRtlMultiByteToUnicodeN ; 
 void* pRtlQueryPackageIdentity ; 
 void* pRtlRandom ; 
 void* pRtlSetThreadErrorMode ; 
 void* pRtlUlonglongByteSwap ; 
 void* pRtlUniform ; 
 void* pRtlZeroMemory ; 
 int /*<<< orphan*/  src ; 
 scalar_t__ src_aligned_block ; 
 int /*<<< orphan*/  src_src ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void InitFunctionPtrs(void)
{
    hntdll = LoadLibraryA("ntdll.dll");
    ok(hntdll != 0, "LoadLibrary failed\n");
    if (hntdll) {
	pRtlCompareMemory = (void *)GetProcAddress(hntdll, "RtlCompareMemory");
	pRtlCompareMemoryUlong = (void *)GetProcAddress(hntdll, "RtlCompareMemoryUlong");
        pRtlDeleteTimer = (void *)GetProcAddress(hntdll, "RtlDeleteTimer");
	pRtlMoveMemory = (void *)GetProcAddress(hntdll, "RtlMoveMemory");
	pRtlFillMemory = (void *)GetProcAddress(hntdll, "RtlFillMemory");
	pRtlFillMemoryUlong = (void *)GetProcAddress(hntdll, "RtlFillMemoryUlong");
	pRtlZeroMemory = (void *)GetProcAddress(hntdll, "RtlZeroMemory");
	pRtlUlonglongByteSwap = (void *)GetProcAddress(hntdll, "RtlUlonglongByteSwap");
	pRtlUniform = (void *)GetProcAddress(hntdll, "RtlUniform");
	pRtlRandom = (void *)GetProcAddress(hntdll, "RtlRandom");
	pRtlAreAllAccessesGranted = (void *)GetProcAddress(hntdll, "RtlAreAllAccessesGranted");
	pRtlAreAnyAccessesGranted = (void *)GetProcAddress(hntdll, "RtlAreAnyAccessesGranted");
	pRtlComputeCrc32 = (void *)GetProcAddress(hntdll, "RtlComputeCrc32");
	pRtlInitializeHandleTable = (void *)GetProcAddress(hntdll, "RtlInitializeHandleTable");
	pRtlIsValidIndexHandle = (void *)GetProcAddress(hntdll, "RtlIsValidIndexHandle");
	pRtlDestroyHandleTable = (void *)GetProcAddress(hntdll, "RtlDestroyHandleTable");
	pRtlAllocateHandle = (void *)GetProcAddress(hntdll, "RtlAllocateHandle");
	pRtlFreeHandle = (void *)GetProcAddress(hntdll, "RtlFreeHandle");
        pRtlAllocateAndInitializeSid = (void *)GetProcAddress(hntdll, "RtlAllocateAndInitializeSid");
        pRtlFreeSid = (void *)GetProcAddress(hntdll, "RtlFreeSid");
        pRtlGetThreadErrorMode = (void *)GetProcAddress(hntdll, "RtlGetThreadErrorMode");
        pRtlSetThreadErrorMode = (void *)GetProcAddress(hntdll, "RtlSetThreadErrorMode");
        pLdrProcessRelocationBlock  = (void *)GetProcAddress(hntdll, "LdrProcessRelocationBlock");
        pRtlIpv4AddressToStringA = (void *)GetProcAddress(hntdll, "RtlIpv4AddressToStringA");
        pRtlIpv4AddressToStringExA = (void *)GetProcAddress(hntdll, "RtlIpv4AddressToStringExA");
        pRtlIpv4StringToAddressA = (void *)GetProcAddress(hntdll, "RtlIpv4StringToAddressA");
        pRtlIpv4StringToAddressExA = (void *)GetProcAddress(hntdll, "RtlIpv4StringToAddressExA");
        pRtlIpv6AddressToStringA = (void *)GetProcAddress(hntdll, "RtlIpv6AddressToStringA");
        pRtlIpv6AddressToStringExA = (void *)GetProcAddress(hntdll, "RtlIpv6AddressToStringExA");
        pRtlIpv6StringToAddressA = (void *)GetProcAddress(hntdll, "RtlIpv6StringToAddressA");
        pRtlIpv6StringToAddressW = (void *)GetProcAddress(hntdll, "RtlIpv6StringToAddressW");
        pRtlIpv6StringToAddressExA = (void *)GetProcAddress(hntdll, "RtlIpv6StringToAddressExA");
        pRtlIpv6StringToAddressExW = (void *)GetProcAddress(hntdll, "RtlIpv6StringToAddressExW");
        pLdrAddRefDll = (void *)GetProcAddress(hntdll, "LdrAddRefDll");
        pLdrLockLoaderLock = (void *)GetProcAddress(hntdll, "LdrLockLoaderLock");
        pLdrUnlockLoaderLock = (void *)GetProcAddress(hntdll, "LdrUnlockLoaderLock");
        pRtlMultiByteToUnicodeN = (void *)GetProcAddress(hntdll, "RtlMultiByteToUnicodeN");
        pRtlGetCompressionWorkSpaceSize = (void *)GetProcAddress(hntdll, "RtlGetCompressionWorkSpaceSize");
        pRtlDecompressBuffer = (void *)GetProcAddress(hntdll, "RtlDecompressBuffer");
        pRtlDecompressFragment = (void *)GetProcAddress(hntdll, "RtlDecompressFragment");
        pRtlCompressBuffer = (void *)GetProcAddress(hntdll, "RtlCompressBuffer");
        pRtlIsCriticalSectionLocked = (void *)GetProcAddress(hntdll, "RtlIsCriticalSectionLocked");
        pRtlIsCriticalSectionLockedByThread = (void *)GetProcAddress(hntdll, "RtlIsCriticalSectionLockedByThread");
        pRtlInitializeCriticalSectionEx = (void *)GetProcAddress(hntdll, "RtlInitializeCriticalSectionEx");
        pLdrEnumerateLoadedModules = (void *)GetProcAddress(hntdll, "LdrEnumerateLoadedModules");
        pRtlQueryPackageIdentity = (void *)GetProcAddress(hntdll, "RtlQueryPackageIdentity");
        pRtlMakeSelfRelativeSD = (void *)GetProcAddress(hntdll, "RtlMakeSelfRelativeSD");
        pRtlAbsoluteToSelfRelativeSD = (void *)GetProcAddress(hntdll, "RtlAbsoluteToSelfRelativeSD");
        pLdrRegisterDllNotification = (void *)GetProcAddress(hntdll, "LdrRegisterDllNotification");
        pLdrUnregisterDllNotification = (void *)GetProcAddress(hntdll, "LdrUnregisterDllNotification");
    }
    hkernel32 = LoadLibraryA("kernel32.dll");
    ok(hkernel32 != 0, "LoadLibrary failed\n");
    if (hkernel32) {
        pIsWow64Process = (void *)GetProcAddress(hkernel32, "IsWow64Process");
    }
    strcpy((char*)src_aligned_block, src_src);
    ok(strlen(src) == 15, "Source must be 16 bytes long!\n");
}