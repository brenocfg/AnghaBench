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
 void* pCopyFile2 ; 
 void* pCreateFile2 ; 
 void* pFindFirstFileExA ; 
 void* pGetFileInformationByHandleEx ; 
 void* pGetFinalPathNameByHandleA ; 
 void* pGetFinalPathNameByHandleW ; 
 void* pGetSystemWindowsDirectoryA ; 
 void* pGetVolumeNameForVolumeMountPointA ; 
 void* pNtCreateFile ; 
 void* pOpenFileById ; 
 void* pQueueUserAPC ; 
 void* pReplaceFileA ; 
 void* pReplaceFileW ; 
 void* pRtlAnsiStringToUnicodeString ; 
 void* pRtlDosPathNameToNtPathName_U ; 
 void* pRtlFreeUnicodeString ; 
 void* pRtlInitAnsiString ; 
 void* pSetFileInformationByHandle ; 
 void* pSetFileValidData ; 

__attribute__((used)) static void InitFunctionPointers(void)
{
    HMODULE hntdll = GetModuleHandleA("ntdll");
    HMODULE hkernel32 = GetModuleHandleA("kernel32");

    pNtCreateFile = (void *)GetProcAddress(hntdll, "NtCreateFile");
    pRtlDosPathNameToNtPathName_U = (void *)GetProcAddress(hntdll, "RtlDosPathNameToNtPathName_U");
    pRtlAnsiStringToUnicodeString = (void *)GetProcAddress(hntdll, "RtlAnsiStringToUnicodeString");
    pRtlInitAnsiString = (void *)GetProcAddress(hntdll, "RtlInitAnsiString");
    pRtlFreeUnicodeString = (void *)GetProcAddress(hntdll, "RtlFreeUnicodeString");

    pFindFirstFileExA=(void*)GetProcAddress(hkernel32, "FindFirstFileExA");
    pReplaceFileA=(void*)GetProcAddress(hkernel32, "ReplaceFileA");
    pReplaceFileW=(void*)GetProcAddress(hkernel32, "ReplaceFileW");
    pGetSystemWindowsDirectoryA=(void*)GetProcAddress(hkernel32, "GetSystemWindowsDirectoryA");
    pGetVolumeNameForVolumeMountPointA = (void *) GetProcAddress(hkernel32, "GetVolumeNameForVolumeMountPointA");
    pQueueUserAPC = (void *) GetProcAddress(hkernel32, "QueueUserAPC");
    pGetFileInformationByHandleEx = (void *) GetProcAddress(hkernel32, "GetFileInformationByHandleEx");
    pOpenFileById = (void *) GetProcAddress(hkernel32, "OpenFileById");
    pSetFileValidData = (void *) GetProcAddress(hkernel32, "SetFileValidData");
    pCopyFile2 = (void *) GetProcAddress(hkernel32, "CopyFile2");
    pCreateFile2 = (void *) GetProcAddress(hkernel32, "CreateFile2");
    pGetFinalPathNameByHandleA = (void *) GetProcAddress(hkernel32, "GetFinalPathNameByHandleA");
    pGetFinalPathNameByHandleW = (void *) GetProcAddress(hkernel32, "GetFinalPathNameByHandleW");
    pSetFileInformationByHandle = (void *) GetProcAddress(hkernel32, "SetFileInformationByHandle");
}