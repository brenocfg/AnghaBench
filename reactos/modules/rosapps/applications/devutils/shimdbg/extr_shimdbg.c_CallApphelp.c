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
typedef  int /*<<< orphan*/  PAPPHELP_CACHE_SERVICE_LOOKUP ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  APPHELPCACHESERVICECLASS ;

/* Variables and functions */
 scalar_t__ NtApphelpCacheControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (char*,unsigned int) ; 

void CallApphelp(APPHELPCACHESERVICECLASS Service,
                PAPPHELP_CACHE_SERVICE_LOOKUP CacheEntry)
{
    NTSTATUS Status = NtApphelpCacheControl(Service, CacheEntry);
    xprintf("NtApphelpCacheControl returned 0x%x\n", (unsigned int)Status);
}