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
typedef  int /*<<< orphan*/  SERVICE_STATUS ;
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ControlService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterShimCacheWithHandle ; 
 int /*<<< orphan*/  RegisterShimCacheWithoutHandle ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOLEAN RequestAddition(SC_HANDLE service_handle, BOOLEAN WithMapping)
{
    SERVICE_STATUS Status;
    ControlService(service_handle, WithMapping ? RegisterShimCacheWithHandle :
                    RegisterShimCacheWithoutHandle, &Status);
    /* TODO: how to get a return code from the service? */
    return TRUE;
}