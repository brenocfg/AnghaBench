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
struct TYPE_3__ {int /*<<< orphan*/  CriticalSection; } ;
typedef  TYPE_1__* PRTL_ATOM_TABLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  RtlEnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
RtlpLockAtomTable(PRTL_ATOM_TABLE AtomTable)
{
   RtlEnterCriticalSection(&AtomTable->CriticalSection);
   return TRUE;
}