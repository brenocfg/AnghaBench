#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_6__ {int DataLength; scalar_t__ Type; int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__* PKEY_VALUE_PARTIAL_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  KeyValueObject ;
typedef  TYPE_1__ KEY_VALUE_PARTIAL_INFORMATION ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AppCompatCacheValue ; 
 int /*<<< orphan*/  AppCompatKeyAttributes ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  KeyValuePartialInformation ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NtClose (scalar_t__) ; 
 scalar_t__ NtOpenKey (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NtQueryValueKey (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 scalar_t__ REG_BINARY ; 
 int RtlComputeCrc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hexdump (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  xprintf (char*,...) ; 

void DumpRegistryData(int IncludeDump)
{
    HANDLE KeyHandle;
    NTSTATUS Status;
    KEY_VALUE_PARTIAL_INFORMATION KeyValueObject;
    PKEY_VALUE_PARTIAL_INFORMATION KeyValueInformation = &KeyValueObject;
    ULONG KeyInfoSize, ResultSize;

    xprintf("Dumping AppCompatCache registry key\n");

    Status = NtOpenKey(&KeyHandle, KEY_QUERY_VALUE, &AppCompatKeyAttributes);

    Status = NtQueryValueKey(KeyHandle, &AppCompatCacheValue,
                KeyValuePartialInformation, KeyValueInformation,
                sizeof(KeyValueObject), &ResultSize);

    if (Status == STATUS_BUFFER_OVERFLOW)
    {
        KeyInfoSize = sizeof(KEY_VALUE_PARTIAL_INFORMATION) + KeyValueInformation->DataLength;
        KeyValueInformation = malloc(KeyInfoSize);
        if (KeyValueInformation != NULL)
        {
            Status = NtQueryValueKey(KeyHandle, &AppCompatCacheValue,
                        KeyValuePartialInformation, KeyValueInformation,
                        KeyInfoSize, &ResultSize);
        }
    }

    if (NT_SUCCESS(Status) && KeyValueInformation->Type == REG_BINARY)
    {
        ULONG crc;
        if (IncludeDump)
            hexdump(KeyValueInformation->Data, KeyValueInformation->DataLength);
        crc = RtlComputeCrc32(0, KeyValueInformation->Data, KeyValueInformation->DataLength);
        xprintf("Len: %lu, Crc: 0x%lx\n", KeyValueInformation->DataLength, crc);
    }
    else
    {
        xprintf("Failed reading AppCompatCache from registry (0x%lx)\n", Status);
    }

    if (KeyValueInformation != &KeyValueObject)
        free(KeyValueInformation);

    if (KeyHandle)
        NtClose(KeyHandle);
}