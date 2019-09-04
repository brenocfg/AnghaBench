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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ApphelpCacheServiceRemove ; 
 scalar_t__ CallCacheControl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_NOT_FOUND ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

int InitEnv(UNICODE_STRING* PathName)
{
    NTSTATUS Status = CallCacheControl(PathName, FALSE, ApphelpCacheServiceRemove);
    if (Status == STATUS_INVALID_PARAMETER)
    {
        /* Windows Vista+ has a different layout for APPHELP_CACHE_SERVICE_LOOKUP */
        return 0;
    }
    ok(Status == STATUS_SUCCESS || Status == STATUS_NOT_FOUND,
        "Wrong value for Status, expected: SUCCESS or NOT_FOUND, got: 0x%lx\n",
        Status);
    return 1;
}