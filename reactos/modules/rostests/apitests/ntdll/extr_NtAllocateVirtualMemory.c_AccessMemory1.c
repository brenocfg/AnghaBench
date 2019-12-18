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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  LOBYTE (size_t) ; 

__attribute__((used)) static
VOID
AccessMemory1(
    PVOID UserBuffer,
    SIZE_T DataSize)
{
    PBYTE Buffer = UserBuffer;
    SIZE_T i;

    for (i = 0; i < DataSize; ++i)
        Buffer[i] = LOBYTE(i);
}