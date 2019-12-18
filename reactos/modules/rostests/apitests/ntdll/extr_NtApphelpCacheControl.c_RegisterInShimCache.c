#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szPath ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ApphelpCacheServiceUpdate ; 
 int /*<<< orphan*/  CallCacheControl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlDosPathNameToNtPathName_U (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN RegisterInShimCache(BOOLEAN WithMapping)
{
    WCHAR szPath[MAX_PATH];
    UNICODE_STRING ntPath;
    BOOLEAN Result;
    NTSTATUS Status;
    GetModuleFileNameW(NULL, szPath, sizeof(szPath) / sizeof(szPath[0]));
    Result = RtlDosPathNameToNtPathName_U(szPath, &ntPath, NULL, NULL);
    if (!Result)
    {
        DbgPrint("RegisterInShimCache: RtlDosPathNameToNtPathName_U failed\n");
        return FALSE;
    }

    Status = CallCacheControl(&ntPath, WithMapping, ApphelpCacheServiceUpdate);
    if (!NT_SUCCESS(Status))
    {
        DbgPrint("RegisterInShimCache: CallCacheControl failed\n");
        RtlFreeHeap(RtlGetProcessHeap(), 0, ntPath.Buffer);
        return FALSE;
    }
    RtlFreeHeap(RtlGetProcessHeap(), 0, ntPath.Buffer);
    return TRUE;
}