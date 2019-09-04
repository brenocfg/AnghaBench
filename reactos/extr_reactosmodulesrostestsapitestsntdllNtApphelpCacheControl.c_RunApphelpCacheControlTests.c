#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szPath ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_9__ {void* ImageHandle; TYPE_1__ ImageName; } ;
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  void* HANDLE ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_2__ APPHELP_CACHE_SERVICE_LOOKUP ;

/* Variables and functions */
 int /*<<< orphan*/  ApphelpCacheServiceLookup ; 
 int /*<<< orphan*/  CallCacheControl (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckValidation (TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InitEnv (TYPE_1__*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RequestAddition (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RtlDosPathNameToNtPathName_U (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_ntstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtApphelpCacheControl (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void RunApphelpCacheControlTests(SC_HANDLE service_handle)
{
    WCHAR szPath[MAX_PATH];
    UNICODE_STRING ntPath;
    BOOLEAN Result;
    NTSTATUS Status;
    APPHELP_CACHE_SERVICE_LOOKUP CacheEntry;

    GetModuleFileNameW(NULL, szPath, sizeof(szPath) / sizeof(szPath[0]));
    Result = RtlDosPathNameToNtPathName_U(szPath, &ntPath, NULL, NULL);
    ok(Result == TRUE, "RtlDosPathNameToNtPathName_U\n");
    if (!InitEnv(&ntPath))
    {
        skip("NtApphelpCacheControl expects a different structure layout\n");
        return;
    }
    /* At this point we have made sure that our binary is not present in the cache,
        and that the NtApphelpCacheControl function expects the struct layout we use. */
    CheckValidation(&ntPath);

    /* We expect not to find it */
    Status = CallCacheControl(&ntPath, TRUE, ApphelpCacheServiceLookup);
    ok_ntstatus(Status, STATUS_NOT_FOUND);
    Status = CallCacheControl(&ntPath, FALSE, ApphelpCacheServiceLookup);
    ok_ntstatus(Status, STATUS_NOT_FOUND);

    /* First we add our process without a file handle (so it will be registered without file info) */
    RequestAddition(service_handle, FALSE);

    /* now we try to find it without validating file info */
    Status = CallCacheControl(&ntPath, FALSE, ApphelpCacheServiceLookup);
    ok_ntstatus(Status, STATUS_SUCCESS);
    /* when validating file info the cache notices the file is wrong, so it is dropped from the cache */
    Status = CallCacheControl(&ntPath, TRUE, ApphelpCacheServiceLookup);
    ok_ntstatus(Status, STATUS_NOT_FOUND);
    /* making the second check without info also fail. */
    Status = CallCacheControl(&ntPath, FALSE, ApphelpCacheServiceLookup);
    ok_ntstatus(Status, STATUS_NOT_FOUND);


    /* Now we add the file with file info */
    RequestAddition(service_handle, TRUE);

    /* so both checks should succeed */
    Status = CallCacheControl(&ntPath, TRUE, ApphelpCacheServiceLookup);
    ok_ntstatus(Status, STATUS_SUCCESS);
    Status = CallCacheControl(&ntPath, FALSE, ApphelpCacheServiceLookup);
    ok_ntstatus(Status, STATUS_SUCCESS);

    /* We know the file is in the cache now (assuming previous tests succeeded,
        let's test invalid handle behavior */
    CacheEntry.ImageName = ntPath;
    CacheEntry.ImageHandle = 0;
    Status = pNtApphelpCacheControl(ApphelpCacheServiceLookup, &CacheEntry);
    ok_ntstatus(Status, STATUS_NOT_FOUND);

    /* re-add it for the next test */
    RequestAddition(service_handle, TRUE);
    Status = CallCacheControl(&ntPath, TRUE, ApphelpCacheServiceLookup);
    ok_ntstatus(Status, STATUS_SUCCESS);
    CacheEntry.ImageHandle = (HANDLE)1;
    Status = pNtApphelpCacheControl(ApphelpCacheServiceLookup, &CacheEntry);
    ok_ntstatus(Status, STATUS_NOT_FOUND);

    /* and again */
    RequestAddition(service_handle, TRUE);
    Status = CallCacheControl(&ntPath, TRUE, ApphelpCacheServiceLookup);
    ok_ntstatus(Status, STATUS_SUCCESS);
#ifdef _WIN64
    CacheEntry.ImageHandle = (HANDLE)0x8000000000000000ULL;
#else
    CacheEntry.ImageHandle = (HANDLE)0x80000000;
#endif
    Status = pNtApphelpCacheControl(ApphelpCacheServiceLookup, &CacheEntry);
    ok_ntstatus(Status, STATUS_NOT_FOUND);

    RtlFreeHeap(RtlGetProcessHeap(), 0, ntPath.Buffer);
}