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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int USHORT ;
struct TYPE_3__ {int Length; int* Buffer; } ;
typedef  int* PWCHAR ;
typedef  TYPE_1__* PUNICODE_STRING ;

/* Variables and functions */

__attribute__((used)) static USHORT
RtlpGetCheckSum(PUNICODE_STRING Name)
{
    PWCHAR CurrentChar;
    USHORT Hash;
    USHORT Saved;
    USHORT Length;

    if (!Name->Length)
        return 0;

    if (Name->Length == sizeof(WCHAR))
        return Name->Buffer[0];

    CurrentChar = Name->Buffer;
    Hash = (*CurrentChar << 8) + *(CurrentChar + 1);

    if (Name->Length == 2 * sizeof(WCHAR))
        return Hash;

    Saved = Hash;
    Length = 2;

    do
    {
        CurrentChar += 2;
        Hash = (Hash << 7) + *CurrentChar;
        Hash = (Saved >> 1) + (Hash << 8);

        if (Length + 1 < Name->Length / sizeof(WCHAR))
        {
            Hash += *(CurrentChar + 1);
        }

        Saved = Hash;
        Length += 2;
    }
    while (Length < Name->Length / sizeof(WCHAR));

    return Hash;
}