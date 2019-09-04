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
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_3__ {int /*<<< orphan*/ * Buffer; int /*<<< orphan*/  MaximumLength; scalar_t__ Length; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
ViAllocateUnicodeString(USHORT BufferLength, PUNICODE_STRING UnicodeString)
{
    PVOID Buffer;

    /* Allocate the buffer */
    Buffer = ExAllocatePoolWithTag(NonPagedPool, BufferLength, ' dCV');
    /* Initialize */
    UnicodeString->Length = 0;
    UnicodeString->MaximumLength = BufferLength;
    UnicodeString->Buffer = Buffer;

    /* Return success if it went fine */
    if (Buffer != NULL)
    {
        return STATUS_SUCCESS;
    }

    return STATUS_NO_MEMORY;
}