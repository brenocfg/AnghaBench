#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* dwCurrentState; void* dwCheckPoint; } ;
typedef  void* DWORD ;

/* Variables and functions */
 TYPE_1__ ServiceStatus ; 
 int /*<<< orphan*/  SetServiceStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  hServiceStatus ; 

__attribute__((used)) static void
_UpdateServiceStatus(DWORD dwNewStatus, DWORD dwCheckPoint)
{
    ServiceStatus.dwCheckPoint = dwCheckPoint;
    ServiceStatus.dwCurrentState = dwNewStatus;
    SetServiceStatus(hServiceStatus, &ServiceStatus);
}