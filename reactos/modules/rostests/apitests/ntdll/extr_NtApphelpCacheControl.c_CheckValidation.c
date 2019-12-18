#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {scalar_t__ ImageHandle; int /*<<< orphan*/  ImageName; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_2__ APPHELP_CACHE_SERVICE_LOOKUP ;

/* Variables and functions */
 int ApphelpCacheServiceDump ; 
 int ApphelpCacheServiceLookup ; 
 int ApphelpCacheServiceRemove ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok_ntstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtApphelpCacheControl (int,TYPE_2__*) ; 

void CheckValidation(UNICODE_STRING* PathName)
{
    APPHELP_CACHE_SERVICE_LOOKUP CacheEntry = { {0} };
    NTSTATUS Status;

    /* Validate the handling of a NULL pointer */
    Status = pNtApphelpCacheControl(ApphelpCacheServiceRemove, NULL);
    ok_ntstatus(Status, STATUS_INVALID_PARAMETER);
    Status = pNtApphelpCacheControl(ApphelpCacheServiceLookup, NULL);
    ok_ntstatus(Status, STATUS_INVALID_PARAMETER);

    /* Validate the handling of a NULL pointer inside the struct */
    Status = pNtApphelpCacheControl(ApphelpCacheServiceRemove, &CacheEntry);
    ok_ntstatus(Status, STATUS_INVALID_PARAMETER);
    Status = pNtApphelpCacheControl(ApphelpCacheServiceLookup, &CacheEntry);
    ok_ntstatus(Status, STATUS_INVALID_PARAMETER);

    /* Just call the dump function */
    Status = pNtApphelpCacheControl(ApphelpCacheServiceDump, NULL);
    ok_ntstatus(Status, STATUS_SUCCESS);

    /* Validate the handling of an invalid handle inside the struct */
    CacheEntry.ImageName = *PathName;
    CacheEntry.ImageHandle = (HANDLE)2;
    Status = pNtApphelpCacheControl(ApphelpCacheServiceLookup, &CacheEntry);
    ok_ntstatus(Status, STATUS_NOT_FOUND);

    /* Validate the handling of an invalid service number */
    Status = pNtApphelpCacheControl(999, NULL);
    ok_ntstatus(Status, STATUS_INVALID_PARAMETER);
    Status = pNtApphelpCacheControl(999, &CacheEntry);
    ok_ntstatus(Status, STATUS_INVALID_PARAMETER);
}