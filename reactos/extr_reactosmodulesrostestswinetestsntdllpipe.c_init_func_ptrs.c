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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* pNtCancelIoFile ; 
 void* pNtCancelIoFileEx ; 
 void* pNtCreateNamedPipeFile ; 
 void* pNtFsControlFile ; 
 void* pNtQueryInformationFile ; 
 void* pNtQueryVolumeInformationFile ; 
 void* pNtSetInformationFile ; 
 void* pOpenThread ; 
 void* pQueueUserAPC ; 
 void* pRtlInitUnicodeString ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static BOOL init_func_ptrs(void)
{
    HMODULE module = GetModuleHandleA("ntdll.dll");

#define loadfunc(name)  if (!(p##name = (void *)GetProcAddress(module, #name))) { \
                            trace("GetProcAddress(%s) failed\n", #name); \
                            return FALSE; \
                        }

    loadfunc(NtFsControlFile)
    loadfunc(NtCreateNamedPipeFile)
    loadfunc(NtQueryInformationFile)
    loadfunc(NtQueryVolumeInformationFile)
    loadfunc(NtSetInformationFile)
    loadfunc(NtCancelIoFile)
    loadfunc(RtlInitUnicodeString)

    /* not fatal */
    pNtCancelIoFileEx = (void *)GetProcAddress(module, "NtCancelIoFileEx");
    module = GetModuleHandleA("kernel32.dll");
    pOpenThread = (void *)GetProcAddress(module, "OpenThread");
    pQueueUserAPC = (void *)GetProcAddress(module, "QueueUserAPC");
    return TRUE;
}