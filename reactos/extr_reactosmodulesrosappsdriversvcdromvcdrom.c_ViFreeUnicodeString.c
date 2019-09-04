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
struct TYPE_3__ {scalar_t__ MaximumLength; scalar_t__ Length; int /*<<< orphan*/ * Buffer; } ;
typedef  TYPE_1__* PUNICODE_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID
ViFreeUnicodeString(PUNICODE_STRING UnicodeString)
{
    /* Only free if allocate, that allows using this
     * on cleanup in short memory situations
     */
    if (UnicodeString->Buffer != NULL)
    {
        ExFreePoolWithTag(UnicodeString->Buffer, 0);
        UnicodeString->Buffer = NULL;
    }

    /* Zero the rest */
    UnicodeString->Length = 0;
    UnicodeString->MaximumLength = 0;
}