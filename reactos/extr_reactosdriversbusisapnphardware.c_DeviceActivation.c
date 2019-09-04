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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  LDN; int /*<<< orphan*/  CSN; } ;
typedef  TYPE_1__* PISAPNP_LOGICAL_DEVICE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateDevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeactivateDevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HwDelay () ; 
 int /*<<< orphan*/  SendKey () ; 
 int /*<<< orphan*/  WaitForKey () ; 
 int /*<<< orphan*/  Wake (int /*<<< orphan*/ ) ; 

VOID
DeviceActivation(PISAPNP_LOGICAL_DEVICE IsaDevice,
                 BOOLEAN Activate)
{
  WaitForKey();
  SendKey();
  Wake(IsaDevice->CSN);

  if (Activate)
    ActivateDevice(IsaDevice->LDN);
  else
    DeactivateDevice(IsaDevice->LDN);

  HwDelay();

  WaitForKey();
}