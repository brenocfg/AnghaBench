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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GspMemoryError ; 
 int /*<<< orphan*/  KdpSafeReadMemory (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static CHAR
GspReadMemSafe(PCHAR Address)
{
    CHAR ch = 0;

    if (!KdpSafeReadMemory((ULONG_PTR)Address, 1, &ch))
        GspMemoryError = TRUE;

    return ch;
}