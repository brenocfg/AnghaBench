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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  TokenInformation ;
struct TYPE_3__ {int /*<<< orphan*/  AuthenticationId; } ;
typedef  TYPE_1__ TOKEN_STATISTICS ;
typedef  int /*<<< orphan*/ * PLUID ;
typedef  scalar_t__ NTSTATUS ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NtClose (scalar_t__) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtCurrentThread () ; 
 scalar_t__ NtOpenProcessToken (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ NtOpenThreadToken (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ NtQueryInformationToken (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,int,scalar_t__*) ; 
 int READ_CONTROL ; 
 int /*<<< orphan*/  RtlCopyLuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_NO_TOKEN ; 
 int TOKEN_QUERY ; 
 int /*<<< orphan*/  TokenStatistics ; 

NTSTATUS
GetCallerLuid(PLUID CallerLuid)
{
    NTSTATUS Status;
    HANDLE TokenHandle;
    ULONG ReturnLength;
    TOKEN_STATISTICS TokenInformation;

    /* We need an output buffer */
    if (CallerLuid == NULL)
    {
        return STATUS_INVALID_PARAMETER;
    }

    /* Open thread token */
    TokenHandle = 0;
    ReturnLength = 0;
    Status = NtOpenThreadToken(NtCurrentThread(),
                               READ_CONTROL | TOKEN_QUERY,
                               FALSE, &TokenHandle);
    /* If we fail, open process token */
    if (Status == STATUS_NO_TOKEN)
    {
        Status = NtOpenProcessToken(NtCurrentProcess(),
                                    READ_CONTROL | TOKEN_QUERY,
                                    &TokenHandle);
    }

    /* In case of a success get caller LUID and copy it back */
    if (NT_SUCCESS(Status))
    {
        Status = NtQueryInformationToken(TokenHandle,
                                         TokenStatistics,
                                         &TokenInformation,
                                         sizeof(TokenInformation),
                                         &ReturnLength);
        if (NT_SUCCESS(Status))
        {
            RtlCopyLuid(CallerLuid, &TokenInformation.AuthenticationId);
        }
    }

    /* Close token handle */
    if (TokenHandle != 0)
    {
        NtClose(TokenHandle);
    }

    return Status;
}