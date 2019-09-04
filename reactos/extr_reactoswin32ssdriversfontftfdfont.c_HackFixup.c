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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__* PVOID ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 scalar_t__* EngAllocMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

PVOID
HackFixup(
    PVOID pvView,
    ULONG cjView)
{
    CHAR *pc;

    pc = EngAllocMem(0, cjView, 'tmp ');
    memcpy(pc, pvView, cjView);

    *pc = 0;

    return pc;
}