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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ const UCHAR ;
typedef  size_t SIZE_T ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  trace (char*,scalar_t__ const,scalar_t__ const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOLEAN
CheckBuffer(
    const VOID *Buffer,
    SIZE_T Size,
    UCHAR Value)
{
    const UCHAR *Array = Buffer;
    SIZE_T i;

    for (i = 0; i < Size; i++)
        if (Array[i] != Value)
        {
            trace("Expected %x, found %x at offset %lu\n", Value, Array[i], (ULONG)i);
            return FALSE;
        }
    return TRUE;
}