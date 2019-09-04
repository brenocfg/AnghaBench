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
typedef  scalar_t__ VOID ;
typedef  scalar_t__ const ULONG ;
typedef  scalar_t__ const UCHAR ;
typedef  size_t SIZE_T ;
typedef  scalar_t__ const* PCSTR ;
typedef  scalar_t__ CHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__ const,scalar_t__ const) ; 
 size_t strlen (scalar_t__ const*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__ const,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static
BOOLEAN
CheckStringBufferA(
    const VOID *Buffer,
    SIZE_T Size,
    PCSTR Expected,
    UCHAR Fill)
{
    const CHAR *Chars = Buffer;
    const UCHAR *UChars = Buffer;
    SIZE_T Length = strlen(Expected);
    SIZE_T i;

    if (Size < Length)
    {
        ok(0, "Size = %lu, Length = %lu\n", (ULONG)Size, (ULONG)Length);
        return FALSE;
    }

    for (i = 0; i < Length; i++)
        if (Chars[i] != Expected[i])
        {
            trace("Expected %x, found %x at offset %lu\n", Expected[i], Chars[i], (ULONG)i);
            return FALSE;
        }

    ok(Chars[i] == 0, "Expected null terminator, found %x at offset %lu\n", Chars[i], (ULONG)i);
    i++;

    for (; i < Size; i++)
        if (UChars[i] != Fill)
        {
            trace("Expected %x, found %x at offset %lu\n", Fill, UChars[i], (ULONG)i);
            return FALSE;
        }
    return TRUE;
}