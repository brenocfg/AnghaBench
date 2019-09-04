#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  TimeInfoOrg ;
struct TYPE_6__ {int TimeAdjustment; int Enable; int TimeIncrement; } ;
struct TYPE_5__ {int TimeAdjustment; int Enable; } ;
typedef  int /*<<< orphan*/  SetTimeInfo ;
typedef  TYPE_1__ SYSTEM_SET_TIME_ADJUST_INFORMATION ;
typedef  TYPE_2__ SYSTEM_QUERY_TIME_ADJUST_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  GetTimeInfo ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ NtQuerySystemInformation (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NtSetSystemInformation (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ RtlAdjustPrivilege (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SE_SYSTEMTIME_PRIVILEGE ; 
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 
 scalar_t__ STATUS_INVALID_PARAMETER_2 ; 
 scalar_t__ STATUS_PRIVILEGE_NOT_HELD ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemTimeAdjustmentInformation ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ok_long (int,int) ; 
 int /*<<< orphan*/  ok_ntstatus (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static
void
Test_TimeAdjustment(void)
{
    SYSTEM_QUERY_TIME_ADJUST_INFORMATION TimeInfoOrg, GetTimeInfo;
    SYSTEM_SET_TIME_ADJUST_INFORMATION SetTimeInfo;
    NTSTATUS Status;
    ULONG ReturnLength;
    BOOLEAN PrivilegeEnabled;

    SetTimeInfo.TimeAdjustment = 0;
    SetTimeInfo.Enable = 0;

    /* Query original values */
    Status = NtQuerySystemInformation(SystemTimeAdjustmentInformation,
                                      &TimeInfoOrg,
                                      sizeof(TimeInfoOrg),
                                      &ReturnLength);

    /* Test without privilege */
    Status = NtSetSystemInformation(SystemTimeAdjustmentInformation,
                                    &SetTimeInfo,
                                    sizeof(SetTimeInfo));
    ok_ntstatus(Status, STATUS_PRIVILEGE_NOT_HELD);

    /* Get the required privilege */
    Status = RtlAdjustPrivilege(SE_SYSTEMTIME_PRIVILEGE, TRUE, FALSE, &PrivilegeEnabled);
    if (!NT_SUCCESS(Status))
    {
        skip("Cannot acquire SeSystemTimePrivilege\n");
        return;
    }

    /* Test wrong length */
    Status = NtSetSystemInformation(SystemTimeAdjustmentInformation,
                                    &SetTimeInfo,
                                    sizeof(SetTimeInfo) + 1);
    ok_ntstatus(Status, STATUS_INFO_LENGTH_MISMATCH);

    /* Test both members 0 */
    Status = NtSetSystemInformation(SystemTimeAdjustmentInformation,
                                    &SetTimeInfo,
                                    sizeof(SetTimeInfo));
    ok_ntstatus(Status, STATUS_INVALID_PARAMETER_2);

    /* Set huge value */
    SetTimeInfo.TimeAdjustment = -1;
    SetTimeInfo.Enable = 0;
    Status = NtSetSystemInformation(SystemTimeAdjustmentInformation,
                                    &SetTimeInfo,
                                    sizeof(SetTimeInfo));
    ok_ntstatus(Status, STATUS_SUCCESS);

    /* Query the result */
    Status = NtQuerySystemInformation(SystemTimeAdjustmentInformation,
                                      &GetTimeInfo,
                                      sizeof(GetTimeInfo),
                                      &ReturnLength);
    ok_ntstatus(Status, STATUS_SUCCESS);
    ok_long(GetTimeInfo.TimeAdjustment, -1);
    ok_long(GetTimeInfo.Enable, 0);

    /* set Enable to 1 */
    SetTimeInfo.TimeAdjustment = -1;
    SetTimeInfo.Enable = 1;
    Status = NtSetSystemInformation(SystemTimeAdjustmentInformation,
                                    &SetTimeInfo,
                                    sizeof(SetTimeInfo));
    ok_ntstatus(Status, STATUS_SUCCESS);

    /* Query the result */
    Status = NtQuerySystemInformation(SystemTimeAdjustmentInformation,
                                      &GetTimeInfo,
                                      sizeof(GetTimeInfo),
                                      &ReturnLength);
    ok_ntstatus(Status, STATUS_SUCCESS);
    ok_long(GetTimeInfo.TimeAdjustment, GetTimeInfo.TimeIncrement);
    ok_long(GetTimeInfo.Enable, 1);

    /* Restore original values */
    SetTimeInfo.TimeAdjustment = TimeInfoOrg.TimeAdjustment;
    SetTimeInfo.Enable = TimeInfoOrg.Enable;
    Status = NtSetSystemInformation(SystemTimeAdjustmentInformation,
                                    &SetTimeInfo,
                                    sizeof(SetTimeInfo));
    ok_ntstatus(Status, STATUS_SUCCESS);

    Status = RtlAdjustPrivilege(SE_SYSTEMTIME_PRIVILEGE, PrivilegeEnabled, FALSE, &PrivilegeEnabled);
    ok(Status == STATUS_SUCCESS, "RtlAdjustPrivilege returned %lx\n", Status);
}