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
typedef  scalar_t__ ULONG_PTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KdbBreakPointTemporary ; 
 int KdbpGetInstLength (scalar_t__) ; 
 int /*<<< orphan*/  KdbpInsertBreakPoint (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KdbpShouldStepOverInstruction (scalar_t__) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
KdbpStepOverInstruction(
    ULONG_PTR Eip)
{
    LONG InstLen;

    if (!KdbpShouldStepOverInstruction(Eip))
        return FALSE;

    InstLen = KdbpGetInstLength(Eip);
    if (InstLen < 1)
        return FALSE;

    if (!NT_SUCCESS(KdbpInsertBreakPoint(Eip + InstLen, KdbBreakPointTemporary, 0, 0, NULL, FALSE, NULL)))
        return FALSE;

    return TRUE;
}