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
typedef  int /*<<< orphan*/ ***************** ULONGLONG ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/ ***************** SYSTEM_POWER_POLICY ;
typedef  int /*<<< orphan*/ ***************** SYSTEM_POWER_INFORMATION ;
typedef  int /*<<< orphan*/ ***************** SYSTEM_POWER_CAPABILITIES ;
typedef  int /*<<< orphan*/ ***************** SYSTEM_BATTERY_STATE ;
typedef  int /*<<< orphan*/ ***************** PROCESSOR_POWER_POLICY ;
typedef  int /*<<< orphan*/ **************** PROCESSOR_POWER_INFORMATION ;
typedef  int /*<<< orphan*/  PPROCESSOR_POWER_INFORMATION ;
typedef  int /*<<< orphan*/ ****************** HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/ ***************** ADMINISTRATOR_POWER_POLICY ;

/* Variables and functions */
 int /*<<< orphan*/  AdministratorPowerPolicy ; 
 scalar_t__ CallNtPowerInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ******************,int,int /*<<< orphan*/ ******************,int) ; 
 int /*<<< orphan*/  LastSleepTime ; 
 int /*<<< orphan*/  LastWakeTime ; 
 int /*<<< orphan*/  ProcessorInformation ; 
 int /*<<< orphan*/  ProcessorPowerPolicyAc ; 
 int /*<<< orphan*/  ProcessorPowerPolicyCurrent ; 
 int /*<<< orphan*/  ProcessorPowerPolicyDc ; 
 int /*<<< orphan*/  ProcessorStateHandler ; 
 int /*<<< orphan*/  ProcessorStateHandler2 ; 
 scalar_t__ STATUS_ACCESS_DENIED ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_PRIVILEGE_NOT_HELD ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemBatteryState ; 
 int /*<<< orphan*/  SystemExecutionState ; 
 int /*<<< orphan*/  SystemPowerCapabilities ; 
 int /*<<< orphan*/  SystemPowerInformation ; 
 int /*<<< orphan*/  SystemPowerPolicyAc ; 
 int /*<<< orphan*/  SystemPowerPolicyCurrent ; 
 int /*<<< orphan*/  SystemPowerPolicyDc ; 
 int /*<<< orphan*/  SystemPowerStateHandler ; 
 int /*<<< orphan*/  SystemPowerStateNotifyHandler ; 
 int /*<<< orphan*/  VerifyProcessorPowerPolicyAc ; 
 int /*<<< orphan*/  VerifyProcessorPowerPolicyDc ; 
 int /*<<< orphan*/  VerifySystemPolicyAc ; 
 int /*<<< orphan*/  VerifySystemPolicyDc ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void test_CallNtPowerInformation(void)
{
   DWORD retval;
   ADMINISTRATOR_POWER_POLICY apolicy;
   ULONGLONG atime, ctime;
   PROCESSOR_POWER_INFORMATION ppi, *pppi;
   PROCESSOR_POWER_POLICY ppp;
   SYSTEM_BATTERY_STATE sbs;
   SYSTEM_POWER_CAPABILITIES spc;
   SYSTEM_POWER_INFORMATION spi;
   SYSTEM_POWER_POLICY spp;
   HANDLE x=NULL;

   /* AdministratorPowerPolicy tests */
   retval = CallNtPowerInformation(AdministratorPowerPolicy, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(AdministratorPowerPolicy, 0, 0, &apolicy, sizeof(ADMINISTRATOR_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(AdministratorPowerPolicy, &apolicy, sizeof(ADMINISTRATOR_POWER_POLICY), 0, 0);
   ok(retval != STATUS_PRIVILEGE_NOT_HELD, "Privileg not held!!!! more errors to expect\n");
   ok(retval == STATUS_SUCCESS, "function expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* LastSleepTime tests */
   retval = CallNtPowerInformation(LastSleepTime, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(LastSleepTime, &atime, sizeof(sizeof(ULONGLONG)), 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(LastSleepTime, &atime, sizeof(ULONGLONG), &ctime, sizeof(ULONGLONG));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(LastSleepTime, 0, 0, &atime, sizeof(ULONGLONG));
   ok(retval == STATUS_SUCCESS, "function expected STATUS_SUCCESS but got %d\n",(UINT)retval);

   /* LastWakeTime tests */
   retval = CallNtPowerInformation(LastWakeTime, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(LastWakeTime, &atime, sizeof(sizeof(ULONGLONG)), 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(LastWakeTime, &atime, sizeof(ULONGLONG), &ctime, sizeof(ULONGLONG));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(LastWakeTime, 0, 0, &atime, sizeof(ULONGLONG));
   ok(retval == STATUS_SUCCESS, "function expected STATUS_SUCCESS but got %d\n",(UINT)retval);

   /* ProcessorInformation tests */
   retval = CallNtPowerInformation(ProcessorInformation, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorInformation, 0, 0, &ppi, sizeof(PROCESSOR_POWER_INFORMATION));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorInformation, &ppi, sizeof(PROCESSOR_POWER_INFORMATION), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorInformation, &ppi, sizeof(PROCESSOR_POWER_INFORMATION), &ppi, sizeof(PROCESSOR_POWER_INFORMATION));

   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorInformation, 0, 0, &pppi, sizeof(PPROCESSOR_POWER_INFORMATION));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorInformation, &pppi, sizeof(PPROCESSOR_POWER_INFORMATION), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorInformation, &pppi, sizeof(PPROCESSOR_POWER_INFORMATION), &pppi, sizeof(PPROCESSOR_POWER_INFORMATION));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* ProcessorPowerPolicyAc tests */
   retval = CallNtPowerInformation(ProcessorPowerPolicyAc, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorPowerPolicyAc, 0, 0, &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorPowerPolicyAc, &ppp, sizeof(PROCESSOR_POWER_POLICY), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorPowerPolicyAc, &ppp, sizeof(PROCESSOR_POWER_POLICY), &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* ProcessorPowerPolicyCurrent tests */
   retval = CallNtPowerInformation(ProcessorPowerPolicyCurrent, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorPowerPolicyCurrent, 0, 0, &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorPowerPolicyCurrent, &ppp, sizeof(PROCESSOR_POWER_POLICY), 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorPowerPolicyCurrent, &ppp, sizeof(PROCESSOR_POWER_POLICY), &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);

   /* ProcessorPowerPolicyDc tests */
   retval = CallNtPowerInformation(ProcessorPowerPolicyDc, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorPowerPolicyDc, 0, 0, &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorPowerPolicyDc, &ppp, sizeof(PROCESSOR_POWER_POLICY), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorPowerPolicyDc, &ppp, sizeof(PROCESSOR_POWER_POLICY), &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* SystemBatteryState tests */
   retval = CallNtPowerInformation(SystemBatteryState, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemBatteryState, 0, 0, &sbs, sizeof(SYSTEM_BATTERY_STATE));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemBatteryState, &sbs, sizeof(SYSTEM_BATTERY_STATE), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemBatteryState, &sbs, sizeof(SYSTEM_BATTERY_STATE), &sbs, sizeof(SYSTEM_BATTERY_STATE));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* SystemExecutionState tests */
   retval = CallNtPowerInformation(SystemExecutionState, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* SystemPowerCapabilities tests */
   retval = CallNtPowerInformation(SystemPowerCapabilities, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerCapabilities, 0, 0, &spc, sizeof(SYSTEM_POWER_CAPABILITIES));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerCapabilities, &spc, sizeof(SYSTEM_POWER_CAPABILITIES), 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerCapabilities, &spc, sizeof(SYSTEM_POWER_CAPABILITIES), &spc, sizeof(SYSTEM_POWER_CAPABILITIES));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);

   /* SystemPowerInformation tests */
   retval = CallNtPowerInformation(SystemPowerInformation, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerInformation, 0, 0, &spi, sizeof(SYSTEM_POWER_INFORMATION));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerInformation, &spi, sizeof(SYSTEM_POWER_INFORMATION), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerInformation, &spi, sizeof(SYSTEM_POWER_INFORMATION), &spi, sizeof(SYSTEM_POWER_INFORMATION));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerInformation, &spp, sizeof(SYSTEM_POWER_POLICY), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerInformation, &spp, sizeof(SYSTEM_POWER_POLICY), &spi, sizeof(SYSTEM_POWER_INFORMATION));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* SystemPowerPolicyAc tests */
   retval = CallNtPowerInformation(SystemPowerPolicyAc, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerPolicyAc, 0, 0, &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerPolicyAc, &spp, sizeof(SYSTEM_POWER_POLICY), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerPolicyAc, &spp, sizeof(SYSTEM_POWER_POLICY), &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* SystemPowerPolicyCurrent tests */
   retval = CallNtPowerInformation(SystemPowerPolicyCurrent, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerPolicyCurrent, 0, 0, &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerPolicyCurrent, &spp, sizeof(SYSTEM_POWER_POLICY), 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerPolicyCurrent, &spp, sizeof(SYSTEM_POWER_POLICY), &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);

   /* SystemPowerPolicyDc tests */
   retval = CallNtPowerInformation(SystemPowerPolicyDc, 0, 0, 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerPolicyDc, 0, 0, &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerPolicyDc, &spp, sizeof(SYSTEM_POWER_POLICY), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerPolicyDc, &spp, sizeof(SYSTEM_POWER_POLICY), &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* SystemReserveHiberFile tests */
/*
   retval = CallNtPowerInformation(SystemReserveHiberFile, 0, 0, 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %ld\n", retval);
   bln=TRUE;
   retval = CallNtPowerInformation(SystemReserveHiberFile, &bln, sizeof(bln), 0, 0);
   ok(retval == STATUS_DISK_FULL, "function result wrong expected STATUS_DISK_FULL but got %ld\n", nret);
   bln=FALSE;
   retval = CallNtPowerInformation(SystemReserveHiberFile, &bln, sizeof(bln), 0, 0);
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %ld\n", nret);

   bln2=TRUE;
   nret = CallNtPowerInformation(SystemReserveHiberFile, 0, 0, &bln2, sizeof(bln2));
   ok(nret == STATUS_DATATYPE_MISALIGNMENT, "function result wrong expected STATUS_DATATYPE_MISALIGNMENT but got %ld\n", nret);
   bln2=FALSE;
   nret = CallNtPowerInformation(SystemReserveHiberFile, 0, 0, &bln2, sizeof(bln2));
   ok(nret == STATUS_DATATYPE_MISALIGNMENT, "function result wrong expected STATUS_DATATYPE_MISALIGNMENT but got %ld\n", nret);

   bln=TRUE;
   bln2=TRUE;
   nret = CallNtPowerInformation(SystemReserveHiberFile, &bln, sizeof(bln), &bln2, sizeof(bln2));
   ok(nret == STATUS_DATATYPE_MISALIGNMENT, "function result wrong expected STATUS_DATATYPE_MISALIGNMENT but got %ld\n", nret);
   bln2=FALSE;
   nret = CallNtPowerInformation(SystemReserveHiberFile, &bln, sizeof(bln), &bln2, sizeof(bln2));
   ok(nret == STATUS_DATATYPE_MISALIGNMENT, "function result wrong expected STATUS_DATATYPE_MISALIGNMENT but got %ld\n", nret);
   bln=FALSE;
   bln2=TRUE;
   nret = CallNtPowerInformation(SystemReserveHiberFile, &bln, sizeof(bln), &bln2, sizeof(bln2));
   ok(nret == STATUS_DATATYPE_MISALIGNMENT, "function result wrong expected STATUS_DATATYPE_MISALIGNMENT but got %ld\n", nret);
   bln2=FALSE;
   nret = CallNtPowerInformation(SystemReserveHiberFile, &bln, sizeof(bln), &bln2, sizeof(bln2));
   ok(nret == STATUS_DATATYPE_MISALIGNMENT, "function result wrong expected STATUS_DATATYPE_MISALIGNMENT but got %ld\n", nret);
 */

   /* VerifyProcessorPowerPolicyAc tests */
   retval = CallNtPowerInformation(VerifyProcessorPowerPolicyAc, 0, 0, 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifyProcessorPowerPolicyAc, 0, 0, &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifyProcessorPowerPolicyAc, &ppp, sizeof(PROCESSOR_POWER_POLICY), 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifyProcessorPowerPolicyAc, &ppp, sizeof(PROCESSOR_POWER_POLICY), &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* VerifyProcessorPowerPolicyDc tests */
   retval = CallNtPowerInformation(VerifyProcessorPowerPolicyDc, 0, 0, 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifyProcessorPowerPolicyDc, 0, 0, &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifyProcessorPowerPolicyDc, &ppp, sizeof(PROCESSOR_POWER_POLICY), 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifyProcessorPowerPolicyDc, &ppp, sizeof(PROCESSOR_POWER_POLICY), &ppp, sizeof(PROCESSOR_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* VerifySystemPolicyAc tests */
   retval = CallNtPowerInformation(VerifySystemPolicyAc, 0, 0, 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifySystemPolicyAc, 0, 0, &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifySystemPolicyAc, &spp, sizeof(SYSTEM_POWER_POLICY), 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifySystemPolicyAc, &spp, sizeof(SYSTEM_POWER_POLICY), &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* VerifySystemPolicyDc tests */
   retval = CallNtPowerInformation(VerifySystemPolicyDc, 0, 0, 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifySystemPolicyDc, 0, 0, &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifySystemPolicyDc, &spp, sizeof(SYSTEM_POWER_POLICY), 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(VerifySystemPolicyDc, &spp, sizeof(SYSTEM_POWER_POLICY), &spp, sizeof(SYSTEM_POWER_POLICY));
   ok(retval == STATUS_SUCCESS, "function result wrong expected STATUS_SUCCESS but got %d\n", (UINT)retval);

   /* SystemPowerStateHandler tests */
   retval = CallNtPowerInformation(SystemPowerStateHandler, 0, 0, 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerStateHandler, 0, 0, x, sizeof(HANDLE));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);

   /* ProcessorStateHandler tests */
   retval = CallNtPowerInformation(ProcessorStateHandler, 0, 0, 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorStateHandler, 0, 0, x, sizeof(HANDLE));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);

   /* ProcessorStateHandler2 tests */
   retval = CallNtPowerInformation(ProcessorStateHandler2, 0, 0, 0, 0);
   ok(retval == STATUS_ACCESS_DENIED, "function result wrong expected STATUS_ACCESS_DENIED but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(ProcessorStateHandler2, 0, 0, x, sizeof(HANDLE));
   ok(retval == STATUS_ACCESS_DENIED, "function result wrong expected STATUS_ACCESS_DENIED but got %d\n", (UINT)retval);

   /* SystemPowerStateNotifyHandler tests */
   retval = CallNtPowerInformation(SystemPowerStateNotifyHandler, 0, 0, 0, 0);
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);
   retval = CallNtPowerInformation(SystemPowerStateNotifyHandler, 0, 0, x, sizeof(HANDLE));
   ok(retval == STATUS_INVALID_PARAMETER, "function result wrong expected STATUS_INVALID_PARAMETER but got %d\n", (UINT)retval);

}